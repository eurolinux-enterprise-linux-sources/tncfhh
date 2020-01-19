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

#ifndef TNCFHH_IML_IMVLIBRARY_H_
#define TNCFHH_IML_IMVLIBRARY_H_

#include "../IMUnitLibrary.h"
#include "AbstractIMV.h"

#include <map>

// TODO - Test it on windows.
#ifdef WIN32
#  include <windows.h>

	/**
	 * Main method for Windows DLL platform binding. Is called by LoadLibrary, FreeLibrary.
	 *
	 * @param hInstance
	 * @param fdwReason
	 * @param pvReserved
	 * @return
	 */
#	define IMCLIBRARY_OS_EXTENSION \
	int WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, PVOID pvReserved) { \
		return TRUE; \
	}
#else
#	define IMCLIBRARY_OS_EXTENSION
#endif

/**
 * Initializes the TNCFHH IMVLibrary framework. Must be called
 * in the .cpp file of the concrete IMV library.
 *
 * @param name - the name of the concrete IMV library
 */
#define TNCFHH_IMVLIBRARY_INITIALIZE(name) \
	namespace tncfhh            \
    {                           \
        namespace iml           \
        {                       \
	        static name imvLib; \
        }                       \
    }							\
								\
    IMCLIBRARY_OS_EXTENSION		\
								\
	TNC_Result TNC_IMV_Initialize(TNC_IMVID imvID, TNC_Version minVersion, TNC_Version maxVersion, TNC_Version *pOutActualVersion) \
	{							\
		/* transition to C++ world */\
		return tncfhh::iml::imvLib.initialize(imvID, minVersion, maxVersion, pOutActualVersion); \
	}							\
	TNC_Result TNC_IMV_ProvideBindFunction(TNC_IMVID imvID, TNC_TNCS_BindFunctionPointer bindFunction) \
	{							\
		/* transition to C++ world */\
		return tncfhh::iml::imvLib.provideBindFunction(imvID, bindFunction); \
	}							\
	TNC_Result TNC_IMV_NotifyConnectionChange(TNC_IMVID imvID, TNC_ConnectionID connectionID, TNC_ConnectionState newState) \
	{							\
		/* transition to C++ world */\
		return tncfhh::iml::imvLib.notifyConnectionChange(imvID, connectionID, newState); \
	}							\
	TNC_Result TNC_IMV_SolicitRecommendation(TNC_IMVID imvID, TNC_ConnectionID connectionID) \
	{							\
		/* transition to C++ world */\
		return tncfhh::iml::imvLib.solicitRecommendation(imvID, connectionID); \
	}							\
	TNC_Result TNC_IMV_ReceiveMessage(TNC_IMVID imvID, TNC_ConnectionID connectionID, TNC_BufferReference messageBuffer, TNC_UInt32 messageLength, TNC_MessageType messageType) \
	{							\
		/* transition to C++ world */\
		return tncfhh::iml::imvLib.receiveMessage(imvID, connectionID, messageBuffer, messageLength, messageType); \
	}							\
	TNC_Result TNC_IMV_BatchEnding(TNC_IMVID imvID, TNC_ConnectionID connectionID) \
	{							\
		/* transition to C++ world */\
		return tncfhh::iml::imvLib.batchEnding(imvID, connectionID); \
	}							\
	TNC_Result TNC_IMV_Terminate(TNC_IMVID imvID) \
	{							\
		/* transition to C++ world */\
		return tncfhh::iml::imvLib.terminate(imvID); \
	}							\
/* end TNCFHH_IMVLIBRARY_INITIALIZE */

namespace tncfhh {

namespace iml {

// Version number of supported TNC IF-IMV specification
#define TNC_IFIMV_VERSION TNC_IFIMV_VERSION_1

/**
 * Class that encapsulates all state information of an IMV library.
 *
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>16.06.2009 - create class (ib)</li>
 * </ul>
 *
 * @date 16.06.2009
 * @author Ingo Bente (ib)
 */
class IMVLibrary: public IMUnitLibrary {
public:
	/**
	 * Ctor.
	 */
	IMVLibrary();

	/**
	 * Dtor.
	 */
	virtual ~IMVLibrary();

	/**
	 * Abstract method that must be implemented by the concrete IMV library.
	 * The implementation will normally look as follows:
	 * @code return new MyFancyIMVThatInheritsFromAbstractIMV(conID, this) @endcode
	 *
	 * @return A pointer to the new, concrete IMV instance for the given conID.
	 */
	virtual AbstractIMV *createNewImvInstance(TNC_ConnectionID conID) = 0;

	/**
	 * Get IMV by connection id
	 *
	 * @param the connection id
	 *
	 * @return the IMV
	 *
	 * @throw tncfhh::iml::ResultException if IMV not found
	 */
	AbstractIMV * getImvInstances(TNC_ConnectionID id) throw (ResultException);

