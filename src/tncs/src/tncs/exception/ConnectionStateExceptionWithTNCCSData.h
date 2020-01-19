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

#ifndef TNCS_CONNECTIONSTATEEXCEPTIONWITHTNCCSDATA_H_
#define TNCS_CONNECTIONSTATEEXCEPTIONWITHTNCCSDATA_H_

#include "ConnectionStateException.h"
#include "../iel/TNCCSData.h"
#include <tcg/tnc/tncifimv.h>

namespace tncfhh
{

namespace iel
{

/**
 * Exception that has information about the TNC_ConnectionState and provides
 * the last outgoing TNCCSData.
 * 
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>19.02.2008 - create class (ib)</li>
 *   <li>19.02.2008 - add getter (mbs)</li>
 *   <li>29.02.2008 - move in NAA-TNCS (mbs)</li>
 *   <li>17.07.2009 - redesign 0.6.0 (ib)</li>
 *   <li>10.09.2009 - add method what (mbs)</li>
 * </ul>
 *
 * @class ConnectionStateExceptionWithTNCCSData
 * @brief Exception that has information about the TNC_ConnectionState.
 * @date 19.02.2008
 * @author Ingo Bente (ib)
 * @author Mike Steinmetz (mbs)
 */
class ConnectionStateExceptionWithTNCCSData : public ConnectionStateException
{
public:
	
	/**
	 * Constructor
	 * 
	 * @param message An error message.
	 * @param connectionState An TNC_ConnectionState.
	 */
	ConnectionStateExceptionWithTNCCSData(TNC_ConnectionState connectionState, TNCCSData lastTnccsData) throw ();
	
	/**
	 * Destructor
	 */
	virtual ~ConnectionStateExceptionWithTNCCSData() throw ();
	
	/**
	 * Returns the last TnccsData
	 */
	TNCCSData getLastTnccsData() const;

	/**
	 * overwrite the std::exception method what
	 *
	 * @return get info about this exception
	 */
    virtual const char* what() const throw();

private:
	
	/**
	 * Last outgoing TNCCSData from TNCS to TNCC
	 */
	TNCCSData lastTnccsData;

};

} // namespace iel

} // namespace tncfhh

#endif /*TNCS_CONNECTIONSTATEEXCEPTIONWITHTNCCSDATA_H_*/
