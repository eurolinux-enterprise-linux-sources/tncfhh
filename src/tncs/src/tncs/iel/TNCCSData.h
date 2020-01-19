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

#ifndef TNCS_TNCCSDATA_H_
#define TNCS_TNCCSDATA_H_

#include <tcg/tnc/tncifimv.h>
#include <tcg/tnc/fhhaddon.h>
#include <stdexcept>

namespace tncfhh
{

namespace iel
{

/**
 * Represent TNCCS-Data message.
 * 
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>16.02.2008 - create class (ib)</li>
 *   <li>19.02.2008 - add some comments and friend (mbs)</li>
 *   <li>29.02.2008 - the last functionality ;) (mbs)</li>
 *   <li>12.07.2009 - change to TNCCSData (mbs)</li>
 * </ul>
 *
 * @class TNCCSData
 * @brief a complete TNCCS-Data message
 * @date 16.02.2008
 * @author Ingo Bente (ib)
 * @author Mike Steinmetz (mbs)
 */
class TNCCSData
{
public:
	
	/**
	 * Constructor for one complete TNCCSData.<br/>
	 * (call by value and deep copy from parameters).
	 *
	 * @param data Pointer to the data data
	 * @param dataLength Length of the data data
	 */
	TNCCSData(TNC_BufferReference data, TNC_UInt32 dataLength) throw (std::invalid_argument);
	
	/**
	 * Copy constructor. (deep copy)
	 *
	 * @param TNCCSData An TNCCSData
	 */
	TNCCSData(const TNCCSData &TNCCSData);

	/**
	 * Constructor that create an empty object.
	 *
	 * @param length the length of the complete TNCCS-data
	 */
	TNCCSData(TNC_UInt32 length);


	/**
	 * Destructor
	 */
	virtual ~TNCCSData();
	

	/*
	 * Operator for data=assign_data
	 *
	 * @param assign_data that assign to this
	 */
    TNCCSData& operator=(TNCCSData const& assign_data);

	/**
	 * Get the const TNCCS-data
	 *
	 * @return the data
	 *
	 * @see getLength()
	 */
	TNC_BufferConstReference getData() const;

	/**
	 * Get the TNCCS-data
	 *
	 * @return the data
	 * 
	 * @see getLength()
	 */
	TNC_BufferReference getData();
	
	/**
	 * Get the length of TNCCS-data
	 *
	 * @return the length of data
	 * 
	 * @see getdata()
	 */
	TNC_UInt32 getLength() const;
	
private:
	/**
	 * The TNCCS-Data
	 */
	TNC_BufferReference data;
	
	/**
	 * The length of data
	 */
	TNC_UInt32 dataLength;
};

} // namespace iel

} // namespace tncfhh

#endif /*TNCS_TNCCSDATA_H_*/
