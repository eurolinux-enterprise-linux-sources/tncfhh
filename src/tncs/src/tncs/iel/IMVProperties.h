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

/*
 * ERROR HANDLING
 *
 * The meaning of the available error codes according to IF-IMV 1.2
 *
 * Result Code                    Definition
 * -----------                    ----------
 * TNC_RESULT_SUCCESS             Function completed successfully
 * TNC_RESULT_NOT_INITIALIZED     TNC_IMV_Initialize has not been called
 * TNC_RESULT_ALREADY_INITIALIZED TNC_IMV_Initialize was called twice
 *                                without a call to TNC_IMV_Terminate
 * TNC_RESULT_NO_COMMON_VERSION   No common IF-IMV API version  between
 *                                IMV and TNC Server
 * TNC_RESULT_CANT_RETRY          TNCS cannot attempt handshake retry
 * TNC_RESULT_WONT_RETRY          TNCS refuses to attempt handshake retry
 * TNC_RESULT_INVALID_PARAMETER   Function parameter is not valid
 * TNC_RESULT_ILLEGAL_OPERATION   Illegal operation attempted
 * TNC_RESULT_OTHER               Unspecified error
 * TNC_RESULT_FATAL               Unspecified fatal error
 *
 * Global error handling
 * =====================
 * Errors that occur when an instance of IMVProperties calls a TNC_IMV_*
 * function that have a global meaning no matter when (i.e. during which function call)
 * they occur, are handled as follows:
 * - TNC_RESULT_FATAL
 *   - meaning: .so has permanent error and does not work properly anymore
 *              that means the .so library must be shutdown for all connections
 *              the .so is not reinitialized (restart of TNCS is required instead)
 *   - if possible, TNC_IMV_Terminate is called
 *   - the corresponding libIMV.so is unloaded (i.e. unavailable for all existing connections)
 *     the unload call is issued by the IMVProperties instance responsible for the .so that
 *     has an FATAL error
 *   - the state of this instance is reseted + flag for FATAL error is set in
 *     this instance
 *   - associated IMV instances are NOT changed in this case. all fatal error logic
 *     is located in this instance of IMVProperties
 *   - the libIMV is not reloaded until the TNCS is restarted
 *   - What if a libIMV.so should be reloaded?
 *     Not supported currently. Not mandatory according to TCG specs.
 *   - Special case when initialize fails? Always shut down library?
 *     No special case. Works as described above because instances of IMVproperties + IMVs
 *     continue to exist even when a FATAL error occurs.
 * - TNC_RESULT_NOT_INITIALIZED
 *   - the call that caused this error should be delayed and TNC_IMV_Initialize
 *     should be called
 *   - the IMVProperties instance tries to call Initialize. If this is successful,
 *     the delayed call is forwarded to the .so and the normal flow goes on.
 *   - if the Initialize call fails, the normal error handling for the Initialize
 *     function takes place (see below)
 * - all other error codes are treated as TNC_RESULT_OTHER if not specified otherwise
 *
 * Function specific error handling
 * ================================
 *
 * TNC_IMV_Initialize
 * ------------------
 * TNC_RESULT_ALREADY_INITIALIZED
 *   - this error should occur when TNC_IMV_Initialize is called twice or more
 *     often without calling TNC_IMV_Terminate in between (perhaps when the
 *     tnc_config mentions one .so two or more times)
 *   - this error is normally ignored
 * any other error code
 *   - is treated exactly as TNC_RESULT_FATAL
 *
 * TNC_IMV_notifyConnectionChange
 * ------------------------------
 * TNC_RESULT_OTHER
 *   - this is treated as a permanent error for ONE specific connection
 *   - therefore, this error is NOT handled by IMVProperties
 *     but the error code is forwarded to the calling IMV instance
 *   - the IMV instance tries to call TNC_IMV_notifyConnectionChange(DELETE)
 *     the return value is ignored by the IMV instance (in case a FATAL error occurs
 *     this is handled by IMVProperties as described above)
 * any result code != (SUCCESS || NOT_INITIALIZED || FATAL)
 *   - is treated as TNC_RESULT_OTHER
 *
 * TNC_IMV_ReceiveMessage
 * ----------------------
 * TNC_RESULT_OTHER
 *   - this is treated as a permanent error for ONE specific connection
 *   - therefore, this error is NOT handled by IMVProperties
 *     but the error code is forwarded to the calling IMV instance
 *   - the IMV instance tries to call TNC_IMV_notifyConnectionChange(DELETE)
 *     the return value is ignored by the IMV instance (in case a FATAL error occurs
 *     this is handled by IMVProperties as described above)
 * any result code != (SUCCESS || NOT_INITIALIZED || FATAL)
 *   - is treated as TNC_RESULT_OTHER
 *
 * TNC_IMV_SolicitRecommendation
 * -----------------------------
 * TNC_RESULT_OTHER
 *   - this is treated as a permanent error for ONE specific connection
 *   - therefore, this error is NOT handled by IMVProperties
 *     but the error code is forwarded to the calling IMV instance
 *   - the IMV instance tries to call TNC_IMV_notifyConnectionChange(DELETE)
 *     the return value is ignored by the IMV instance (in case a FATAL error occurs
 *     this is handled by IMVProperties as described above)
 * any result code != (SUCCESS || NOT_INITIALIZED || FATAL)
 *   - is treated as TNC_RESULT_OTHER
 *
 * TNC_IMV_BatchEnding
 * -------------------
 * TNC_RESULT_OTHER
 *   - this is treated as a permanent error for ONE specific connection
 *   - therefore, this error is NOT handled by IMVProperties
 *     but the error code is forwarded to the calling IMV instance
 *   - the IMV instance tries to call TNC_IMV_notifyConnectionChange(DELETE)
 *     the return value is ignored by the IMV instance (in case a FATAL error occurs
 *     this is handled by IMVProperties as described above)
 * any result code != (SUCCESS || NOT_INITIALIZED || FATAL)
 *   - is treated as TNC_RESULT_OTHER
 *
 * TNC_IMV_Terminate
 * -----------------
 * any result code is ignored :D
 */
