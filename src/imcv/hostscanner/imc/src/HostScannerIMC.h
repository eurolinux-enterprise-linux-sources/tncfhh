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

#ifndef HOSTSCANNERIMC_H_
#define HOSTSCANNERIMC_H_

#include <imunit/imc/AbstractIMC.h>
#include "HostScannerIMCLibrary.h"

/**
 * HostScannerIMC
 *
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>06.05.2006 - create class (Daniel Wuttke)</li>
 *   <li>09.05.2008 - completely redesign (mbs)</li>
 *   <li>19.06.2009 - redesign 0.6.0 (ib)</li>
 *   <li>30.07.2009 - update to 0.6.0 (mbs)</li>
 * </ul>
 *
 * @class HostScannerIMC
 * @date 06.05.2006
 * @author Mike Steinmetz (mbs)
 * @author Daniel Wuttke
 */
class HostScannerIMC : public tncfhh::iml::AbstractIMC
{
private:
	/**
	 * Layer 4 Protocols
	 */
	enum Protocol {TCP, UDP};

	/**
	 * Status of a Port
	 */
	enum Status {open, close};

	/**
	 * Policy is a triple of protocol, port and status
	 */
	class Policy
	{
		public:
			/**
			 * The layer 4 protocol
			 */
			Protocol protocol;

			/**
			 * The port number
			 */
			unsigned short port;

			/**
			 * Status of the port
			 */
			Status status;

			/**
			 * Ctor
			 */
			Policy(Protocol pr, unsigned short po, Status s);
	};

	bool readLine(std::istream *in, char *buf, const int size);

public:
	/**
	 * Ctor
	 */
    HostScannerIMC(TNC_ConnectionID cid, HostScannerIMCLibrary *pHostScannerIMCLibrary);

    /**
     * Dtor
     */
    virtual ~HostScannerIMC();

    /**
     * beginHandshake
     */
    virtual TNC_Result beginHandshake();

    /**
     * receiveMessage
     */
    virtual TNC_Result receiveMessage(TNC_BufferReference message, TNC_UInt32 messageLength, TNC_MessageType messageType);
};

#endif /*HostScannerIMC_H_*/
