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

#include "DummyIMC.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <log4cxx/logger.h>

using namespace log4cxx;

static LoggerPtr logger(Logger::getLogger("IMUnit.AbstractIMUnit.AbstractIMC.DummyIMC"));

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
DummyIMC::DummyIMC(TNC_ConnectionID conID, DummyIMCLibrary *pDummyIMCLibrary)
	:AbstractIMC(conID, pDummyIMCLibrary), localFileAction(""), count(0)
{
	//
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
DummyIMC::~DummyIMC()
{
	//
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_Result DummyIMC::beginHandshake()
{
	LOG4CXX_TRACE(logger, "beginHandshake()");
	// reset counter
	this->count = 0;
	// read local file
	std::ifstream dummyIMCfile(IMC_CONFIG);
	if(!dummyIMCfile)
	{
		LOG4CXX_DEBUG(logger, "could not open dummy_imc_file: " << IMC_CONFIG << ". Using isolate as recommendation." );
		this->localFileAction = "isolate";
	} else {
		getline(dummyIMCfile, this->localFileAction);
		if( this->localFileAction.compare("allow") != 0 &&
			this->localFileAction.compare("isolate") != 0 &&
			this->localFileAction.compare("none") != 0)
		{
			LOG4CXX_DEBUG(logger, "recommendation from " << IMC_CONFIG << " not valid. Using isolate as recommendation.");
			this->localFileAction = "isolate";
		}
		dummyIMCfile.close();
	}
	std::stringstream ss;
	ss << "DummyIMC message " << this->count << ", ";
	ss << "action = " << this->localFileAction;
	std::string sendString = ss.str();
	LOG4CXX_TRACE(logger, "Send Message: " << sendString);
	this->tncc.sendMessage((unsigned char*)sendString.c_str(), sendString.size(), TNC_MESSAGETYPE_FHH_DUMMY);
	return TNC_RESULT_SUCCESS;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_Result DummyIMC::receiveMessage(TNC_BufferReference message,
		                          TNC_UInt32 messageLength,
		                          TNC_MessageType messageType)
{
	LOG4CXX_TRACE(logger, "Received Message: " << message);
	this->count++;
	std::stringstream ss;
	ss << "DummyIMC message " << this->count << ", ";
	ss << "action = " << this->localFileAction;

	std::string sendString = ss.str();

	LOG4CXX_TRACE(logger, "Send Message: " << sendString);
	this->tncc.sendMessage((unsigned char*)sendString.c_str(), sendString.size(), TNC_MESSAGETYPE_FHH_DUMMY);

	return TNC_RESULT_SUCCESS;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_Result DummyIMC::batchEnding()
{
	LOG4CXX_TRACE(logger, "batchEnding");
	return TNC_RESULT_SUCCESS;
}
