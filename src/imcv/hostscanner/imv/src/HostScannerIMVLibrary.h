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
#ifndef HOSTSCANNERIMVLIBRARY_H_
#define HOSTSCANNERIMVLIBRARY_H_

#include <imunit/imv/IMVLibrary.h>

// FHH IANA PEN
#define TNC_VENDORID_FHH ((TNC_VendorID) 0x0080ab)
// message subtype
#define TNC_SUBTYPE_FHH_HOSTSCANNER ((TNC_MessageSubtype) 0x30)
// message type = vendorID + message subtype
#define TNC_MESSAGETYPE_FHH_HOSTSCANNER ((TNC_VENDORID_FHH << 8) | (TNC_SUBTYPE_FHH_HOSTSCANNER & 0xff))
// number of message types the IMC is interested in
#define MESSAGE_TYPE_COUNT 1

class HostScannerIMVLibrary : public tncfhh::iml::IMVLibrary{
public:
	/**
	 * Ctor. Sets all attributes.
	 */
	HostScannerIMVLibrary();

	/**
	 * Returns a pointer to a instance of HostScannerIMV.
	 */
	virtual tncfhh::iml::AbstractIMV *createNewImvInstance(TNC_ConnectionID conID);

	/**
	 * Dtor.
	 */
	virtual ~HostScannerIMVLibrary();
};

#endif /* HostScannerIMVLIBRARY_H_ */
