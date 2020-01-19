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

#ifndef EXAMPLEIMVLIBRARY_H_
#define EXAMPLEIMVLIBRARY_H_

#include <imunit/imv/IMVLibrary.h>

/* define Vendor ID (see IANA PEN). Should change this ID */
#define VENDOR_ID 0x0080ab
/* define Messagesubtype */
#define MESSAGE_SUBTYPE 0xfe

/**
 * ExampleIMVLibrary.
 *
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>19.08.2009 - create class (mbs)</li>
 * </ul>
 *
 * @date 19.08.2009
 * @author Mike Steinmetz (mbs)
 */
class ExampleIMVLibrary : public tncfhh::iml::IMVLibrary{
public:
	/**
	 * Ctor. Sets all attributes.
	 */
	ExampleIMVLibrary();

	/**
	 * Returns a pointer to a instance of ExampleIMV.
	 */
	virtual tncfhh::iml::AbstractIMV *createNewImvInstance(TNC_ConnectionID conID);

	/**
	 * Dtor.
	 */
	virtual ~ExampleIMVLibrary();
};

#endif /* EXAMPLEIMVLIBRARY_H_ */
