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
#ifndef TNCS_ABSTRACTTNCCSPROTOCOL_H_
#define TNCS_ABSTRACTTNCCSPROTOCOL_H_

#include <tcg/tnc/tncifimv.h>
#include <string>
#include "Policy.h"
#include "TNCCSData.h"
#include <list>
#include <map>
#include "../exception/ConnectionStateException.h"
#include "../exception/TNCCSProtocolNotSupportedException.h"

namespace tncfhh {

namespace iel {

/**
 * TODO Comment
 *
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>13.07.2009 - create class (mbs)</li>
 * </ul>
 *
 * @class AbstractTNCCSProtocol
 * @brief TODO Brief
 * @date 13.07.2009
 * @author Mike Steinmetz (mbs)
 */
class AbstractTNCCSProtocol {
public:
	/*
	 * Default-Ctor.
	 */
	AbstractTNCCSProtocol(const std::map<TNC_IMVID, IMV*> &imvsMap);

	/*
	 * Default-Dtor.
	 */
	virtual ~AbstractTNCCSProtocol();

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
	virtual void sendMessage(TNC_IMVID imvID, TNC_BufferReference message, TNC_UInt32 messageLength, TNC_MessageType messageType)=0;

	/**
	 * This function delegates the requestHandshakeRetry() call to the connectionID specific FlowControl.
	 *
	 * @param imvID
	 * @param connectionID
	 * @param reason
	 *
	 * @throw TNCUtil::exception::ResultException
	 *
	 * @see TNC_TNCS_RequestHandshakeRetry()
	 */
	virtual void requestHandshakeRetry(TNC_IMVID imvID, TNC_RetryReason reason)=0;

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
	virtual void getAttribute(TNC_IMVID imvID, TNC_AttributeID attributeID, TNC_UInt32 bufferLength, /*out*/ TNC_BufferReference buffer, /*out*/ TNC_UInt32 *pOutValueLength)=0;

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
	virtual void setAttribute(TNC_IMVID imvID, TNC_AttributeID attributeID, TNC_UInt32 bufferLength, TNC_BufferReference buffer)=0;

	/**
	 * Returns the name of the protocol.
	 */
	std::string getProtocolName() const;

	/**
	 * Sets the IMVs for the TNCCS Protocol instance.
	 * IMVs are needed for calling TNC_IMV functions.
	 */
//	void setIMVs(const std::map<TNC_IMVID, IMV*> &imvsMap);

	/**
	 * Informs this protocol instance about a new handshake. Does <b>not</b> call
	 * TNC_IMV_notifyConnectionChange
	 */
	virtual void notifyConnectionChangeHandshake();

	/**
	 * Processes incoming TNCCSData. If this protocol can process the incoming
	 * data, this will lead normally to a receiveMessage call to the IMV instances.
	 * Those IMVs will then normally call sendMessage which is delegated
	 * over IFTNCSImpl->Coordinator->Connection to this protocol. Those sendMessage
	 * calls will be composed to a outgoing TNCCSData instance which is returned
	 * by this method.
	 */
	virtual TNCCSData processTNCCSData(TNCCSData incomingTNCCSData) throw (ConnectionStateException, TNCCSProtocolNotSupportedException);

protected:
	std::string protocolName;
	Policy policy;
	std::map<TNC_IMVID, IMV*> imvs;
};


} // namespace iel

} // namespace tncfhh

#endif /*TNCS_ ABSTRACTTNCCSPROTOCOL_H_ */
