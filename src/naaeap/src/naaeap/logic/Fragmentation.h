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

#ifndef FRAGMENTATION_H_
#define FRAGMENTATION_H_

#include "../data/EapTncFragment.h"

#include <tncs/iel/TNCCSData.h>
#include <map>
#include <queue>

namespace tncfhh
{

namespace nal
{

/**
 * TODO_Comment
 * 
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>16.02.2008 - create class (ib)</li>
 *   <li>19.02.2008 - add methods (mbs)</li>
 *   <li>11.04.2008 - add reset (mbs)</li>
 *   <li>15.05.2008 - now, can disable fragmentation by compiler (mbs)</li>
 *   <li>22.07.2009 - redesign 0.6.0 (mbs)</li>
 * </ul>
 *
 * @class Fragmentation
 * @brief TODO_Brief
 * @date 16.02.2008
 * @author Ingo Bente (ib)
 * @author Mike Steinmetz (mbs)
 */

class Fragmentation
{
public:
	Fragmentation();
	virtual ~Fragmentation();
	
	/**
	 * TODO_Comment
	 *
	 * @param conID
	 * @param input
	 *
	 * @return the next fragment for send
	 */
	EapTncFragment fragment(TNC_ConnectionID conID, const iel::TNCCSData &input) throw (std::logic_error);
	
	/**
	 * TODO_Comment
	 *
	 * @param conID
	 *
	 * @return the next fragment for send
	 */
	EapTncFragment getNextFragment(TNC_ConnectionID conID) throw (std::logic_error);
	
	/**
	 * Detete all TNCCSBatchFragments for a connection ID.
	 * 
	 * @param conID The connection ID
	 */
	void reset(TNC_ConnectionID conID);

	void setActive(bool active);

	bool getActive();

private:
	/**
	 * here stored all not yet sended TNCCS-Batch-Fragments.
	 */
	std::map<TNC_ConnectionID, std::queue<EapTncFragment *> > allEapTncFragments;

	bool active;

	TNC_UInt32 maxFragmentDataSize;
};

} // namespace nal

} // namespace tncfhh

#endif /*FRAGMENTATION_H_*/
