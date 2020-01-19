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

#include "TNCS.h"
#include "IMVLibrary.h"

#include <log4cxx/logger.h>
using namespace log4cxx;

namespace tncfhh {

namespace iml {

static LoggerPtr logger(Logger::getLogger("IMUnit.TNCS"));

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNCS::TNCS(TNC_ConnectionID cid, IMVLibrary *pImvLibrary):
	cid(cid), pImvLibrary(pImvLibrary)
{
	// intentionally left blank
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *                               TNCS::~TNCS()                               *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

TNCS::~TNCS()
{
	// intentionally left blank
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void TNCS::sendMessage(TNC_BufferReference message, TNC_UInt32 messageLength, TNC_MessageType messageType) throw (ResultException)
{
//	Possible binary data in message... Just comment this out and leave it
//	to the IMV whether output is done or not
//	LOG4CXX_TRACE(logger, "sendMessage message: " << message << " length: "<< messageLength  << "type: " << messageType);
	LOG4CXX_TRACE(logger, "sendMessage message: length: "<< messageLength  << "type: " << messageType);
	if (pImvLibrary->tncsFunctionPointers.sendMessagePointer == NULL)
	{
		LOG4CXX_WARN(logger, "No function pointer for sending message to TNCS. Throwing ResultException ...")
		throw ResultException("Could not send a message, because I do not have the functionpointer", TNC_RESULT_FATAL);
	}

	TNC_Result result = pImvLibrary->tncsFunctionPointers.sendMessagePointer(pImvLibrary->getIMUnitLibraryID(), cid, message, messageLength, messageType);
	if (result != TNC_RESULT_SUCCESS)
	{
		LOG4CXX_WARN(logger, "Error when calling sendMessage for TNCS. Throwing ResultException ...")
		throw ResultException(std::string("Exception on send a message."), result);
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void TNCS::sendMessage(TNC_BufferReference message, TNC_UInt32 messageLength, TNC_VendorID vendorId, TNC_MessageSubtype messageSubtype) throw (ResultException)
{
	this->sendMessage(message, messageLength, (vendorId << 8) | (messageSubtype & 0xff));
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void TNCS::requestHandshakeRetry(TNC_RetryReason reason) throw (ResultException)
{
	LOG4CXX_TRACE(logger, "requestHandshakeRetry reason: " << reason);
	if (pImvLibrary->tncsFunctionPointers.requestHandshakeRetryPointer == NULL)
	{
		LOG4CXX_WARN(logger, "No function pointer for requestHandshakeRetry in TNCS. Throwing ResultException ...")
		throw ResultException("Could not requestHandshakeRetry, because i haven't the functionpointer", TNC_RESULT_FATAL);
	}

	TNC_Result result = pImvLibrary->tncsFunctionPointers.requestHandshakeRetryPointer(pImvLibrary->getIMUnitLibraryID(), cid, reason);
	if (result != TNC_RESULT_SUCCESS)
	{
		LOG4CXX_WARN(logger, "Error when calling requestHandshakeRetry for TNCS. Throwing ResultException ...")
		throw ResultException(std::string("Exception on requestHandshakeRetry."), result);
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void TNCS::provideRecommendation(TNC_IMV_Action_Recommendation recommendation, TNC_IMV_Evaluation_Result evaluation) throw (ResultException)
{
	LOG4CXX_TRACE(logger, "provideRecommendation recommendation: " << recommendation << " evaluation: " << evaluation);
	if (pImvLibrary->tncsFunctionPointers.provideRecommendationPointer == NULL)
	{
		LOG4CXX_WARN(logger, "No function pointer for provideRecommendation in TNCS. Throwing ResultException ...")
		throw ResultException("Could not provide recommendation, because i haven't the functionpointer", TNC_RESULT_FATAL);
	}

	TNC_Result result = pImvLibrary->tncsFunctionPointers.provideRecommendationPointer(pImvLibrary->getIMUnitLibraryID(), cid, recommendation, evaluation);

	if (result != TNC_RESULT_SUCCESS)
	{
		LOG4CXX_WARN(logger, "Error when calling provideRecommendation for TNCS. Throwing ResultException ...")
		throw ResultException(std::string("Exception on provide recommendation."), result);
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool TNCS::getAttribute(/*in*/ TNC_AttributeID attributeID, /*in*/ TNC_UInt32 bufferLength, /*out*/ TNC_BufferReference buffer, /*out*/ TNC_UInt32 *pOutValueLength) throw (ResultException)
{
	LOG4CXX_TRACE(logger, "getAttribute attributeID: " << attributeID << " bufferLength: " << bufferLength);
	if (pImvLibrary->tncsFunctionPointers.getAttributePointer == NULL)
	{
		LOG4CXX_INFO(logger, "No function pointer for getAttribute in TNCS. Don't call getAttribute.")
		return false;
	}

	TNC_Result result = pImvLibrary->tncsFunctionPointers.getAttributePointer(pImvLibrary->getIMUnitLibraryID(), cid, attributeID, bufferLength, buffer, pOutValueLength);

	if (result != TNC_RESULT_SUCCESS)
	{
		LOG4CXX_WARN(logger, "Error when calling getAttribute for TNCS. Throwing ResultException ...")
		throw ResultException(std::string("Exception on get attribute."), result);
	}
	return true;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool TNCS::supportGetAttribute()
{
	return pImvLibrary->tncsFunctionPointers.getAttributePointer != NULL;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool TNCS::setAttribute(TNC_AttributeID attributeID, TNC_UInt32 bufferLength, TNC_BufferReference buffer) throw (ResultException)
{
	LOG4CXX_TRACE(logger, "setAttribute attributeID: " << attributeID << " bufferLength: " << bufferLength);
	if (pImvLibrary->tncsFunctionPointers.setAttributePointer == NULL)
	{
		LOG4CXX_INFO(logger, "No function pointer for setAttribute in TNCS. Don't call setAttribute.")
		return false;
	}
	TNC_Result result = pImvLibrary->tncsFunctionPointers.setAttributePointer(pImvLibrary->getIMUnitLibraryID(), cid, attributeID, bufferLength, buffer);

	if (result != TNC_RESULT_SUCCESS)
	{
		LOG4CXX_WARN(logger, "Error when calling setAttribute in TNCS. Throwing ResultException ...")
		throw ResultException(std::string("Exception on set attribute."), result);
	}
	return true;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool TNCS::supportSetAttribute()
{
	return pImvLibrary->tncsFunctionPointers.setAttributePointer != NULL;
}

}  // namespace iml

}  // namespace tncfhh
