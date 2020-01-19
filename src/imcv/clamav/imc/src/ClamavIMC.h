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

#ifndef CLAMAVIMC_H_
#define CLAMAVIMC_H_

#include <imunit/imc/AbstractIMC.h>
#include "ClamavIMCLibrary.h"
#include <string>
#include <sstream>

// this file is created by running cmake
#include <clamavimcConfig.h>

/**
 * ClamavIMC.
 *
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>06.01.2010 - create class (ib)</li>
 * </ul>
 *
 * @date 06.01.2010
 * @author Ingo Bente (ib)
 */
class ClamavIMC: public tncfhh::iml::AbstractIMC
{
public:
	/**
	 * Ctor.
	 */
	ClamavIMC(TNC_ConnectionID conID, ClamavIMCLibrary *pClamavIMCLibrary);

	/**
	 * Dtor.
	 */
	virtual ~ClamavIMC();

	/**
	 * beginHandshake
	 */
    virtual TNC_Result beginHandshake();

    /**
     * receiveMessage
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
     * Reads the clamavimc.conf configuration file.
     */
    void readConfiguration();

    /**
     * Checks the operational status of Clamav. This is done by sending the
     * 'PING' command to the clamd socket. If clamd is currently running, a
     * 'PONG' is returned. The result is saved in this->resulOperationalStatus.
     */
    void checkOperationalStatus();

    /**
     * Executes the 'clamconf' command in a new process. The entire output of
     * this call is saved in this->resultClamconf.
     */
    void checkClamconf();

    /**
     * Parses the output of the check* methods and fills the this->out stream
     * accordingly.
     */
    void parseResults();

    /**
     * Controls the measurement process of the IMC. Calls
     * - readConfiguration(),
     * - checkOperationalStatus(),
     * - checkClamconf(),
     * - parseResults()
     */
    void measure();

    /**
     * Path to clamconf
     */
    std::string clamconfPath;

    /**
     * Path to clamd socket
     */
    std::string clamdSocketPath;

    /**
     * Result of operational status check
     */
    ClamavIMCLibrary::OperationalStatus resultOperationalStatus;

    /**
     * Result of clamconf execution
     */
    std::string resultClamconf;

    /**
     * Stream for the message that is sent to the IMV.
     * Content depends on the last execution of the check* methods.
     */
    std::stringstream out;

};

#endif /* CLAMAVIMC_H_ */
