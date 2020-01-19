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

#include "ExampleIMV.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <log4cxx/logger.h>

static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("IMUnit.AbstractIMUnit.AbstractIMC.ExampleIMV"));

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
ExampleIMV::ExampleIMV(TNC_ConnectionID conID, ExampleIMVLibrary *pExampleIMVLibrary)
	:AbstractIMV(conID, pExampleIMVLibrary)
{
	// initialize
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
ExampleIMV::~ExampleIMV()
{
	// if necessary delete memory
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_Result ExampleIMV::receiveMessage(TNC_BufferReference message,
		                          TNC_UInt32 messageLength,
		                          TNC_MessageType messageType)
{
	LOG4CXX_DEBUG(logger, "receiveMessage round " << this->getRound());

	// print received message dirty out. WARNING: don't ape this,
	// message should end with non-null! Heed: Message can be evil!
	LOG4CXX_INFO(logger, "Received Message: " << message);

	/* only send one message to ExampleIMC */
	if (this->getRound() < 1) {
		// this message should be send to ExampleIMC
		std::string sendMessage("Example message from ExampleIMV");

		LOG4CXX_INFO(logger, "Send Message: " << sendMessage);
		// send message
		this->tncs.sendMessage((unsigned char*)sendMessage.c_str(), sendMessage.size()+1/*for'\0'*/, VENDOR_ID, MESSAGE_SUBTYPE);
	} else {
		/* validation finish, set recommendation & co */
        validationFinished = true;

		// for no access:
//		actionRecommendation = TNC_IMV_ACTION_RECOMMENDATION_NO_ACCESS;
		// for isolate:
//		actionRecommendation = TNC_IMV_ACTION_RECOMMENDATION_ISOLATE;
		// for access allow:
        actionRecommendation = TNC_IMV_ACTION_RECOMMENDATION_ALLOW;

        // set evaluation (see TNC_IMV_EVALUATION_RESULT_...)
        evaluationResult = TNC_IMV_EVALUATION_RESULT_DONT_KNOW;
	}

	// return all ok
	return TNC_RESULT_SUCCESS;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_Result ExampleIMV::batchEnding()
{
	LOG4CXX_TRACE(logger, "batchEnding");
	// return all ok
	return TNC_RESULT_SUCCESS;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_Result ExampleIMV::notifyConnectionChange()
{
	LOG4CXX_TRACE(logger, "notifyConnectionChange");

	/* if new handshake start */
	if(this->getConnectionState() == TNC_CONNECTION_STATE_HANDSHAKE)
		/* reset IMC */;

	// return all ok
	return TNC_RESULT_SUCCESS;
}
