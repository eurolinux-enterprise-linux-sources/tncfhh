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


#include "AbstractIMV.h"

#include <log4cxx/logger.h>

using namespace log4cxx;

namespace tncfhh {

namespace iml {

static LoggerPtr logger(Logger::getLogger("IMUnit.AbstractIMUnit.AbstractIMV"));

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
AbstractIMV::AbstractIMV(TNC_ConnectionID conID, IMVLibrary *pImvLibrary)
	:AbstractIMUnit(conID), tncs(conID, pImvLibrary),
	actionRecommendation(TNC_IMV_ACTION_RECOMMENDATION_NO_RECOMMENDATION),
	evaluationResult(TNC_IMV_EVALUATION_RESULT_ERROR),
	validationFinished(false)
{
    // intentionally left blank
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
AbstractIMV::~AbstractIMV()
{
    // intentionally left blank
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_Result AbstractIMV::notifyConnectionChange(TNC_ConnectionState newState)
{
	LOG4CXX_TRACE(logger, "notifyConnectionChange new state = " << newState);

    if (newState == TNC_CONNECTION_STATE_HANDSHAKE || newState == TNC_CONNECTION_STATE_CREATE) {
        actionRecommendation = TNC_IMV_ACTION_RECOMMENDATION_NO_RECOMMENDATION;
        evaluationResult = TNC_IMV_EVALUATION_RESULT_DONT_KNOW;
        validationFinished = false;
    }

    return AbstractIMUnit::notifyConnectionChange(newState);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_Result AbstractIMV::solicitRecommendation()
{
	LOG4CXX_TRACE(logger, "solicitRecommendation");

    tncs.provideRecommendation(this->actionRecommendation, this->evaluationResult);

	return TNC_RESULT_SUCCESS;
}

}  // namespace iml

}  // namespace tncfhh
