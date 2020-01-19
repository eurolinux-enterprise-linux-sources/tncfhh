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


#ifndef TNCFHH_IML_ABSTRACTIMV_H_
#define TNCFHH_IML_ABSTRACTIMV_H_

#include "../AbstractIMUnit.h"
#include "TNCS.h"

namespace tncfhh {

namespace iml {

// Prototyp instead of include
class IMVLibrary;

/**
 * AbstractIMV represents the abstract super class for any concrete IMV implementation. It manages
 * the current connectionState and provides helper functions for parsing message types.
 *
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>09.05.2006 - create class (Daniel Wuttke)</li>
 *   <li>09.02.2008 - add tncs and remove all xml (mbs)</li>
 *   <li>08.05.2008 - change namespace and remove old (XML-) code (mbs)</li>
 *   <li>16.06.2009 - redesign 0.6.0 (ib)</li>
 * </ul>
 *
 * @class AbstractIMV
 * @brief Represents the abstract super class for any concrete IMV implementation.
 * @date 09.05.2006
 * @author Daniel Wuttke
 * @author Ingo Bente
 * @author Mike Steinmetz (mbs)
 */
class AbstractIMV : public AbstractIMUnit
{
    public:

    	/**
    	 * Ctor.
    	 *
    	 * @param conID The TNC_ConnectionID for the IMV instance.
    	 */
        AbstractIMV(TNC_ConnectionID conID, IMVLibrary *pImvLibrary);

        /**
         * Dtor.
         */
        virtual ~AbstractIMV();

        /**
		 * Called by TNCS when a recommendation must be provided by the IMV. IMV must call
		 * tncs.provideRecommendation().
		 *
		 * @return TNC_Result
		 */
        virtual TNC_Result solicitRecommendation();

    	/**
         * Sets the current connection state. Initializes also some attributes
         * of AbstractIMV. Calls AbstractIMUnit::notifyConnectionChange().
         *
         * @param newState The new, current connection state.
         */
         virtual TNC_Result notifyConnectionChange(TNC_ConnectionState newState);

    protected:

    	/**
    	 * The TNCS interface.
    	 * With tncs, you can call the Server.
    	 */
    	TNCS tncs;

    	/**
    	 * The calculated action recommendation.
    	 */
    	TNC_IMV_Action_Recommendation actionRecommendation;

    	/**
    	 * The calculated evaluation result.
    	 */
    	TNC_IMV_Evaluation_Result evaluationResult;

    	/**
    	 * Flag that indicates whether the validation has been finished.
    	 */
    	bool validationFinished;

    private:

};

}  // namespace iml

}  // namespace tncfhh

#endif /*TNCFHH_IML_ABSTRACTIMV_H_*/
