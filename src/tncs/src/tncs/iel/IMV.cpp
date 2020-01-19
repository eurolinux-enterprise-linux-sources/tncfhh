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
#include "IMV.h"
#include <log4cxx/logger.h>
#include <iomanip>

namespace tncfhh {

namespace iel {

/* for logging */
static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("TNCS.IMV"));


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *                IMV::IMV(TNC_ConnectionID, IMVProperties&)                 *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
IMV::IMV(TNC_ConnectionID conID, IMVProperties *imvProperties)
	:conID(conID), imvProperties(imvProperties), inReceiveMessage(false),
	inSolicitRecommendation(false), inBatchEnding(false),
	isProvideRecommendationSet(false), error(false),
	recommendation(TNC_IMV_ACTION_RECOMMENDATION_NO_RECOMMENDATION),
	evaluation(TNC_IMV_EVALUATION_RESULT_DONT_KNOW)
{
	LOG4CXX_DEBUG(logger, "Creating IMV instance for IMVProperties " << this->imvProperties->getName() << " for connection " << conID);
	// call libIMV.so
	this->notifyConnectionChange(TNC_CONNECTION_STATE_CREATE);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *                                IMV::~IMV()                                *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
IMV::~IMV()
{
	LOG4CXX_TRACE(logger, "destructor for IMV instance " << this->imvProperties->getName() << " connection " << this->conID);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *           void IMV::notifyConnectionChange(TNC_ConnectionState)           *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void IMV::notifyConnectionChange(TNC_ConnectionState connectionState)
{
	LOG4CXX_TRACE(logger, "notifyConnectionChange( " << connectionState << ") for IMV " << this->imvProperties->getName() << " connection " << this->conID);
	
	/* if the connection state is handshake, then reset the error and recommendation flags*/
	if (connectionState == TNC_CONNECTION_STATE_HANDSHAKE)
	{
		this->error = false;
        this->recommendation = TNC_IMV_ACTION_RECOMMENDATION_NO_RECOMMENDATION;
        this->evaluation = TNC_IMV_EVALUATION_RESULT_DONT_KNOW;
        this->isProvideRecommendationSet = false;
	}
	
	/* if IMV has an error, don't call the function */
	if (this->error)
	{
		LOG4CXX_WARN(logger, "Not calling notifyConnectionChange for IMV " << this->imvProperties->getName() << ". IMV instance has an error.");
		return;
	}
	
	/* call function on IMVProperties */
	this->inNotifyConnectionChange = true;
	LOG4CXX_TRACE(logger, "call notifyConnectionChange for IMV " << this->imvProperties->getName() << ", newState is " << connectionState);
	TNC_Result result = this->imvProperties->call_TNC_IMV_NotifyConnectionChange(this->conID, connectionState);
	this->inNotifyConnectionChange = false;

	/* check result */
	if (result != TNC_RESULT_SUCCESS)
	{
		LOG4CXX_WARN(logger, "error in call notifyConnectionChange for IMV " << this->imvProperties->getName() << " connection " << this->conID << " . Result is " << result);
		this->handleOtherError();
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void IMV::receiveMessage(TNC_BufferReference message, TNC_UInt32 messageLength, TNC_MessageType messageType)
{
	LOG4CXX_TRACE(logger, "receiveMessage for IMV " << this->imvProperties->getName());

	/* if IMV has an error, don't call the function */
	if (this->error)
	{
		LOG4CXX_WARN(logger, "Not calling receiveMessage for IMV " << this->imvProperties->getName() << ". IMV instance has an error.");
		return;
	}

	/* call function in IMVProperties */
	this->inReceiveMessage = true;
	LOG4CXX_TRACE(logger, "call receiveMessage for IMV " << this->imvProperties->getName() << ", length is " << messageLength << " messageType is 0x" << std::setw(8) << std::setfill('0') << std::hex << messageType);
	TNC_Result result = this->imvProperties->call_TNC_IMV_ReceiveMessage(this->conID, message, messageLength, messageType);
	this->inReceiveMessage = false;

	/* check result */
	if (result != TNC_RESULT_SUCCESS)
	{
		LOG4CXX_WARN(logger, "error in call receiveMessage for IMV " << this->imvProperties->getName() << " connection " << this->conID << " . Result is " << result);
		this->handleOtherError();
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *                     void IMV::solicitRecommendation()                     *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void IMV::solicitRecommendation()
{
	LOG4CXX_TRACE(logger, "solicitRecommendation for IMV " << this->imvProperties->getName());
	
	/* if IMV has an error, don't call the function */
	if (this->error)
	{
		LOG4CXX_WARN(logger, "Not calling solicitRecommendation for IMV " << this->imvProperties->getName() << ". IMV instance has an error.");
		return;
	}

	/* call function on libIMV.so */
	this->inSolicitRecommendation = true;
	LOG4CXX_TRACE(logger, "call solicitRecommendation for IMV " << this->imvProperties->getName() << "(id=" << this->imvProperties->getID() << ") and connection " << this->conID);
	TNC_Result result = this->imvProperties->call_TNC_IMV_SolicitRecommendation(this->conID);
	this->inSolicitRecommendation = false;

	/* check result */
	if (result != TNC_RESULT_SUCCESS)
	{
		LOG4CXX_WARN(logger, "error in call solicitRecommendation for IMV " << this->imvProperties->getName() << " connection " << this->conID << " . Result is " << result);
		this->handleOtherError();
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *                          void IMV::batchEnding()                          *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void IMV::batchEnding()
{
	LOG4CXX_TRACE(logger, "batchEnding for IMV " << this->imvProperties->getName() << ", connection is " << this->conID);

	/* if IMV has an error, don't call the function */
	if (this->error)
	{
		LOG4CXX_WARN(logger, "Not calling batchEnding for IMV " << this->imvProperties->getName() << " connection " << this->conID << ". IMV instance has an error.");
		return;
	}

	/* call funtion on libIMV.so */
	this->inBatchEnding = true;
	LOG4CXX_TRACE(logger, "call batchEnding for IMV " << this->imvProperties->getName() << "(id=" << this->imvProperties->getID() << ") and connection " << this->conID);
	TNC_Result result = this->imvProperties->call_TNC_IMV_BatchEnding(this->conID);
	this->inBatchEnding = false;

	/* check result */
	if (result != TNC_RESULT_SUCCESS)
	{
		LOG4CXX_WARN(logger, "error in call batchEnding for IMV " << this->imvProperties->getName() << " connection " << this->conID << " . Result is " << result);
		this->handleOtherError();
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *                   bool IMV::isInNotifyConnectionChange()                  *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool IMV::isInNotifyConnectionChange()
{
	return this->inNotifyConnectionChange;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *                       bool IMV::isInReceiveMessage()                      *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool IMV::isInReceiveMessage()
{
	return this->inReceiveMessage;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *                   bool IMV::isInSolicitRecommendation()                   *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool IMV::isInSolicitRecommendation()
{
	return this->inSolicitRecommendation;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *                        bool IMV::isInBatchEnding()                        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool IMV::isInBatchEnding()
{
	return this->inBatchEnding;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *                    bool IMV::hasProvideRecommendation()                   *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool IMV::hasProvideRecommendation()
{
	return this->isProvideRecommendationSet;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *      void IMV::setProvideRecommendation(TNC_IMV_Action_Recommendation,    *
 *                             TNC_IMV_Evaluation_Result)                    *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void IMV::setProvideRecommendation(TNC_IMV_Action_Recommendation recommendation, TNC_IMV_Evaluation_Result evaluation)
{
	this->recommendation = recommendation;
	this->evaluation = evaluation;
	this->isProvideRecommendationSet = true;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *          TNC_IMV_Action_Recommendation IMV::getRecommendation()           *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_IMV_Action_Recommendation IMV::getRecommendation()
{
	return this->recommendation;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *              TNC_IMV_Evaluation_Result IMV::getEvaluation()               *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_IMV_Evaluation_Result IMV::getEvaluation()
{
	return this->evaluation;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *                const IMVProperties & IMV::getProperties()                 *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
const IMVProperties *IMV::getIMVProperties()
{
	return this->imvProperties;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *                            bool IMV::hasError()                           *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool IMV::hasError() const
{
	return this->error;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *                   TNC_ConnectionID IMV::getConnectionID()                 *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_ConnectionID IMV::getConnectionID()
{
	return this->conID;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *                     void IMV::handleOtherError()                          *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void IMV::handleOtherError()
{
	// NOT_INITIALIZED and FATAL errors are handled by IMVProperties
	// any other error is treated as TNC_RESULT_OTHER, causing a permanent error
	// for this handshake on this connection
	// try to call notifyConnectionChange(DELETE), ignore return value
	this->imvProperties->call_TNC_IMV_NotifyConnectionChange(this->conID, TNC_CONNECTION_STATE_DELETE);
	// set error flag. can only be reseted by calling notifyConnectionChange(HANDSHAKE)
	this->error = true;
    this->recommendation = TNC_IMV_ACTION_RECOMMENDATION_NO_RECOMMENDATION;
    this->evaluation = TNC_IMV_EVALUATION_RESULT_ERROR;
    this->isProvideRecommendationSet = true;
}

} // namespace iel

} // namespace tncfhh
