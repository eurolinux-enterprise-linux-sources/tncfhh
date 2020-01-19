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

#ifndef DUMMYIMC_H_
#define DUMMYIMC_H_

#include <imunit/imc/AbstractIMC.h>
#include "DummyIMCLibrary.h"

// this file is created by running cmake
#include <dummyimcConfig.h>

/**
 * DummyIMC.
 *
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>12.01.2009 - create class (ib)</li>
 *   <li>19.06.2009 - redesign 0.6.0 (ib)</li>
 * </ul>
 *
 * @date 12.01.2009
 * @author Ingo Bente (ib)
 */
class DummyIMC: public tncfhh::iml::AbstractIMC
{
public:
	/**
	 * Ctor.
	 */
	DummyIMC(TNC_ConnectionID conID, DummyIMCLibrary *pDummyIMCLibrary);

	/**
	 * Dtor.
	 */
	virtual ~DummyIMC();

	/**
	 * beginHandshake
	 */
    virtual TNC_Result beginHandshake();

    /**
     * receive Message
     */
    virtual TNC_Result receiveMessage(TNC_BufferReference message,
    		                          TNC_UInt32 messageLength,
    		                          TNC_MessageType messageType);

    /**
     * batchEnding
     */
    virtual TNC_Result batchEnding();
protected:
	/**
	 * value read from DUMMY_IMC_FILE
	 */
	std::string localFileAction;

	/**
	 * Counter for number of messages send to IMV.
	 */
	unsigned int count;
};

#endif /* DUMMYIMC_H_ */
