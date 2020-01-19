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

/**
 * TNC@FHH specific addons to the TCG specifications
 *
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>15.08.2006 - create (MS)</li>
 *   <li>15.02.2008 - comments/change (ib)</li>
 *   <li>11.04.2008 - add connectionCreate (mbs)</li>
 *   <li>04.11.2008 - removed obsolete function pointers (bhl)</li>
 *   <li>04.11.2008 - changed the name from 'fhhaddon.h' to 'naatncs.h' (bhl)</li>
 *   <li>08.07.2009 - redesign 0.6.0 (ib)</li>
 *   <li>22.07.2009 - move some define to tcg/tnc/fhhaddon.h (mbs)</li>
 * </ul>
 *
 * @date 15.08.2006
 * @author Martin Schmiedel (MS)
 * @author: Mike Steinmetz (mbs)
 * @author: Ingo Bente (ib)
 * @author: Bastian Hellmann (bhl)
 */
#ifndef NAAEAP_H_
#define NAAEAP_H_

#include <tcg/tnc/tncifimv.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32
#ifdef TNC_IMV_EXPORTS
#define TNC_IMV_API __declspec(dllexport)
#else
#define TNC_IMV_API __declspec(dllimport)
#endif
#else
#define TNC_IMV_API
#endif

/**
 * Terminate function for libNAAEAP.
 */
TNC_IMV_API TNC_Result terminate();

/**
 * Interface function for libNAAEAP.
 *
 * Called by FreeRADIUS when a new connection // FIXME - documentation
 * should be established (necessary for running a TNC handshake).
 * This function sets up a new connection context that is identified
 * by the given connection id.
 *
 * @param tnc_config path to tnc_config file
 */
TNC_IMV_API TNC_Result initialize(/* in */ const char* tnc_config);

/**
 * Interface function for libNAAEAP.
 *
 * Called by FreeRADIUS when a new connection // FIXME - documentation
 * should be established (necessary for running a TNC handshake).
 * This function sets up a new connection context that is identified
 * by the given connection id.<br/>
 * Use the default tnc_config file.
 */
TNC_IMV_API TNC_Result initializeDefault();

/**
 * Interface function for libNAAEAP.
 *
 * Called by FreeRADIUS when a new connection
 * should be established (necessary for running a TNC handshake).
 * This function sets up a new connection context that is identified
 * by the given connection id.
 *
 * @param input c string as identifying key for the connection
 * @param connedtionID buffer where the new connection ID is saved
 */
TNC_IMV_API TNC_Result getConnection(/* in */ const char* input,
		 /* out */ TNC_ConnectionID *connectionID);

/**
 * Interface function for libNAAEAP.
 *
 * Called by FreeRADIUS when EAP-TNC data arrives.
 *
 * @param conID The connection ID
 * @param input The complete EAP_TNC packet (all EAP_TNC specific data) received from the peer
 * @param inputLength The length of the incoming EAP_TNC packet
 * @param output The EAP_TNC packet this library has generated as response to the input packet
 * @param outputLength The length of the ouput packet
 * @param connectionState The current TNC connection state. Determines which EAP code is set in the packet
 *        that will be send to the peer.
 */
TNC_IMV_API TNC_Result processEAPTNCData(
        /*in*/ TNC_ConnectionID conId,
        /*in*/ TNC_BufferReference input,
        /*in*/ TNC_UInt32 inputLength,
        /*out*/ TNC_BufferReference *output,
        /*out*/ TNC_UInt32 *outputLength,
        /*out*/ TNC_ConnectionState *connectionState
);

/**
 * Interface function to libNAAEAP.
 *
 * Called by FreeRADIUS to store the username with a connection.
 *
 * @param conID The connection ID
 * @param username The username
 */
TNC_IMV_API TNC_Result storeUsername(
		/*in*/ TNC_ConnectionID conID,
		/*in*/ TNC_BufferReference username,
		/*in*/ TNC_UInt32 usernameLength
);

/**
 * Activate or deactivate the fragmentation.
 *
 * @param active FALSE (0) deactivate fragmentation, otherwise activate fragmentation.
 */
void setActivateFragmentation(int active);

/**
 * Activate or deactivate the fragmentation.
 *
 * @return FALSE (0) if fragmentation is deactivate and TRUE (1) if fragmentation is activate.
 */
int getActivateFragmentation();

#ifdef __cplusplus
}
#endif

#endif /*NAAEAP_H_*/

