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
#include "AbstractTNCCSProtocol.h"
#include <log4cxx/logger.h>

namespace tncfhh {

namespace iel {

/* for logging */
static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("TNCS.AbstractTNCCSProtocol"));

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
AbstractTNCCSProtocol::AbstractTNCCSProtocol(const std::map<TNC_IMVID, IMV*> &imvsMap)
:imvs(imvsMap)
{
	//Do nothing? Really? Yes! NO! YES!
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
AbstractTNCCSProtocol::~AbstractTNCCSProtocol() {
	//Do nothing, too.
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
std::string AbstractTNCCSProtocol::getProtocolName() const
{
	return this->protocolName;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//void AbstractTNCCSProtocol::setIMVs(const std::map<TNC_IMVID, IMV*> &imvsMap)
//{
//
//    std::map<TNC_IMVID, IMV*>::const_iterator iter = imvsMap.begin();
//    while (iter!=imvsMap.end())
//    {
//    	if (!(iter->second))
//        {
//    		// ignore NULL
//        	LOG4CXX_WARN(logger, "Uhoh strange things happening...imv instance == NULL");
//        	iter++;
//        	continue;
//        }
//
//    	LOG4CXX_DEBUG(logger, "Adding IMV " << (*iter).second->getIMVProperties().getName() << " to TNCCSProtocol " << getProtocolName());
//
//        this->imvs.push_back(iter->second);
//
//       	iter++;
//     }
//}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void AbstractTNCCSProtocol::notifyConnectionChangeHandshake()
{
	// TODO AbstractTNCCSProtocol::notifyConnectionChangeHandshake()
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNCCSData AbstractTNCCSProtocol::processTNCCSData(TNCCSData incomingTNCCSData) throw (ConnectionStateException, TNCCSProtocolNotSupportedException)
{
	throw TNCCSProtocolNotSupportedException("AbstractTNCCSProtocol does not support anything.");
}

} // namespace iel

} // tncfhh
