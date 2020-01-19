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

#include "ExampleIMVLibrary.h"
#include "ExampleIMV.h"

#include <log4cxx/logger.h>

static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("IMUnit.IMUnitLibrary.IMCLibrary.ExampleIMVLibrary"));

// TNC@FHH IMCLibrary Initialization +
// implement IF-IMC c-functions
TNCFHH_IMVLIBRARY_INITIALIZE(ExampleIMVLibrary) ;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
ExampleIMVLibrary::ExampleIMVLibrary()
{
	LOG4CXX_INFO(logger, "Load ExampleIMV library ");

	/* set all attributes inherited from tncfhh::iml::IMCLibrary */
	// the library name for logging
	this->imUnitLibraryName = "ExampleIMV";
	// add an messageType comprise Vendor ID (IANA PEN) and MessageSubtype
	this->addMessageType(VENDOR_ID, MESSAGE_SUBTYPE);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
tncfhh::iml::AbstractIMV *ExampleIMVLibrary::createNewImvInstance(TNC_ConnectionID conID)
{
	LOG4CXX_TRACE(logger, "createNewImvInstance( " << conID << ")");

	// just return a new instance of ExampleIMV
	return new ExampleIMV(conID, this);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
ExampleIMVLibrary::~ExampleIMVLibrary()
{
	// if necessary delete memory
}
