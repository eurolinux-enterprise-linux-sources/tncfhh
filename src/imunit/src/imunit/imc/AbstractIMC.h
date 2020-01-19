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

#ifndef TNCFHH_IML_ABSTRACTIMC_H_
#define TNCFHH_IML_ABSTRACTIMC_H_

#include "../AbstractIMUnit.h"
#include "TNCC.h"

namespace tncfhh {

namespace iml {

// Prototype instead of include IMCLibrary.h
class IMCLibrary;

/**
 * AbstractIMC represents the abstract super class for any concrete IMC implementation. It manages
 * the current connectionState and provides helper functions for parsing message types. Furthermore,
 * it declares two abstract methods (begin and receive) which must be implemented by derived classes.
 *
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>09.04.2006 - create class (Daniel Wuttke)</li>
 *   <li>09.02.2008 - add tncc (mbs)</li>
 *   <li>08.05.2008 - change namespace (mbs)</li>
 *   <li>16.06.2009 - redesign 0.6.0 (ib)</li>
 * </ul>
 *
 * @class AbstractIMC
 * @brief Represents the abstract super class for any concrete IMC implementation.
 * @date 09.04.2006
 * @author Daniel Wuttke
 * @author Ingo Bente
 * @author Mike Steinmetz (mbs)
 */
class AbstractIMC : public AbstractIMUnit
{
    private:

    protected:

    	/**
    	 * The TNC part of the IF-IMC interface provided by an instance of TNCC.
    	 * The IMC calls the TNCC <b>only</b> via this attribute.
    	 */
    	TNCC tncc;

    public:

    	/**
    	 * Ctor.
    	 *
    	 * @param conID The TNC_ConnectionID for the IMC instance.
    	 * @param pImcLibrary Pointer to an instance of the concrete IMC library.
    	 */
        AbstractIMC(TNC_ConnectionID conID, IMCLibrary *pImcLibrary);

        /**
         * Dtor.
         */
        virtual ~AbstractIMC();

        /**
         * Invoked after TNC_IMC_BeginHandshake() has been called by TNC client. Has to be implemented
         * by concrete IMC. This method is called to trigger a TNC handshake.
         *
         * @param message The message that shall be sent from IMC to IMV.
         * @param messageType The type of the message
         * @param messageLength The length of the message
         * @return Result code (specified in tncifimc.h) that indicates if the operation was succesful or not.
         */
        virtual TNC_Result beginHandshake() = 0;
};

}  // namespace iml

}  // namespace tncfhh

#endif /*TNCFHH_IML_ABSTRACTIMC_H_*/
