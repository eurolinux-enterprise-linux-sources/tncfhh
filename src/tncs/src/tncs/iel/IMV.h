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
#ifndef TNCS_IMV_H_
#define TNCS_IMV_H_

#include "IMVProperties.h"

#include <list>

namespace tncfhh {

namespace iel {

/**
 * Connection specific IMV instance.
 * 
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>25.02.2008 - create class (mbs)</li>
 *   <li>28.02.2008 - impl methods (mbs)</li>
 *   <li>08.04.2008 - fixed a hasProvideRecommendation() bug (mbs)</li>
 *   <li>15.05.2008 - add error handling (mbs)</li>
 *   <li>13.07.2009 - redesign for 0.6.0 (mbs)</li>
 * </ul>
 *
 * @class IMV
 * @brief TODO_Brief
 * @date 25.02.2008
 * @author Mike Steinmetz (mbs)
 */
class IMV
{
public:
	/**
	 * Constructor. Calls TNC_IMV_NotifyConnectionChange(CREATE).
	 *
	 * @param conID the Connection ID for this IMV instance
	 * @param imvProperties Reference to IMVProperties instance
	 */
	IMV(TNC_ConnectionID conID, IMVProperties *imvProperties);

	/**
	 * Destructor
	 */
	virtual ~IMV();
	
	virtual void notifyConnectionChange(TNC_ConnectionState connectionState);

	/**
	 * Forwards the call to IMVProperties.
	 */
	virtual void receiveMessage(TNC_BufferReference message, TNC_UInt32 messageLength, TNC_MessageType messageType);
	virtual void solicitRecommendation();
	virtual void batchEnding();
	
	virtual bool isInNotifyConnectionChange();
	virtual bool isInReceiveMessage();
	virtual bool isInSolicitRecommendation();
	virtual bool isInBatchEnding();

	virtual bool hasProvideRecommendation();
	virtual void setProvideRecommendation(TNC_IMV_Action_Recommendation recommendation, TNC_IMV_Evaluation_Result evaluation);
	
	/**
	 * TODO_Comment
	 * <br>
	 * call only function if hasProvideRecommendation() return true
	 *
	 * @return the action recommendation
	 */
	virtual TNC_IMV_Action_Recommendation getRecommendation();
	
	/**
	 * TODO_Comment
	 * <br>
	 * call only function if hasProvideRecommendation() return true
	 *
	 * @return the evaluation result
	 */
	virtual TNC_IMV_Evaluation_Result getEvaluation();
	
	/**
	 * TODO_Comment
	 *
	 * @return a const reference to IMVProperties instance (don't delete that reference)
	 */
	virtual const IMVProperties *getIMVProperties();

	/**
	 * return if the IMV has an error. The error is resetting on begin handshake.
	 *
	 * @return true if the imv has an error, otherwise false
	 */
	virtual bool hasError() const;
	
	TNC_ConnectionID getConnectionID();


private:
	TNC_ConnectionID conID;
	IMVProperties *imvProperties;
	
	bool inNotifyConnectionChange;
	bool inReceiveMessage;
	bool inSolicitRecommendation;
	bool inBatchEnding;
	
	bool isProvideRecommendationSet;
	bool error;
	TNC_IMV_Action_Recommendation recommendation;
	TNC_IMV_Evaluation_Result evaluation;

	void handleOtherError();
};

}  // namespace iel

}  // namespace tncfhh

#endif /*TNCS_IMV_H_*/
