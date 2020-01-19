/*
 * This software is Copyright (C) 2006-2010
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

#include "AttestationIMVLibrary.h"
#include "AttestationIMV.h"

/* logging */
#include <log4cxx/logger.h>
using namespace log4cxx;


TNCFHH_IMVLIBRARY_INITIALIZE(AttestationIMVLibrary);


static LoggerPtr
logger(Logger::getLogger("IMUnit.IMUnitLibrary.IMVLibrary.AttestationIMVLibrary"));


AttestationIMVLibrary::AttestationIMVLibrary()
{
	this->imUnitLibraryName = "AttestationIMVLibrary";
	this->addMessageType(TNC_VENDORID_FHH, TNC_SUBTYPE_FHH_ATTESTATION);
	this->policyManager = new AttestationIMVPolicyManager(IMV_CONFIG);
}

AttestationIMVLibrary::~AttestationIMVLibrary()
{
	LOG4CXX_TRACE(logger, "~AttestationIMVLibrary()");
	if (policyManager != NULL){
		delete policyManager;
		policyManager = NULL;
	}
}

AbstractIMV * AttestationIMVLibrary::createNewImvInstance(TNC_ConnectionID connid)
{
	return new AttestationIMV(connid, this, policyManager);
}
