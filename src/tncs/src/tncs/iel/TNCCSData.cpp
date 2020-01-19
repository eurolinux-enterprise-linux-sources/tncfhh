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

#include "TNCCSData.h"
#include "string_helper.h"

#include <log4cxx/logger.h>
#include <string.h>

namespace tncfhh {

namespace iel {

/* for logging */
static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("TNCS.TNCCSData"));

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNCCSData::TNCCSData(TNC_BufferReference data, TNC_UInt32 dataLength) throw (std::invalid_argument)
:data(NULL), dataLength(dataLength)
{
	LOG4CXX_TRACE(logger, "Create a TNCCSData object. length: " << dataLength << " (" << this << ")");

	if(data == NULL && dataLength != 0)
		throw std::invalid_argument(std::string("Data is NULL but length isn't 0 (") + dataLength + ").");

	// allocate heap memory
	this->data = new TNC_Buffer[dataLength];

	// copy data
	memcpy(this->data, data, dataLength*sizeof(TNC_Buffer));
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNCCSData::TNCCSData(TNC_UInt32 dataLength)
:data(NULL), dataLength(dataLength)
{
	LOG4CXX_TRACE(logger, "Create an empty TNCCSData object. length:" << dataLength << " (" << this << ")");

	// allocate heap memory
	this->data = new TNC_Buffer[dataLength];

	memset(this->data, 0, dataLength*sizeof(TNC_Buffer));
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNCCSData::TNCCSData(const TNCCSData &tnccsdata)
:data(NULL), dataLength(tnccsdata.dataLength)
{
	LOG4CXX_TRACE(logger, "Copy a TNCCSData object. length:" << tnccsdata.dataLength << " (" << this << " from " << &tnccsdata << ")");

	// allocate heap memory
	this->data = new TNC_Buffer[tnccsdata.dataLength];

	// copy data
	memcpy(this->data, tnccsdata.data, tnccsdata.dataLength*sizeof(TNC_Buffer));
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNCCSData::~TNCCSData()
{
	LOG4CXX_TRACE(logger, "Delete an TNCCSData object. (" << this << ")");

	//delete data
	delete[] this->data;

	this->data = NULL;
	this->dataLength = 0;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNCCSData& TNCCSData::operator=(TNCCSData const& assign_data)
{
	LOG4CXX_TRACE(logger, "Assign a TNCCSData object. length:" << assign_data.dataLength << " (" << this << "==" << &assign_data << ")");

	// delete old data
	delete[] this->data;
	this->data = NULL;

	//assign length
	this->dataLength = assign_data.dataLength;

	// allocate heap memory
	this->data = new TNC_Buffer[assign_data.dataLength];

	// copy data
	memcpy(this->data, assign_data.data, assign_data.dataLength*sizeof(TNC_Buffer));

	//return the result
	return *this;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_BufferConstReference TNCCSData::getData() const
{
	return this->data;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_BufferReference TNCCSData::getData()
{
	return this->data;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_UInt32 TNCCSData::getLength() const
{
	return this->dataLength;
}

} // namespace iel

} // namespace tncfhh
