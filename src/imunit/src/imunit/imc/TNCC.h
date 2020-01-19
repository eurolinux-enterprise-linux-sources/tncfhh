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

#ifndef TNCFHH_IML_TNCC_H_
#define TNCFHH_IML_TNCC_H_

#include "../exception/ResultException.h"

#include <tcg/tnc/tncifimc.h>

namespace tncfhh {

namespace iml {

// Prototyp instead of include IMCLibrary.h
class IMCLibrary;

/**
 * Interfaceclass for the TNC-Client. With this class, you can call
 * functions on TNC-Client.
 *
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>09.02.2008 - create class (mbs)</li>
 *   <li>08.05.2008 - change namespace (mbs)</li>
 *   <li>16.06.2009 - redesign (ib)</li>
 * </ul>
 *
 * @class TNCC
 * @brief Interfaceclass for the TNC-Client.
 * @date 09.02.2008
 * @author Mike Steinmetz (mbs)
 *         Ingo Bente (ib)
 */
class TNCC
{
private:
	/**
	 * The connection ID
	 */
	TNC_ConnectionID cid;

	/**
	 * The IMCLibrary for the corresponding IMC instance of this TNCC instance.
	 */
	IMCLibrary *pImcLibrary;

public:
	/**
	 * Ctor.
	 *
	 * @param cid the connection ID
	 * @param cid the corresponding IMCLibrary
	 */
	TNCC(TNC_ConnectionID cid, IMCLibrary *pImcLibrary);

	/**
	 * Dtor.
	 */
	virtual ~TNCC();

	// can not be called by an IMC outside of provideBindFunction.
//	virtual void reportMessageTypes() throw (exception::Exception);

	/**
	 * send a IMV/IMC message
	 *
	 * @param message The binary message you want to send.
	 * @param messageLength The length of message.
	 * @param messageType The type of message.
	 *
	 * @see <a href="https://www.trustedcomputinggroup.org/specs/TNC/TNC_IFIMC_v1_2_r8.pdf">TCG TNC IF-IMC Specification 1.2</a>
	 */
	virtual void sendMessage(TNC_BufferReference message, TNC_UInt32 messageLength, TNC_MessageType messageType) throw (ResultException);

	/**
	 * send a IMV/IMC message
	 *
	 * @param message The binary message you want to send.
	 * @param messageLength The length of message.
	 * @param vendorId The type of message.
	 * @param messageSubtype The type of message.
	 *
	 * @see <a href="https://www.trustedcomputinggroup.org/specs/TNC/TNC_IFIMC_v1_2_r8.pdf">TCG TNC IF-IMC Specification 1.2</a>
	 */
	virtual void sendMessage(TNC_BufferReference message, TNC_UInt32 messageLength, TNC_VendorID vendorId, TNC_MessageSubtype messageSubtype) throw (ResultException);

	/**
	 * Call the TNCC and request to retry the TNC handshake.
	 *
	 * @param Reason the reason of handshake retry
	 *
	 * @see <a href="https://www.trustedcomputinggroup.org/specs/TNC/TNC_IFIMC_v1_2_r8.pdf">TCG TNC IF-IMC Specification 1.2</a>
	 */
	virtual void requestHandshakeRetry(TNC_RetryReason reason) throw (ResultException);
};

}  // namespace iml

}  // namespace tncfhh

#endif /*TNCFHH_IML_TNCC_H_*/