#ifndef TNCS_IMVPROPERTIES_H_
#define TNCS_IMVPROPERTIES_H_

#include <tcg/tnc/tncifimv.h>
#include <ltdl.h>
#include <string>
#include <list>
#include <stdexcept>

namespace tncfhh {

namespace iel {

/**
 * TODO_Comment
 * 
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>25.02.2008 - create class (mbs)</li>
 *   <li>15.05.2008 - add error handling (mbs)</li>
 * </ul>
 *
 * @class IMVProperties
 * @brief TODO_Brief
 * @date 25.02.2008
 * @author Mike Steinmetz (mbs)
 * @author Ingo Bente (ib)
 */
class IMVProperties {
public:
	/**
	 * Constructor
	 *
	 * @param id The id of the libIMV
	 * @param name The name of the libIMV
	 * @param file The absolute path to libIMV.so
	 */
	IMVProperties(TNC_IMVID id, std::string name, std::string file);

	/**
	 * Destructor
	 */
	virtual ~IMVProperties();

	/**
	 * The ID of the corresponding IMV library
	 */
	virtual TNC_IMVID getID() const;

	/**
	 * The name of the corresponding IMV library
	 */
	virtual std::string getName() const;

	/**
	 * The .so-file of the corresponding IMV library
	 */
	virtual std::string getFile() const;

	/**
	 * Checks if this IMVProperties supports the given message type
	 */
	virtual bool hasMessageType(TNC_MessageType messageType) const;

	/**
	 * Set the supported message types. This method is not check parameter!
	 *
	 * @param supportedTypes
	 * @param typeCount
	 */
	virtual void reportMessageTypes(TNC_MessageTypeList supportedTypes,
			TNC_UInt32 typeCount);

	/**
	 * Provides the bind function to the libIMV.so
	 */
	virtual void call_TNC_IMV_ProvideBindFunction();

	/* methods called by IMV instances*/
	TNC_Result call_TNC_IMV_NotifyConnectionChange(
			TNC_ConnectionID connectionID, TNC_ConnectionState newState);

	TNC_Result call_TNC_IMV_ReceiveMessage(TNC_ConnectionID connectionID,
			TNC_BufferReference message, TNC_UInt32 messageLength,
			TNC_MessageType messageType);

	TNC_Result call_TNC_IMV_ReceiveMessageSOH(TNC_ConnectionID connectionID,
			TNC_BufferReference sohrReportEntry, TNC_UInt32 sohrRELength,
			TNC_MessageType systemHealthID);

	TNC_Result call_TNC_IMV_ReceiveMessageLong(TNC_ConnectionID connectionID,
			TNC_UInt32 messageFlags, TNC_BufferReference message,
			TNC_UInt32 messageLength, TNC_VendorID messageVendorID,
			TNC_UInt32 messageSubtype, TNC_UInt32 sourceIMCID,
			TNC_UInt32 destinationIMVID);

	TNC_Result call_TNC_IMV_SolicitRecommendation(TNC_ConnectionID connectionID);

	TNC_Result call_TNC_IMV_BatchEnding(TNC_ConnectionID connectionID);

private:
	TNC_IMVID id;
	std::string name;
	std::string file;
	TNC_Version ifimvVersion;
	std::list<TNC_MessageType> messageTypes;

	// TNC_IMV function pointers
	TNC_IMV_InitializePointer initializePointer; //Mandatory
	TNC_IMV_NotifyConnectionChangePointer notifyConnectionChangePointer; //Optional
	TNC_IMV_ReceiveMessagePointer receiveMessagePointer; //Optional
	TNC_IMV_SolicitRecommendationPointer solicitRecommendationPointer; //Mandatory
	TNC_IMV_BatchEndingPointer batchEndingPointer; //Optional
	TNC_IMV_TerminatePointer terminatePointer; //Optional
	TNC_IMV_ProvideBindFunctionPointer provideBindFunctionPointer; //Mandatory
	TNC_IMV_ReceiveMessageSOHPointer receiveMessageSOHPointer; //Optional
	TNC_IMV_ReceiveMessageLongPointer receiveMessageLongPointer; //Optional

	/**
	 * Handle to libIMV.so
	 */
	lt_dlhandle handle;

	/**
	 * Wrapper function for lt_dlsym
	 *
	 * @param handle The handle to the .so file.
	 * @param name The name of the symbol that shall be retrieved.
	 *
	 * @return A pointer to the desired function.
	 */
	lt_ptr getSymbol(lt_dlhandle handle, const char *name)
			throw (std::runtime_error);

	/**
	 * Tries to call TNC_IMV_Initialize for the associated .so + handles
	 * all errors.
	 */
	void call_TNC_IMV_Initialize();

	/**
	 * Tries to call TNC_IMV_Terminate for the associated .so + handles
	 * all errors.
	 */
	void call_TNC_IMV_Terminate();

	/**
	 * Handles a fatal error that occurred when calling TNC_IMV_*
	 */
	void handleFatalError();

	bool hasFatalError; // TODO - support for reinitialization
};

} // namespace iel

} // namespace tncfhh

#endif /*TNCS_IMVPROPERTIES_H_*/
