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

#ifndef CLAMAVIMCLIBRARY_H_
#define CLAMAVIMCLIBRARY_H_

#include <imunit/imc/IMCLibrary.h>

// FHH IANA PEN
#define TNC_VENDORID_FHH ((TNC_VendorID) 0x0080ab)
// message subtype
#define TNC_SUBTYPE_FHH_CLAMAV ((TNC_MessageSubtype) 0x41)
// message type = vendorID + message subtype
#define TNC_MESSAGETYPE_FHH_CLAMAV ((TNC_VENDORID_FHH << 8) | (TNC_SUBTYPE_FHH_CLAMAV & 0xff))
// number of message types the IMC is interested in
#define MESSAGE_TYPE_COUNT 1

/* names of configuration options (according to clamavimc.conf) */
#define CLAMAVIMC_CONF_CLAMCONF_PATH "ClamconfPath"
#define CLAMAVIMC_CONF_CLAMD_SOCKET "ClamdSocket"

/**
 * ClamavIMCLibrary
 */
class ClamavIMCLibrary : public tncfhh::iml::IMCLibrary{
public:
	/**
	 * Ctor. Sets all attributes.
	 */
	ClamavIMCLibrary();

	/**
	 * Returns a pointer to a instance of ClamavIMC.
	 */
	virtual tncfhh::iml::AbstractIMC *createNewImcInstance(TNC_ConnectionID conID);

	/**
	 * Dtor.
	 */
	virtual ~ClamavIMCLibrary();

	/**
	 * Enum that represents all values for the Operational Status of clamd.
	 */
	enum OperationalStatus{
		UNKNOWN,
		NOT_INSTALLED,
		INSTALLED_NOT_OPERATIONAL,
		OPERATIONAL,
		RESERVED
	};
};

#endif /* CLAMAVIMCLIBRARY_H_ */
