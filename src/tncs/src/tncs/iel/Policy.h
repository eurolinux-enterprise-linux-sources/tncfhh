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
#ifndef TNCS_POLICY_H_
#define TNCS_POLICY_H_

#include "IMV.h"

#include <list>

namespace tncfhh {

namespace iel {

/**
 * TODO_Comment
 * 
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>25.02.2008 - create class (mbs)</li>
 *   <li>29.02.2008 - impl methods (mbs)</li>
 *   <li>08.04.2008 - fixed the accessIsolated bug (mbs)</li>
 *   <li>11.04.2008 - added resetPolicy [bug] (mbs)</li>
 *   <li>16.05.2008 - inform IMVs about notifyConnectionChange [bug] (mbs)</li>
 *   <li>16.07.2009 - redesign 0.6.0 (ib)</li>
 * </ul>
 *
 * @class Policy
 * @brief TODO_Brief
 * @date 25.02.2008
 * @author Mike Steinmetz (mbs)
 *         Ingo Bente (ib)
 */
class Policy
{
public:
	Policy();
	virtual ~Policy();
	
	/**
	 * Reset the Policy. In this Implementation the method do nothing.
	 */
	virtual void resetPolicy();
	
	/**
	 * Computes an overall action recommendation from the recommendations
	 * provided by the single IMV instances. This function works as follows:
	 * - if all IMVs provide an allow -> an allow is returned
	 * - if there is at least one none -> a none is returned
	 * - if there is at least one isolate and no none -> an isolate is returned
	 *
	 * In short: allow < isolate < none.
	 * The evaluation results provided by the IMVs are not considered.
	 *
	 * This function is called when the IF-TNCCS implementation notifies that
	 * a handshake is finished.
	 *
	 * TODO - getActionRecommendation make it configurable
	 */
	virtual TNC_IMV_Action_Recommendation getActionRecommendation(const std::list<IMV *> &imvs);

	/**
	 * TODO_Comment
	 *
	 * @param outgoingTnccsBatch
	 * @param imvs
	 *
	 * @throw ConnectionStateException is handshake Finished
	 */
//	virtual void isHandshakeFinished(TNCCSBatch & outgoingTnccsBatch, std::list<IMV*> imvs); TODO - Policy move isHandshakeFinished to IF-TNCS Protocol
	
private:
//	void handshakeIsFinished(TNCCSBatch & outgoingTnccsBatch,  std::list<IMV*> & imvs); TODO - Policy - create recommendation message in IF-TNCS Protocol
};

}  // namespace iel

}  // namespace tncfhh

#endif /*TNCS_POLICY_H_*/
