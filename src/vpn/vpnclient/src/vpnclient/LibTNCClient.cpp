/*
 * This software is Copyright (C) 2010-2011
 * Fachhochschule Hannover (University of Applied Sciences and Arts)
 * Use is subject to license conditions.
 *
 * The main licensing options available are:
 *
 * Open Source Licensing. This is the appropriate option if you want to
 * share the source code of your application with everyone you
 * distribute it to, and you also want to give them the right to share
 * who uses it. If you wish to use TNC@FHH under Open Source Licensing,
 * you must contribute all your source code to the open source
 * community in accordance with the GPL Version 2 when your application
 * is distributed. See http://www.gnu.org/licenses/gpl-2.0.html/ or gpl-2.0.txt
 *
 * Commercial Licensing. This is the appropriate option if you are
 * creating proprietary applications and you are not prepared to
 * distribute and share the source code of your application.
 * Contact trust@f4-i.fh-hannover.de for details.
 *
 * http://trust.inform.fh-hannover.de/
 */

#include "LibTNCClient.h"
#include <iostream>

#include <log4cxx/logger.h>

// FIXME: we only support _one_ active TNCClient
static ifttls::Envelope *uglyStaticEnvelopePointer = NULL;
static bool uglyStaticReceiveIndicator = false;

namespace tnc {

#define LOGNAME "[LibTNC Wrapper]"
static log4cxx::LoggerPtr logger = log4cxx::Logger::getLogger(LOGNAME);

LibTNCClient::LibTNCClient() : wantWrite_(true), wantRead_(false), finished_(false)
{
	LOG4CXX_TRACE(logger, "Constructor");
}

LibTNCClient::~LibTNCClient()
{
	LOG4CXX_TRACE(logger, "Delete connection");
	libtnc_tncc_DeleteConnection(connection);
	libtnc_tncc_Terminate();
	connection = NULL;
	LOG4CXX_TRACE(logger, "Deleted");
}

void LibTNCClient::beginSession()
{
	LOG4CXX_TRACE(logger, "beginSession()");
	/* TODO: configureable? */
	libtnc_tncc_Initialize("/etc/tnc_config");
	libtnc_tncc_PreferredLanguage("en");
	connection = libtnc_tncc_CreateConnection(NULL);
	libtnc_tncc_BeginSession(connection);
	LOG4CXX_TRACE(logger, "beginSession() finished");
}

ifttls::Envelope *LibTNCClient::getMessage()
{
	LOG4CXX_TRACE(logger, "getMessage()");
	if (wantWrite_ && uglyStaticReceiveIndicator) {
		ifttls::Envelope *tmp = uglyStaticEnvelopePointer;
		uglyStaticEnvelopePointer = NULL;
		uglyStaticReceiveIndicator = false;
		wantWrite_ = false;
		wantRead_ = true;
		return tmp;
	} else {
		LOG4CXX_ERROR(logger, "getMessage() bad call!");
		throw 20;
	}
}

void LibTNCClient::putData(ifttls::Envelope *env)
{
	LOG4CXX_TRACE(logger, "putData() value length=" << env->getMessageValueLength());
	if (wantRead_) {
		char * payload = env->getMessageValue();
		uint32_t len = env->getMessageValueLength();
		TNC_Result res = libtnc_tncc_ReceiveBatch(connection, payload, len);
		delete[] payload;
		if (res == TNC_RESULT_SUCCESS) {
			wantWrite_ = true;
			wantRead_ = false;

			/* no message to be sent, so we are finished */
			if (!uglyStaticReceiveIndicator) {
				LOG4CXX_TRACE(logger, "Finished!");
				finished_ = true;
			} else {
				LOG4CXX_TRACE(logger, "Have something to send!!!");
			}
		} else {
			LOG4CXX_ERROR(logger, "putData() failed!");
		}
	} else {
		LOG4CXX_ERROR(logger, "putData() bad call!");
		throw 30;
	}
}


} // namespace tnc

/*
 * This is the callback function needed by libtnc, currently it assumes only
 * one libtnc_tncc_connection is open and uses a static pointer
 * to an envelope to store the message to be sent
 */
TNC_Result TNC_TNCC_SendBatch(libtnc_tncc_connection *conn, const char *buffer,
			      size_t len)
{
	LOG4CXX_TRACE(tnc::logger, "TNC_TNCC_SendBatch()");
	uglyStaticEnvelopePointer = new ifttls::Envelope(ifttls::Envelope::IFT_TNCCS_20_BATCH,
			buffer, len);
	uglyStaticReceiveIndicator = true;

	return TNC_RESULT_SUCCESS;
}
/*
 * Callback normally needed for a TNCS implementation. Linking under
 * Ubuntu leads to errors as of a failing TNC_TNCS_SendBatch function.
 * Therefore, include a skeleton here.
 */
TNC_Result TNC_TNCS_SendBatch( libtnc_tncc_connection *conn, const char *buffer,
			       size_t len)
{
	return TNC_RESULT_SUCCESS;
}

