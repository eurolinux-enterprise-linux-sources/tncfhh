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
#ifndef TNCS_CONNECTION_H_
#define TNCS_CONNECTION_H_

#include "IMV.h"
#include "Policy.h"
#include "TNCCSData.h"
#include "AbstractTNCCSProtocol.h"
#include "../exception/ResultException.h"
#include "../exception/ConnectionStateException.h"
#include "../exception/ConnectionStateExceptionWithTNCCSData.h"
#include "../exception/TNCCSProtocolNotSupportedException.h"

#include <exception>
#include <map>
#include <list>

namespace tncfhh {

namespace iel {

/**
 * The Connection class encapsulates all information
 * related to one given connection ID.
 *
 * Its main purpose is to delegate TNCCSData to the right
 * TNCCSProtocol handler. Furthermore, Connection manages the  IMV instances
 * (create, delete, notifyConnectionChange).
 * 
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>25.02.2008 - create class (mbs)</li>
 *   <li>28.02.2008 - added TNCS functions (ib)</li>
 *   <li>29.02.2008 - the last functionality ;) (mbs)</li>
 *   <li>11.04.2008 - added notifyConnectionChangeHandshake (mbs)</li>
 *   <li>22.04.2008 - fixed notifyConnectionChangeHandshake [bug 9] (mbs)</li>
 *   <li>12.07.2009 - redesign for 0.6.0 (mbs,ib)</li>
 *   <li>05.01.2011 - added username as field
 * </ul>
 *
 * @class Connection
 * @brief TODO_Brief
 * @date 25.02.2008
 * @author Mike Steinmetz (mbs)
 * @author Ingo Bente (ib)
 */
class Connection
{
public:
	/**
	 * Constructor.
	 *
	 * @param conID The ID for this connection (provided by Coordinator)
	 * @param imvProperties list of all available imvProperties. This connection
	 *        creates the necessary IMV instances for each given property.
	 */
	Connection(TNC_ConnectionID conID, const std::list<IMVProperties*> &imvProperties);

	/**
	 * Destructor.
	 * Deletes allocated IMV instances.
	 */
	virtual ~Connection();
	
	/**
	 * Notifies all IMVs and all TNCCSProtocol handlers about a new handshake.
	 * Called by Coordinator at the beginning of a handshake.
	 */
	virtual void notifyConnectionChangeHandshake();
	
	/**
	 * Called by Coordinator when TNCCSData arrives from the NAA.
	 * Parses incoming TNCData by forwarding it to a concrete TNCCSProtocol
	 * implementation and returns the result (outgoing TNCCSData).
	 *
	 * @param receivedData TNCCSData for receive from client
	 *
	 * @return TNCCSData outgoing data (send to TNCC)
	 *
	 * @throw ConnectionStateException when handshake is finished.
	 * @throw TNCCSProtocolNotSupportedException when incoming TNCCSData could not be parsed.
	 */
	virtual TNCCSData processTNCCSData(const TNCCSData & receivedData) throw (ConnectionStateException, ConnectionStateExceptionWithTNCCSData, TNCCSProtocolNotSupportedException);
	
	// TNCS functions
	
	/**
	 * Called by Coordinator. Forwards the message to a concrete TNCCSProtocol
	 * implementation.
	 *
	 * @param imvID
	 * @param message
	 * @param messageLength
	 * @param messageType
	 *
	 */
	void sendMessage(TNC_IMVID imvID, TNC_BufferReference message, TNC_UInt32 messageLength, TNC_MessageType messageType) throw (ResultException);
	
	/**
	 * Called by Coordinator. Not implemented yet.
	 *
	 * @param imvID
	 * @param connectionID
	 * @param reason
	 *
	 */
	void requestHandshakeRetry(TNC_IMVID imvID, TNC_RetryReason reason) throw (ResultException);
	
	/**
	 * Called by Coordinator. Sets the recommendation for an IMV.
	 *
	 * @param imvID
	 * @param recommendation
	 * @param evaluation
	 *
	 */
	void provideRecommendation(TNC_IMVID imvID, TNC_IMV_Action_Recommendation recommendation, TNC_IMV_Evaluation_Result evaluation)  throw (ResultException);
	
	/**
	 * Called by Coordinator. Returns the requested attribute via buffer if possible.
	 *
	 * @param imvID
	 * @param attributeID
	 * @param bufferLength
	 * @param buffer [out]
	 * @param pOutValueLength [out]
	 *
	 */
	void getAttribute(TNC_IMVID imvID, TNC_AttributeID attributeID, TNC_UInt32 bufferLength, TNC_BufferReference buffer, TNC_UInt32 *pOutValueLength)  throw (ResultException);
	
	/**
	 * Called by Coordinator. Sets the specific attribute.
	 *
	 * @param imvID
	 * @param attributeID
	 * @param bufferLength
	 * @param buffer
	 *
	 */
	void setAttribute(TNC_IMVID imvID, TNC_AttributeID attributeID, TNC_UInt32 bufferLength, TNC_BufferReference buffer) throw (ResultException);

	/**
	 * Getter for current connection state
	 * FIXME - called by whom?
	 */
	TNC_ConnectionState getConnectionState();
private:
	/**
	 * The connection ID.
	 */
	TNC_ConnectionID conID;

	/**
	 * The username for this connection.
	 */
	TNC_BufferReference username;

	/**
	 * The current state of this connection.
	 */
	TNC_ConnectionState connectionState;

	/**
	 * All IMV instances relevant for this connection.
	 */
	std::map<TNC_IMVID, IMV*> imvInstances;

	/**
	 * List of Handlers for all supported TNCCSProtocols
	 */
	std::list<AbstractTNCCSProtocol *> tnccsProtocolHandlerChain;

	/**
	 * The active TNCCSProtocol handler. Set when the first TNCCSData
	 * has arrived and was successful parsed by a handler of the handler chain.
	 *
	 * Further incoming data in this handshake is processed by this handler and not
	 * by any other handler of the chain.
	 */
	AbstractTNCCSProtocol *activeTnccsProtocolHandler;

	/**
	 * Looks up a IMV instance by the given ID.
	 *
	 * Throws std::runtime_error if IMV does not exists.
	 */
	IMV *getImvById(TNC_IMVID imvID) throw (std::runtime_error);

};

}  // namespace iel

}  // namespace tncfhh

#endif /*TNCS_CONNECTION_H_*/
