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

#ifndef TNCFHH_IML_TNCS_H_
#define TNCFHH_IML_TNCS_H_

#include "../exception/ResultException.h"

#include <tcg/tnc/tncifimv.h>

namespace tncfhh {

namespace iml {

// Prototyp instead of include.
class IMVLibrary;

/**
 * Interfaceclass for the TNC-Server. With this class, you can call
 * functions on TNC-Server.
 *
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>09.02.2008 - create class (mbs)</li>
 *   <li>08.05.2008 - change namespace (mbs)</li>
 *   <li>16.06.2009 - redesign 0.6.0 (ib)</li>
 * </ul>
 *
 * @class TNCS
 * @brief Interfaceclass for the TNC-Server.
 * @date 09.02.2008
 * @author Mike Steinmetz (mbs)
 *         Ingo Bente (ib)
 */
class TNCS
{
private:
	/**
	 * The connection ID
	 */
	TNC_ConnectionID cid;

	/**
	 * Pointer to the IMVLibrary of the corrensponding IMV of this TNCS instance.
	 */
	IMVLibrary *pImvLibrary;
public:
	/**
	 * @param cid The connection ID
	 */
	TNCS(TNC_ConnectionID cid, IMVLibrary *pImvLibrary);

	/**
	 * Dtor.
	 */
	virtual ~TNCS();
//	virtual void reportMessageTypes() throw (exception::Exception);

	/**
	 * send a IMV/IMC message
	 *
	 * @param message the binary message you would send
	 * @param messageLength the length of message
	 * @param messageType the type of message
	 *
	 * @see <a href="https://www.trustedcomputinggroup.org/specs/TNC/TNC_IFIMV_v1_2_r8.pdf">TCG TNC IF-IMV Specification 1.2</a>
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
	 * Call the TNCS and request to retry the TNC handshake.
	 *
	 * @param reason the reason of handshake retry
	 *
	 * @see <a href="https://www.trustedcomputinggroup.org/specs/TNC/TNC_IFIMV_v1_2_r8.pdf">TCG TNC IF-IMV Specification 1.2</a>
	 */
	virtual void requestHandshakeRetry(TNC_RetryReason reason) throw (ResultException);

	/**
	 * Provide the recommendation to TNCS.
	 *
	 * @param recommendation
	 * @param evaluation
	 *
	 * @see <a href="https://www.trustedcomputinggroup.org/specs/TNC/TNC_IFIMV_v1_2_r8.pdf">TCG TNC IF-IMV Specification 1.2</a>
	 */
	virtual void provideRecommendation(TNC_IMV_Action_Recommendation recommendation, TNC_IMV_Evaluation_Result evaluation) throw (ResultException);

	/**
	 * Get an attribute from the TNCS.
	 * This function is OPTIONAL on TNC-Server.
	 *
	 * @param attributeID
	 * @param bufferLength
	 * @param buffer {out}
	 * @param pOutValueLength {out}
	 *
	 * @return return true if TNC-Server support getAttribute function, otherwise false
	 *
	 * @see <a href="https://www.trustedcomputinggroup.org/specs/TNC/TNC_IFIMV_v1_2_r8.pdf">TCG TNC IF-IMV Specification 1.2</a>
	 * @see TNCS::supportGetAttribute
	 */
	virtual bool getAttribute(/*in*/ TNC_AttributeID attributeID, /*in*/ TNC_UInt32 bufferLength, /*out*/ TNC_BufferReference buffer, /*out*/ TNC_UInt32 *pOutValueLength) throw (ResultException);

	/**
	 * Check the support for getAttribute
	 *
	 * @return return true if TNC-Server support getAttribute function, otherwise false
	 *
	 * @see TNCS::getAttribute
	 */
	virtual bool supportGetAttribute();

	/**
	 * Set an attribute in TNCS.
	 * This function is OPTIONAL on TNC-Server.
	 *
	 * @param attributeID
	 * @param bufferLength
	 * @param buffer
	 *
	 * @return return true if TNC-Server support setAttribute function, otherwise false
	 *
	 * @see <a href="https://www.trustedcomputinggroup.org/specs/TNC/TNC_IFIMV_v1_2_r8.pdf">TCG TNC IF-IMV Specification 1.2</a>
	 * @see TNCS::supportSetAttribute
	 */
	virtual bool setAttribute(TNC_AttributeID attributeID, TNC_UInt32 bufferLength, TNC_BufferReference buffer) throw (ResultException);

	/**
	 * Check the support for setAttribute
	 *
	 * @return return true if TNC-Server support setAttribute function, otherwise false
	 *
	 * @see TNCS::setAttribute
	 */
	virtual bool supportSetAttribute();
};

}  // namespace iml

}  // namespace tncfhh

#endif /*TNCFHH_IML_TNCS_H_*/
