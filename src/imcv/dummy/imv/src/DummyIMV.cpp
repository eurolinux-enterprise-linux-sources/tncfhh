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

#include "DummyIMV.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <log4cxx/logger.h>
using namespace log4cxx;

static LoggerPtr logger(Logger::getLogger(
		"IMUnit.AbstractIMUnit.AbstractIMV.DummyIMV"));

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
DummyIMV::DummyIMV(TNC_ConnectionID conID, DummyIMVLibrary *pDummyImvLibrary) :
	tncfhh::iml::AbstractIMV(conID, pDummyImvLibrary), msgCountMax(0),
			msgCountCur(0) {
	//
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
DummyIMV::~DummyIMV() {
	//
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_Result DummyIMV::notifyConnectionChange() {
	LOG4CXX_TRACE(logger, "notifyConnectionChange()");
	// check that TNC handshake has started
	if (this->getConnectionState() == TNC_CONNECTION_STATE_HANDSHAKE) {
		std::string line;
		// reset counter for current messages
		this->msgCountCur = 0;
		// open policy file
		std::ifstream policy(IMV_CONFIG, std::ios::in);
		if (!policy) {
			LOG4CXX_DEBUG(logger, "could not open policy file: " << IMV_CONFIG << ". Using 0 as default value for msgCountMax.");
			this->msgCountMax = 0;
		} else {
			// read first line
			getline(policy, line);
			std::stringstream ss(line);

			// save max number of messages to be sent
			ss >> this->msgCountMax;
			if (ss.fail()) {
				LOG4CXX_DEBUG(logger, "could not parse msg count from policy. Using 0 as default value for msgCountMax.")
				this->msgCountMax = 0;
			}
			// close policy file
			policy.close();
		}
	}
	return TNC_RESULT_SUCCESS;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_Result DummyIMV::receiveMessage(TNC_BufferReference message,
		TNC_UInt32 messageLength, TNC_MessageType messageType) {

	// parse message from IMC
	// should look like
	// "DummyIMC message n, action = <access | isolate | none>"
	std::stringstream receive;
	receive.write((const char*) message, messageLength);
	std::string receiveString = receive.str();
	LOG4CXX_TRACE(logger, "Receive Message: " << receiveString)
	size_t pos = receiveString.find_first_of("=");
	std::string action = receiveString.substr(pos + 2, std::string::npos);
	if (!action.compare("allow")) {
		this->actionRecommendation = TNC_IMV_ACTION_RECOMMENDATION_ALLOW;
		this->evaluationResult = TNC_IMV_EVALUATION_RESULT_COMPLIANT;
	}
	if (!action.compare("isolate")) {
		this->actionRecommendation = TNC_IMV_ACTION_RECOMMENDATION_ISOLATE;
		this->evaluationResult = TNC_IMV_EVALUATION_RESULT_NONCOMPLIANT_MINOR;
	}
	if (!action.compare("none")) {
		this->actionRecommendation = TNC_IMV_ACTION_RECOMMENDATION_NO_ACCESS;
		this->evaluationResult = TNC_IMV_EVALUATION_RESULT_NONCOMPLIANT_MAJOR;
	}
	// can we send another message
	if (this->msgCountCur < this->msgCountMax) {
		// send another message to IMV
		this->msgCountCur++;
		std::stringstream send;
		send << "DummyIMV to DummyIMC message " << this->msgCountCur;
		std::string sendString = send.str();
		LOG4CXX_DEBUG(logger, "Send Message: " << sendString)
		this->tncs.sendMessage((unsigned char *) sendString.c_str(),
				sendString.size(), TNC_MESSAGETYPE_FHH_DUMMY);
	}
	// check if necessary amount of messages has been sent
	if (this->msgCountCur == this->msgCountMax) {
		LOG4CXX_DEBUG(logger, "All DummyIMV messages sent. Providing Recommendation: " << this->actionRecommendation << " " << this->evaluationResult)
		this->validationFinished = true;
		this->tncs.provideRecommendation(this->actionRecommendation,
				this->evaluationResult);
	}
	return TNC_RESULT_SUCCESS;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_Result DummyIMV::batchEnding() {
	LOG4CXX_TRACE(logger, "batchEnding()");
	return TNC_RESULT_SUCCESS;
}
