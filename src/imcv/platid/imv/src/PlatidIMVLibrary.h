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

/**
 * PlatidIMVLibrary
 *
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>24.11.2009 - create class skeleton (awe)</li>
 *   <li>08.12.2009 - include path to policy file (awe)</li>
 * </ul>
 *
 * @date 24.11.09
 * @author Arne Welzel (awe)
 */

#ifndef PLATIDIMVLIBRARY_H_
#define PLATIDIMVLIBRARY_H_

#include "tcg/tnc/tncifimc.h"
#include "imunit/imv/IMVLibrary.h"
#include "imunit/imv/AbstractIMV.h"


#include "CertManager.h"
#include "platidimvConfig.h"


#include <string>



#define TNC_VENDORID_FHH 		((TNC_VendorID) 0x0080ab)
/* FIXME: which MessageSubtype? */
#define TNC_SUBTYPE_FHH_PLATID 		((TNC_MessageSubtype) 0x33)
#define TNC_MESSAGETYPE_FHH_PLATID 	((TNC_VENDORID_FHH << 8) | (TNC_SUBTYPE_FHH_PLATID & 0xff))
#define PLATIDIMV_KNOWN_CERTS_FILENAME	IMV_CONFIG


using namespace tncfhh::iml;



class PlatidIMVLibrary : public tncfhh::iml::IMVLibrary
{
public:
	PlatidIMVLibrary();

	~PlatidIMVLibrary();


	AbstractIMV *createNewImvInstance(TNC_ConnectionID connid);


private:
	/* our cert manager */
	CertManager *certManager;

};

#endif // PLATIDIMVLIBRARY_H_
