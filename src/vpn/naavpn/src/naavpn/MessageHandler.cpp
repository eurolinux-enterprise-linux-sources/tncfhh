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

#include "MessageHandler.h"
#include "PEPNotifier.h"

#include <log4cxx/logger.h>

#define LOGNAME "[MsgHandler]"
static log4cxx::LoggerPtr logger = log4cxx::Logger::getLogger(LOGNAME);

namespace tnc {

using namespace ifttls;

MessageHandler::MessageHandler(tnc::Endpoint *ep)
	: ep(ep), reply_msg(0), pre_negotiation_finished(false),
	  want_read_(true), want_write_(false), finished_(false) {


	std::string ip = ep->getAddress()->to_string();

	// Create connection id
	conn_id = tncfhh::iel::coordinator.getConnection(ip);
}

MessageHandler::~MessageHandler() {
	LOG4CXX_TRACE(logger, "Destructor");
	clean();
}

void
MessageHandler::handleMessage(Envelope* message) {

	// Ensure reply_msg is clean!
	clean();

	switch (message->getMessageType()) {
		case Envelope::IFT_TNCCS_20_BATCH: handleTnccs20Batch(message); break;
	}
}

void
MessageHandler::handleTnccs20Batch(Envelope* message) {
	LOG4CXX_TRACE(logger, "TNCCS 20 Batch received");

	// The notifier is used to send a recommendation
	// to the PEP
	tnc::PEPNotifier notifier;

	try {
		tncfhh::iel::TNCCSData data((TNC_BufferReference) message->getMessageValue(),
				                    message->getMessageValueLength());

		// Passing the TNCCS payload to the TNC server
		tncfhh::iel::TNCCSData ret = tncfhh::iel::coordinator.processTNCCSData(conn_id, data);


		// This part is only reached when the TNC server wants to send data
		// back to the client since processTNCCSData() throws an exception
		// if the Endpoint verification has finished.
		reply_msg = new Envelope(Envelope::IFT_TNCCS_20_BATCH,
				       (const char*) ret.getData(),
					ret.getLength());

	} catch (tncfhh::iel::ConnectionStateExceptionWithTNCCSData e) {
		LOG4CXX_INFO(logger, "Access Recommendation");

		switch (e.getConnectionState()) {
		case TNC_CONNECTION_STATE_ACCESS_ALLOWED:
			LOG4CXX_INFO(logger, "ALLOW");
			notifier.sendAllow(ep);
			break;
		case TNC_CONNECTION_STATE_ACCESS_NONE:
			LOG4CXX_INFO(logger, "NO ACCESS");
			notifier.sendDeny(ep);
			break;
		case TNC_CONNECTION_STATE_ACCESS_ISOLATED:
			LOG4CXX_INFO(logger, "ISOLATE");
			// Not implemented yet!
			break;
		}
		tncfhh::iel::TNCCSData ret = e.getLastTnccsData();
		reply_msg = new Envelope(Envelope::IFT_TNCCS_20_BATCH,
				       (const char*) ret.getData(),
					ret.getLength());
		finished_ = true;
	}
}


bool
MessageHandler::hasReplyMessage() const {
	return reply_msg != 0;
}


Envelope*
MessageHandler::getReplyMessage() {
	Envelope *tmp = reply_msg;
	reply_msg = NULL;
	return tmp;
}

void
MessageHandler::clean() {

	if (reply_msg != NULL) {
		delete reply_msg;
		reply_msg = 0;
	}

}


bool
MessageHandler::wantWrite() const {
	return want_write_;
}


bool
MessageHandler::wantRead() const {
	return want_read_;
}


void
MessageHandler::done() {
	if (!finished_) {
		want_read_ = !want_read_;
		want_write_ = !want_write_;
	} else {
		want_read_ = false;
		want_write_ = false;
	}
}

}