	/**
	 * This function returns a pointer to a TNC server function with the
	 * specified name.
	 *
	 * @param functionName The name of the function that shall be looked up.
	 * @param tncBindFunction The bindFunction from the server that has been previously
	 *        provided by TNC_IMV_provideBindFunction.
	 *
	 * @return a pointer to the desired function.
	 */
	void * getTNCSFunctionPointer(const char *functionName,
			                     TNC_BindFunctionPointer tncBindFunction) throw (ResultException);
	/**
	 * C++ method for corresponding C-function in IFIMVImpl.cpp
	 * @see TNC_IMV_ProvideBindFunction
	 */
	TNC_Result provideBindFunction(TNC_IMVID imvID, TNC_TNCS_BindFunctionPointer bindFunction);

	/**
	 * C++ method for corresponding C-function in IFIMVImpl.cpp
	 * @see TNC_IMV_notifyConnectionChange
	 */
	TNC_Result notifyConnectionChange(TNC_IMVID imvID, TNC_ConnectionID connectionID, TNC_ConnectionState newState);

	/**
	 * C++ method for corresponding C-function in IFIMVImpl.cpp
	 * @see TNC_IMV_solicitRecommendation
	 */
	TNC_Result solicitRecommendation(TNC_IMVID imvID, TNC_ConnectionID connectionID);

	/**
	 * C++ method for corresponding C-function in IFIMVImpl.cpp
	 * @see TNC_IMV_receiveMessage
	 */
	TNC_Result receiveMessage(TNC_IMVID imvID,
			                  TNC_ConnectionID connectionID,
                              TNC_BufferReference messageBuffer,
                              TNC_UInt32 messageLength,
                              TNC_MessageType messageType);

	/**
	 * C++ method for corresponding C-function in IFIMVImpl.cpp
	 * @see TNC_IMV_batchEnding
	 */
	TNC_Result batchEnding(TNC_IMVID imvID, TNC_ConnectionID connectionID);

	/**
	 * C++ method for corresponding C-function in IFIMVImpl.cpp
	 * @see TNC_IMV_terminate
	 */
	TNC_Result terminate(TNC_IMVID imvID);

	/**
	 * This struct holds all the function pointers to the TNCS functions.
	 */
	struct TNCS_FunctionPointers{
		TNC_TNCS_ReportMessageTypesPointer reportMessageTypesPointer;
		TNC_TNCS_SendMessagePointer sendMessagePointer;
		TNC_TNCS_RequestHandshakeRetryPointer requestHandshakeRetryPointer;
		TNC_TNCS_ProvideRecommendationPointer provideRecommendationPointer;
		TNC_TNCS_BindFunctionPointer bindFunctionPointer;
		TNC_TNCS_GetAttributePointer getAttributePointer;
		TNC_TNCS_SetAttributePointer setAttributePointer;
	};

	/**
	 * The function pointer from TNC-Server
	 */
	struct TNCS_FunctionPointers tncsFunctionPointers;

protected:
	/**
	 * Checks if preconditions for provideBindFunction call are fulfilled, i.e.
	 * - the library is initialized
	 * - the imvID equals @link #imUnitLibraryID @endlink
	 * - bindFunction is not NULL
	 *
	 * @throw tncfhh::iml::ResultException if preconditions are not fulfilled
	 */
	void checkProvideBindFunction(TNC_IMVID imvID, TNC_TNCS_BindFunctionPointer bindFunction) throw (ResultException);

	/**
	 * Checks if preconditions for notifyConnectionChange call are fulfilled, i.e.
	 * - the library is initialized
	 * - the imvID equals @link #imUnitLibraryID @endlink
	 * - the new state is a valid TNC_ConnectionState
	 *
	 * @throw tncfhh::iml::ResultException if preconditions are not fulfilled
	 */
	void checkNotifyConnectionChange(TNC_IMVID imvID, TNC_ConnectionID connectionID, TNC_ConnectionState newState) throw (ResultException);

	/**
	 * Checks if preconditions for solicitRecommendation call are fulfilled, i.e.
	 * - the library is initialized
	 * - the imvID equals @link #imUnitLibraryID @endlink
	 *
	 * @throw tncfhh::iml::ResultException if preconditions are not fulfilled
	 */
	void checkSolicitRecommendation(TNC_IMVID imvID, TNC_ConnectionID connectionID) throw (ResultException);

	/**
	 * Checks if preconditions for batchEnding call are fulfilled, i.e.
	 * - the library is initialized
	 * - the imvID equals @link #imUnitLibraryID @endlink
	 *
	 * @throw tncfhh::iml::ResultException if preconditions are not fulfilled
	 */
	void checkBatchEnding(TNC_IMVID imvID, TNC_ConnectionID connectionID) throw (ResultException);

	/**
	 * Checks if preconditions for terminate call are fulfilled, i.e.
	 * - the library is initialized
	 * - the imvID equals @link #imUnitLibraryID @endlink
	 *
	 * @throw tncfhh::iml::ResultException if preconditions are not fulfilled
	 */
	void checkTerminate(TNC_IMVID imvID) throw (ResultException);

	/**
	 * Map with pointers to concrete IMV instance for a given connection ID.
	 */
	std::map<TNC_ConnectionID, AbstractIMV *> imvInstances;
};

} // namespace iml

} // namespace tncfhh

#endif /* TNCFHH_IML_IMVLIBRARY_H_ */
