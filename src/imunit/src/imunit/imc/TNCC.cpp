/*
 * This software is Copyright (C) 2006-2009
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

#include "TNCC.h"
#include "IMCLibrary.h"

#include <log4cxx/logger.h>

using namespace log4cxx;
using namespace log4cxx::helpers;

namespace tncfhh {

namespace iml {

static LoggerPtr logger(Logger::getLogger("IMUnit.TNCC"));

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNCC::TNCC(TNC_ConnectionID cid, IMCLibrary *pImcLibrary):
	cid(cid), pImcLibrary(pImcLibrary)
{
	// intentionally left blank
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNCC::~TNCC()
{
	// intentionally left blank
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void TNCC::sendMessage(TNC_BufferReference message, TNC_UInt32 messageLength, TNC_MessageType messageType) throw (ResultException)
{
//	Possible binary data in message... Just comment this out and leave it
//	to the IMV whether output is done or not
//	LOG4CXX_TRACE(logger, "sendMessage message: " << message << " length: "<< messageLength  << "type: " << messageType);
	LOG4CXX_TRACE(logger, "sendMessage message: length: "<< messageLength  << "type: " << messageType);
	if (pImcLibrary->tnccFunctionPointers.sendMessagePointer == NULL)
	{
		LOG4CXX_WARN(logger, "No function pointer for sending message to TNCC. Throwing ResultException ...")
		throw ResultException("Could not send a message. No sendMessage function pointer", TNC_RESULT_FATAL);
	}

	TNC_Result result = pImcLibrary->tnccFunctionPointers.sendMessagePointer(pImcLibrary->getIMUnitLibraryID(), this->cid, message, messageLength, messageType);

	if (result != TNC_RESULT_SUCCESS)
	{
		LOG4CXX_WARN(logger, "Error when calling sendMessage for TNCC. Throwing ResultException ...")
		throw ResultException(std::string("Exception on TNCC::sendMessage."), result);
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void TNCC::sendMessage(TNC_BufferReference message, TNC_UInt32 messageLength, TNC_VendorID vendorId, TNC_MessageSubtype messageSubtype) throw (ResultException)
{
	this->sendMessage(message, messageLength, (vendorId << 8) | (messageSubtype & 0xff));
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void TNCC::requestHandshakeRetry(TNC_RetryReason reason) throw (ResultException)
{
	LOG4CXX_TRACE(logger, "requestHandshakeRetry reason: " << reason);
	if (pImcLibrary->tnccFunctionPointers.requestHandshakeRetryPointer == NULL)
	{
		LOG4CXX_WARN(logger, "No function pointer for requestHandshakeRetry in TNCC. Throwing ResultException ...")
		throw ResultException("Could not requestHandshakeRetry. No requestHandshakeRetry function pointer", TNC_RESULT_FATAL);
	}

	TNC_Result result = pImcLibrary->tnccFunctionPointers.requestHandshakeRetryPointer(pImcLibrary->getIMUnitLibraryID(), this->cid, reason);

	if (result != TNC_RESULT_SUCCESS)
	{
		LOG4CXX_WARN(logger, "Error when calling requestHandshakeRetry for TNCC. Throwing ResultException ...")
		throw ResultException(std::string("Exception on requestHandshakeRetry."), result);
	}
}

}  // namespace iml

}  // namespace tncfhh
