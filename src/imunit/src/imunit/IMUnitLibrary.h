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

#ifndef TNCFHH_IMUNITLIBRARY_H_
#define TNCFHH_IMUNITLIBRARY_H_

#include "exception/ResultException.h"

#include <tcg/tnc/tncifimc.h>
#include <tcg/tnc/tncifimv.h>
#include <tcg/tnc/fhhaddon.h>
#include <string>

#include <tncfhhConfig.h> 

namespace tncfhh {

namespace iml {

/**
 * IMUnit ID is the generalization of IMC/IMV ID.
 */
typedef unsigned long TNC_IMUnitID;

/**
 * Function pointer to bind function.
 */
typedef TNC_Result (*TNC_BindFunctionPointer)(TNC_IMUnitID id,
		char *functionName, void **pOutfunctionPointer);

/**
 * Class that encapsulates all state information of an IMC/IMV library.
 * There is one instance of this class per IMC/IMV library. Known subclasses
 * are IMCLibrary and IMVLibrary.
 *
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>07.02.2008 - create class (mbs)</li>
 *   <li>06.01.2009 - added comment (ib)</li>
 *   <li>11.06.2009 - tnc_fhh 0.6.0 redesign (ib,mbs)</li>
 * </ul>
 *
 * @date 07.02.2008
 * @author Mike Steinmetz (mbs)
 * @author Ingo Bente (ib)
 */
class IMUnitLibrary {

public:

	/**
	 * Ctor.
	 */
	IMUnitLibrary();

	/**
	 * Dtor.
	 */
	virtual ~IMUnitLibrary();

	/**
	 * Getter for @link #messageTypeList @endlink
	 *
	 * @return @link #messageTypeList @endlink
	 */
	TNC_MessageTypeList getMessageTypeList();

	/**
	 * Getter for @link #typeCount @endlink
	 *
	 * @return @link #typeCount @endlink
	 */
	TNC_UInt32 getMessageTypeCount();

	/**
	 * Getter for @link #imUnitLibraryName @endlink
	 *
	 * @return @link #imUnitLibraryName @endlink
	 */
	std::string getIMUnitLibraryName();

	/**
	 * Getter for @link #isIMUnitLibraryInitialized @endlink
	 *
	 * @return @link #isIMUnitLibraryInitialized @endlink
	 */
	bool getIMUnitLibraryInitialized();

	/**
	 * Getter for @link #imUnitLibraryID @endlink
	 *
	 * @return @link #imUnitLibraryID @endlink
	 */
	TNC_IMUnitID getIMUnitLibraryID();

	/**
	 * Getter for @link #ifImcImvVersion @endlink
	 *
	 * @return @link #ifImcImvVersion @endlink
	 */
	TNC_Version getIfImcImvVersion();

	/**
	 * Setter for @link imUnitLibraryName @endlink
	 */
	void setIMUnitLibraryName(std::string &imUnitName);

	/**
	 * Setter for @link #isIMUnitLibraryInitialized @endlink
	 */
	void setIMUnitLibraryInitialized(bool initialized);

	/**
	 * Setter for @link #imUnitLibraryID @endlink
	 */
	void setIMUnitLibraryID(TNC_IMUnitID id);

	/**
	 * Setter for @link #ifImcImvVersion @endlink
	 */
	void setIfImcImvVersion(TNC_Version version);

	/**
	 * Initializes the IMUnit. Called by TNC_IMC/V_Initialize.
	 *
	 * @param imUnitID - The ID of the IMC/VLibrary assigned by the TNCC/S.
	 * @param minVersion - minimum Version of IF-IMC/V supported by TNCC/S.
	 * @param maxVersion - maximum Version of IF-IMC/V supported by TNCC/S.
	 * @param pOutActualVersion - Version of IF-IMC/V used for communication
	 *                            between the TNCC/S and this library.
	 */
	TNC_Result initialize(TNC_IMUnitID imUnitID, // in
			TNC_Version minVersion, // in
			TNC_Version maxVersion, // in
			TNC_Version *pOutActualVersion // out
			);


protected:

	/**
	 * Add messageType in @link #messageTypeList @endlink
	 *
	 * @param vendorId VendorID (last 24 Bits in messageType)
	 * @param messageSubtype MessageSubtype (first 8 Bits in messageType)
	 */
	void addMessageType(TNC_VendorID vendorId, TNC_MessageSubtype messageSubtype);

	/**
	 * Add messageType in @link #messageTypeList @endlink
	 *
	 * @param messageType MessageType
	 */
	void addMessageType(TNC_MessageType messageType);

	/**
	 * Checks if the Log4cxx Framework is initialized.
	 */
    bool checkLog4cxxInitialized();

	/**
	 * Checks if initialize call for library is correct.
	 */
	void checkInitialize(TNC_IMUnitID imUnitID, TNC_Version minVersion,
			TNC_Version maxVersion, TNC_Version *pOutActualVersion)
			throw (ResultException);
	/**
	 * Checks that IMUnitLibrary is initialized. Throws an exception if
	 * IMUnitLibrary is not initialized.
	 */
	void checkIMUnitLibraryIsInitialized() throw (ResultException);

	/**
	 * Checks if imUnitID matches the libraries ID.
	 */
	void checkIMUnitID(TNC_IMUnitID imUnitID)
			throw (ResultException);

	/**
	 * Checks if receiveMessage preconditions are fulfilled.
	 *
	 * @throw tncfhh::iml::ResultException if preconditions are not fulfilled
	 */
	void checkReceiveMessage(TNC_IMUnitID id,
			TNC_BufferReference messageBuffer, TNC_UInt32 messageLength,
			TNC_MessageType messageType) throw (ResultException);

	/**
	 * List of message types for which the IMC/IMV wishes to receive messages.
	 * @see section 3.8.1 TNC_TNCS_ReportMessageTypes(...) in IF-IMV version 1.2
	 *      http://www.trustedcomputinggroup.org/resources/tnc_ifimv_specification_version_12
	 * @see section 3.8.1 TNC_TNCC_ReportMessageTypes(...) in IF-IMC version 1.2
	 *      http://www.trustedcomputinggroup.org/resources/tnc_ifimc_specification_version_12
	 */
	TNC_MessageTypeList messageTypeList;

	/**
	 * Number of message types for which the IMC/IMV wishes to receive messages.
	 * @see section 3.8.1 TNC_TNCS_ReportMessageTypes(...) in IF-IMV version 1.2
	 *      http://www.trustedcomputinggroup.org/resources/tnc_ifimv_specification_version_12
	 * @see section 3.8.1 TNC_TNCS_ReportMessageTypes(...) in IF-IMC version 1.2
	 *      http://www.trustedcomputinggroup.org/resources/tnc_ifimc_specification_version_12
	 */
	TNC_UInt32 typeCount;

	/**
	 * The name of the IMC/IMV library. This name is used for logging purposes.
	 */
	std::string imUnitLibraryName;

	/**
	 * Flag indicating if IMC/IMV library is initialized
	 */
	bool isIMUnitLibraryInitialized;

	/**
	 * ID of the IMC/IMV library assigned by the TNCC/TNCS
	 */
	TNC_IMUnitID imUnitLibraryID;

	/**
	 * IF-IMC/V Version used between TNCC/IMC or TNCS/IMV.
	 */
	TNC_Version ifImcImvVersion;
};

} // namespace iml

} // namespace tncfhh

#endif /*TNCFHH_IMUNITLIBRARY_H_*/
