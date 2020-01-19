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

#include "SOH1Protocol.h"
#include "../../exception/ConnectionStateException.h"
#include "../../exception/ConnectionStateExceptionWithTNCCSData.h"
#include "../string_helper.h"

#include <log4cxx/logger.h>

namespace tncfhh {

namespace iel {

namespace soh {

/* for logging */
static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("TNCS.TNC1.Protocol"));

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
SOH1Protocol::SOH1Protocol(const std::map<TNC_IMVID, IMV*> &imvsMap)
:AbstractTNCCSProtocol(imvsMap), incoming(TNCCSBatch::TNCS),
outgoing(TNCCSBatch::TNCC)
{
	// Lets rock!
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
SOHProtocol::~SOH1Protocol() {
	// unrockable?!
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void SOH1Protocol::sendMessage(TNC_IMVID imvID, TNC_BufferReference message, TNC_UInt32 messageLength, TNC_MessageType messageType)
{
	// get iterator
	std::map<TNC_IMVID, IMV*>::iterator iter = this->imvs.find(imvID);

	// check imvID
	checkIMVID(imvID, iter);

	// check if receiveMessage | batchEnding has been called for imvID
	if(!iter->second->isInReceiveMessage() && !iter->second->isInBatchEnding()){
		throw std::domain_error(std::string("sendMessage called in wrong state."));
	}

	// TODO call Policy.checkMessage()

	// add message to outgoing batch
	this->outgoing.addIMCIMVMessage(new IMCIMVMessage(message, messageLength, messageType));
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void SOH1Protocol::requestHandshakeRetry(TNC_IMVID imvID, TNC_RetryReason reason)
{
	//TODO - TNC1Protocol - requestHandshakeRetry
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void SOH1Protocol::getAttribute(TNC_IMVID imvID, TNC_AttributeID attributeID, TNC_UInt32 bufferLength, /*out*/ TNC_BufferReference buffer, /*out*/ TNC_UInt32 *pOutValueLength)
{
	//TODO - TNC1Protocol - getAttribute
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void SOH1Protocol::setAttribute(TNC_IMVID imvID,  TNC_AttributeID attributeID, TNC_UInt32 bufferLength, TNC_BufferReference buffer)
{
	//TODO - TNC1Protocol - setAttribute
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNCCSData SOH1Protocol::processTNCCSData(TNCCSData incomingTNCCSData) throw (ConnectionStateException, TNCCSProtocolNotSupportedException)
{
	try {
		// convert TNCSBatch to TNCSData and save it in incoming
		this->incoming = incomingTNCCSData;

		// delete old outgoing batch
		this->outgoing.deleteAllMessages();

		std::list<IMCIMVMessage *> imcImvMessages = this->incoming.getImcImvMessages();
		std::list<IMCIMVMessage *>::iterator iterM = imcImvMessages.begin();
		while(iterM!=imcImvMessages.end()){
			IMCIMVMessage * imcImvMessage = *iterM;

			/*  */
			for (std::map<TNC_IMVID, IMV*>::iterator iterI = this->imvs.begin();
				 iterI != this->imvs.end();
				 ++iterI) {

				if ((iterI->second)->getIMVProperties()->hasMessageType(imcImvMessage->getType()))
					(iterI->second)->receiveMessage(imcImvMessage->getData(), imcImvMessage->getDataLength(), imcImvMessage->getType());
			}
			iterM++;
		}

		// inform all IMV about batchEnding
		for (std::map<TNC_IMVID, IMV*>::iterator iter = this->imvs.begin();
			 iter != this->imvs.end();
			 ++iter) {
			iter->second->batchEnding();
		}

		/* create a list with all IMVs */
		std::list<IMV*> imvs;
		for (std::map<TNC_IMVID, IMV*>::iterator iter = this->imvs.begin();
			 iter != this->imvs.end();
			 ++iter) {
			imvs.push_back(iter->second);
		}


		if (this->outgoing.getImcImvMessages().size() == 0) {
			TNC_IMV_Action_Recommendation recommendation = policy.getActionRecommendation(imvs);
			throw ConnectionStateExceptionWithTNCCSData(recommendation, this->outgoing.getNewTnccsData());
		}

		//Connection::exchangeTNCCSBatch return
		return this->outgoing.getNewTnccsData();
	} catch (std::runtime_error & e) {
		LOG4CXX_ERROR(logger, e.what());
		throw ConnectionStateException(TNC_IMV_ACTION_RECOMMENDATION_NO_RECOMMENDATION);
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void SOH1Protocol::checkIMVID(TNC_IMVID imvID, std::map<TNC_IMVID, IMV *>::iterator &iter) throw (std::domain_error)
{

	// check if imv exists
	if(iter == this->imvs.end()){
		throw std::domain_error(std::string("No IMV for imvID == ") + imvID);
	}
	// check pointer != NULL
	if(iter->second == NULL){
		throw std::domain_error(std::string("IMV for imvID ") + imvID + " == NULL!");
	}
}



}

}

}
