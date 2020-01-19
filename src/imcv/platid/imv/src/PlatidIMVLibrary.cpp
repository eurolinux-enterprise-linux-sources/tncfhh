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

#include "PlatidIMVLibrary.h"
#include "PlatidIMV.h"
#include "FileCertManager.h"

/* logging */
#include <log4cxx/logger.h>
using namespace log4cxx;



TNCFHH_IMVLIBRARY_INITIALIZE(PlatidIMVLibrary);



static LoggerPtr
logger(Logger::getLogger("IMUnit.IMUnitLibrary.IMVLibrary.PlatidIMVLibrary"));


PlatidIMVLibrary::PlatidIMVLibrary()
{
	this->imUnitLibraryName = "PlatidIMVLibrary";
	this->addMessageType(TNC_VENDORID_FHH, TNC_SUBTYPE_FHH_PLATID);
	this->certManager = new FileCertManager(PLATIDIMV_KNOWN_CERTS_FILENAME);
}

PlatidIMVLibrary::~PlatidIMVLibrary()
{
	LOG4CXX_TRACE(logger, "~PlatidIMVLibrary()");
	if (certManager != NULL)
	{
		LOG4CXX_TRACE(logger, "Deleting Certmanager...");
		delete certManager;
		certManager = NULL;
	}
}

AbstractIMV * PlatidIMVLibrary::createNewImvInstance(TNC_ConnectionID connid)
{
	return new PlatidIMV(connid, this, certManager);
}
