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

#include "DummyIMVLibrary.h"
#include "DummyIMV.h"

#include <log4cxx/logger.h>

#include <tncfhhConfig.h>

using namespace log4cxx;

static LoggerPtr logger(Logger::getLogger("IMUnit.IMUnitLibrary.IMVLibrary.DummyIMVLibrary"));

// TNC@FHH IMVLibrary Initialization +
// include IF-IMV c-functions defined by TNC@FHH IMUnit package
TNCFHH_IMVLIBRARY_INITIALIZE(DummyIMVLibrary) ;
#include <imunit/imv/IFIMVImpl.cpp>

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
DummyIMVLibrary::DummyIMVLibrary()
{
	LOG4CXX_INFO(logger, "Load DummyIMV library version " << TNCFHH_VERSION_MAJOR << "." << TNCFHH_VERSION_MINOR << "." << TNCFHH_VERSION_PATCH );
	// ...
	this->ifImcImvVersion = TNC_IFIMV_VERSION_1;
	this->imUnitLibraryName = "DummyIMV";
	this->addMessageType(TNC_MESSAGETYPE_FHH_DUMMY);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
tncfhh::iml::AbstractIMV *DummyIMVLibrary::createNewImvInstance(TNC_ConnectionID conID)
{
	LOG4CXX_TRACE(logger, "createNewImcInstance( " << conID << ")");
	return new DummyIMV(conID, this);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
DummyIMVLibrary::~DummyIMVLibrary()
{
	delete[] this->messageTypeList;
	this->messageTypeList = NULL;
}
