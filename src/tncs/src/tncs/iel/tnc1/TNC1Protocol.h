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
#ifndef TNCS_TNC1PROTOCOL_H_
#define TNCS_TNC1PROTOCOL_H_

#include "../AbstractTNCCSProtocol.h"
#include "TNCCSBatch.h"

namespace tncfhh {

namespace iel {

namespace tnc1 {

/**
 * TODO Comment
 *
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>13.07.2009 - create class (mbs)</li>
 * </ul>
 *
 * @class TNC1Protocol
 * @brief TODO Brief
 * @date 13.07.2009
 * @author Mike Steinmetz (mbs)
 */
class TNC1Protocol: public tncfhh::iel::AbstractTNCCSProtocol {
public:
	/*
	 * Default-Ctor.
	 */
	TNC1Protocol(const std::map<TNC_IMVID, IMV*> &imvsMap);

	/*
	 * Default-Dtor.
	 */
	virtual ~TNC1Protocol();

	/**
	 * This function delegates the sendMessage() call to the connectionID specific FlowControl.
	 *
	 * @param imvID
	 * @param message
	 * @param messageLength
	 * @param messageType
	 *
	 * @throw TNCUtil::exception::ResultException
	 *
	 * @see TNC_TNCS_SendMessage()
	 */
	virtual void sendMessage(TNC_IMVID imvID, TNC_BufferReference message, TNC_UInt32 messageLength, TNC_MessageType messageType);

	/**
	 * This function delegates the requestHandshakeRetry() call to the connectionID specific FlowControl.
	 *
	 * @param imvID
	 * @param reason
	 *
	 * @throw TNCUtil::exception::ResultException
	 *
	 * @see TNC_TNCS_RequestHandshakeRetry()
	 */
	virtual void requestHandshakeRetry(TNC_IMVID imvID, TNC_RetryReason reason);

	/**
	 * This function delegates the getAttribute() call to the connectionID specific FlowControl.
	 *
	 * @param imvID
	 * @param attributeID
	 * @param bufferLength
	 * @param buffer [out]
	 * @param pOutValueLength [out]
	 *
	 * @throw TNCUtil::exception::ResultException
	 *
	 * @see TNC_TNCS_GetAttribute()
	 */
	virtual void getAttribute(TNC_IMVID imvID, TNC_AttributeID attributeID, TNC_UInt32 bufferLength, /*out*/ TNC_BufferReference buffer, /*out*/ TNC_UInt32 *pOutValueLength);

	/**
	 * This function delegates the setAttribute() call to the connectionID specific FlowControl.
	 *
	 * @param imvID
	 * @param attributeID
	 * @param bufferLength
	 * @param buffer
	 *
	 * @throw TNCUtil::exception::ResultException
	 *
	 * @see TNC_TNCS_SetAttribute()
	 */
	virtual void setAttribute(TNC_IMVID imvID, TNC_AttributeID attributeID, TNC_UInt32 bufferLength, TNC_BufferReference buffer);

	/*
	 * @param incomingTNCCSData
	 *
	 * @return outgoingTNCCSData
	 *
	 * @throw ConnectionStateException, TNCCSProtocolNotSupportedException
	 */
	virtual TNCCSData processTNCCSData(TNCCSData incomingTNCCSData) throw (ConnectionStateException, TNCCSProtocolNotSupportedException);

	/**
	 * Informs this protocol instance about a new handshake. Does <b>not</b> call
	 * TNC_IMV_notifyConnectionChange
	 */
	virtual void notifyConnectionChangeHandshake();

private:
	TNCCSBatch incoming;
	TNCCSBatch outgoing;

	/*
	 * If true then wait for the 1. TNCCSBatch (see notifyConnectionChangeHandshake())
	 */
	bool isFirst;

	void checkIMVID(TNC_IMVID imvID, std::map<TNC_IMVID, IMV *>::iterator &iter) throw (std::domain_error);

	bool doXACMLEvaluation(std::list<IMV*> imvs, TNC_IMV_Action_Recommendation &recommendation);
};

}

}

}

#endif /*TNCS_ TNC1PROTOCOL_H_ */
