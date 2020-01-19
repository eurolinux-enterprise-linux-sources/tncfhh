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

#include "AbstractIMUnit.h"

#include <log4cxx/logger.h>

using namespace log4cxx;

namespace tncfhh {

namespace iml {

static LoggerPtr logger(Logger::getLogger("IMUnit.AbstractIMUnit"));

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
AbstractIMUnit::AbstractIMUnit(TNC_ConnectionID conID)
	:connectionID(conID), round(0)
{
	// intentionally left blank
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
AbstractIMUnit::~AbstractIMUnit()
{
	// intentionally left blank
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_ConnectionState AbstractIMUnit::getConnectionState() const {
    return connectionState;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_ConnectionID AbstractIMUnit::getConnectionID() const
{
    return connectionID;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_UInt32 AbstractIMUnit::getRound() const
{
    return round;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_Result AbstractIMUnit::notifyConnectionChange(TNC_ConnectionState newState)
{
	LOG4CXX_TRACE(logger, "notifyConnectionChange new state = " << newState);
    // check newState value
    if(newState >= TNC_CONNECTION_STATE_CREATE && newState <= TNC_CONNECTION_STATE_DELETE){
    	connectionState = newState;
    	// call hook method for event notification
    	return notifyConnectionChange();
    } else {
    	return TNC_RESULT_INVALID_PARAMETER;
    }

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_Result AbstractIMUnit::notifyConnectionChange()
{
	LOG4CXX_TRACE(logger, "notifyConnectionChange()");
	return TNC_RESULT_SUCCESS;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_Result AbstractIMUnit::batchEnding()
{
	LOG4CXX_TRACE(logger, "batchEnding()");
	return TNC_RESULT_SUCCESS;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_Result AbstractIMUnit::receiveMessage(TNC_BufferReference message,
		                                  TNC_UInt32 messageLength,
		                                  TNC_MessageType messageType)
{
	LOG4CXX_TRACE(logger, "receiveMessage( " << message << ", " << messageLength << ", " << messageType << ")");
	return TNC_RESULT_SUCCESS;
}

} // namespace iml

} // namespace tncfhh
