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
#include "Policy.h"
#include <log4cxx/logger.h>

namespace tncfhh {

namespace iel {

/* for logging */
static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("TNCS.Policy"));

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *                             Policy::Policy()                              *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
Policy::Policy()
{
	LOG4CXX_TRACE(logger, "Constructor Policy");
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *                             Policy::~Policy()                             *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
Policy::~Policy()
{
	LOG4CXX_TRACE(logger, "Destructor Policy");
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *                    void Policy::resetPolicy()                             *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Policy::resetPolicy()
{
	/* Do nothing. */ // Todo - Policy::resetPolicy
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *                 Policy::getActionRecommendation()                         *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_IMV_Action_Recommendation Policy::getActionRecommendation(const std::list<IMV *> &imvs)
{
	LOG4CXX_TRACE(logger, "getActionRecommendation");

	bool accessAllow = true;
	bool accessIsolate = true;

	/* check all IMVs have provided recommendation and compute overall recommendation */
	for (std::list<IMV*>::const_iterator iter = imvs.begin(); iter != imvs.end(); ++iter)
	{
		if (!(*iter)->hasProvideRecommendation())
		{
			// last try to call solicitRecommendation
			LOG4CXX_DEBUG(logger, "IMV " << (*iter)->getIMVProperties()->getName() << " connection " << (*iter)->getConnectionID() << " has not provided recommendation yet. Last try calling solicitRecommendation.");
			(*iter)->solicitRecommendation();
		}

		TNC_IMV_Action_Recommendation imvActionRecommendation;

		if (!(*iter)->hasProvideRecommendation())
		{
			/* WARNING imv has not provided recommendation */
			LOG4CXX_WARN(logger, "IMV " << (*iter)->getIMVProperties()->getName() << " connection " << (*iter)->getConnectionID() << " has ultimately not provided recommendation.");
			imvActionRecommendation = TNC_IMV_ACTION_RECOMMENDATION_NO_RECOMMENDATION;
		} else {
			LOG4CXX_DEBUG(logger, "IMV " << (*iter)->getIMVProperties()->getName() << " connection " << (*iter)->getConnectionID()
					<< " has provided recommendation " << (*iter)->getRecommendation() << " and evaluation " << (*iter)->getEvaluation());
			imvActionRecommendation = (*iter)->getRecommendation();
		}

		// incorporate single recommendation to overall result
		accessAllow &= (imvActionRecommendation == TNC_IMV_ACTION_RECOMMENDATION_ALLOW);
		accessIsolate &= ((imvActionRecommendation == TNC_IMV_ACTION_RECOMMENDATION_ISOLATE) | (imvActionRecommendation == TNC_IMV_ACTION_RECOMMENDATION_ALLOW));
	}

	// special case if there are no IMVs -> access none
	if (imvs.size() == 0)
		accessAllow = accessIsolate = false;

	if (accessAllow)
		return TNC_IMV_ACTION_RECOMMENDATION_ALLOW;

	if (accessIsolate)
		return TNC_IMV_ACTION_RECOMMENDATION_ISOLATE;

	// if (accessNone)
	return TNC_IMV_ACTION_RECOMMENDATION_NO_ACCESS;

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *       void Policy::isHandshakeFinished(TNCCSBatch&, std::list<IMV*>)      *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//void Policy::isHandshakeFinished(TNCCSBatch & outgoingTnccsBatch,  std::list<IMV*> imvs)
//{
//	TNCLog &log = TNCLog::getLog(CLASSNAME, "isHandshakeFinished");
//
//	if (outgoingTnccsBatch.getImcImvMessages().size() == 0)
//		handshakeIsFinished(outgoingTnccsBatch, imvs);
//
//	log.info("Handshake is not finished");
//}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *      void Policy::handshakeIsFinished(TNCCSBatch&, std::list<IMV*>&)      *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//void Policy::handshakeIsFinished(TNCCSBatch & outgoingTnccsBatch, std::list<IMV*> & imvs)
//{
//	TNCLog &log = TNCLog::getLog(CLASSNAME, "handshakeIsFinished");
//
//	outgoingTnccsBatch.deleteAllMessages();
//
//	xercesc::DOMImplementation * impl = xercesc::DOMImplementationRegistry::getDOMImplementation(XercesString("LS").c_str());
//	if (!impl)
//		throw TNCUtil::exception::Exception("Policy::handshakeIsFinished: Xerces error: No DOMImplementation LS found!");
//	xercesc::DOMDocument * doc = impl->createDocument();
//
//	xercesc::DOMElement * xml = doc->createElement(XercesString("TNCCS-Recommendation").c_str());
//	TNC_MessageType messageType = 0x01;
//
//
//	bool accessAllowed = true;
//	bool accessIsolated = true;
//
//	/* check all IMVs has provide recommendation an calculate access */
//	for (std::list<IMV*>::iterator iter = imvs.begin();
//	     iter != imvs.end();
//	     ++iter)
//	{
//		if (!(*iter)->hasProvideRecommendation()) {
//			(*iter)->solicitRecommendation();
//		}
//
//		TNC_IMV_Action_Recommendation imvActionRecommendation;
//
//		if (!(*iter)->hasProvideRecommendation()) {
//			/* WARNING imv has no provide recommendation */
//			log.warn("IMV %s has not provided recommendation", (*iter)->getProperties().getName().c_str());
//			imvActionRecommendation = TNC_IMV_ACTION_RECOMMENDATION_NO_RECOMMENDATION;
//		} else {
//			log.debug("IMV %s has provided recommendation: %lu and evaluation: %lu", (*iter)->getProperties().getName().c_str(), (*iter)->getRecommendation(), (*iter)->getEvaluation());
//			imvActionRecommendation = (*iter)->getRecommendation();
//		}
//
//		accessAllowed  &= imvActionRecommendation==TNC_IMV_ACTION_RECOMMENDATION_ALLOW;
//		accessIsolated &= ((imvActionRecommendation==TNC_IMV_ACTION_RECOMMENDATION_ISOLATE)|(imvActionRecommendation==TNC_IMV_ACTION_RECOMMENDATION_ALLOW));
//	}
//	if (imvs.size() == 0)
//		accessAllowed = accessIsolated = false;
//
//
//	if (accessAllowed) {
//		/* acces allowed */
//		xml->setAttribute(XercesString("type").c_str(), XercesString("allow").c_str());
//
//		outgoingTnccsBatch.addTNCCTNCSMessage(new TNCCTNCSMessageXML(messageType, doc, xml));
//
//	    /* inform all IMV about access allowed */
//	    for (std::list<IMV*>::iterator iter = imvs.begin();
//	         iter != imvs.end();
//	         ++iter) {
//	    	(*iter)->notifyConnectionChange(TNC_CONNECTION_STATE_ACCESS_ALLOWED);
//	    }
//
//	    throw NAATNCS::exception::ConnectionStateException("Access allowed", TNC_CONNECTION_STATE_ACCESS_ALLOWED, outgoingTnccsBatch.getNewNalTnccsBatch());
//	}
//
//
//	if (accessIsolated) {
//		/* acces isolated */
//		xml->setAttribute(XercesString("type").c_str(), XercesString("isolate").c_str());
//
//		outgoingTnccsBatch.addTNCCTNCSMessage(new TNCCTNCSMessageXML(messageType, doc, xml));
//
//	    /* inform all IMV about access isolated */
//	    for (std::list<IMV*>::iterator iter = imvs.begin();
//	         iter != imvs.end();
//	         ++iter) {
//	    	(*iter)->notifyConnectionChange(TNC_CONNECTION_STATE_ACCESS_ISOLATED);
//	    }
//
//		throw NAATNCS::exception::ConnectionStateException("Access isolated", TNC_CONNECTION_STATE_ACCESS_ISOLATED, outgoingTnccsBatch.getNewNalTnccsBatch());
//	}
//
//	/* no acces allowed */
//	xml->setAttribute(XercesString("type").c_str(), XercesString("none").c_str());
//
//	outgoingTnccsBatch.addTNCCTNCSMessage(new TNCCTNCSMessageXML(messageType, doc, xml));
//
//    /* inform all IMV about access none */
//    for (std::list<IMV*>::iterator iter = imvs.begin();
//         iter != imvs.end();
//         ++iter) {
//    	(*iter)->notifyConnectionChange(TNC_CONNECTION_STATE_ACCESS_NONE);
//    }
//
//    throw NAATNCS::exception::ConnectionStateException("Access none", TNC_CONNECTION_STATE_ACCESS_NONE, outgoingTnccsBatch.getNewNalTnccsBatch());
//}

} // namespace iel

} // namespace tncfhh
