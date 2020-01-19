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

#include "EapTncFragment.h"

#include <netinet/in.h>
#include <string.h>
#include <log4cxx/logger.h>
#include <tncs/iel/string_helper.h>


namespace tncfhh
{

namespace nal
{

/* for logging */
static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("NAA-EAP.EapTncFragment"));

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
EapTncFragment::EapTncFragment(const TNC_BufferReference fragment, TNC_UInt32 fLength) throw (std::invalid_argument)
	:fragment(NULL), fragmentLength(fLength)
{
	LOG4CXX_TRACE(logger, "Create EapTncFragment from EAP-TNC Packet " << this)

	// check parameters
	if(fragment == NULL || fLength < EAP_TNC_HEADER_FLAGS_SIZE) {
		throw std::invalid_argument(std::string("Invalid Parameters: fragmentData = ") + ((void*)fragment) + ", fLength = " + (fLength) + ".");
	}

	/* read relevant TNC flags */
	this->lengthIncluded = (*fragment)&0x80             /*10000000*/;
	this->moreFragments  = (*fragment)&0x40             /*01000000*/;

	/* check advanced parameter */
	if (this->lengthIncluded && fLength < (EAP_TNC_HEADER_FLAGS_SIZE + EAP_TNC_HEADER_DATA_LENGTH_SIZE) )
		throw std::invalid_argument(std::string("Invalid Parameters: length is included but fLength = ") + (fLength) + ".");

	/* calculate attributes */
	if (this->lengthIncluded){
		this->TNCCSDataLength = ntohl(*(unsigned long int *)(fragment+1));
	} else {
		this->TNCCSDataLength = 0;
	}

	/* copy fragment */
	this->fragment = new TNC_Buffer[fLength];
	memcpy(this->fragment, fragment, fLength*sizeof(TNC_Buffer));

	LOG4CXX_TRACE(logger, "LengthIncludet: " << this->lengthIncluded <<
			" moreFragments: " << this->moreFragments <<
			" TNCCSDataLength: " << this->TNCCSDataLength <<
			" dataLength: " << this->getDataLength());
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
EapTncFragment::EapTncFragment(TNC_BufferConstReference data, TNC_UInt32 dataLength, bool lengthIncluded, TNC_UInt32 TNCCSDataLength, bool moreFragments) throw (std::invalid_argument)
	:fragment(NULL), fragmentLength(0), TNCCSDataLength(0), lengthIncluded(lengthIncluded), moreFragments(moreFragments)
{
	LOG4CXX_TRACE(logger, "Create EapTncFragment from TNCCSData " << this)

	/* check parameters */
	if( (data == NULL && dataLength != 0) ||
		(data != NULL && dataLength == 0) )
		throw std::invalid_argument(std::string("Invalid Parameters: data = ") + (data) + ", dataLength = " + (dataLength) + ".");

	/* check more parameters */
	if (this->lengthIncluded && TNCCSDataLength == 0)
		throw std::invalid_argument(std::string("Invalid Parameters: lengthIncluded = true, TNCCSDataLength = ") + (TNCCSDataLength) + ".");

	/* check still more parameters */
	if (this->moreFragments && this->lengthIncluded && dataLength >= TNCCSDataLength)
		throw std::invalid_argument(std::string("Invalid Parameters: lengthIncluded = true, moreFragemnts = true, TNCCSDataLength = ") + (TNCCSDataLength) + ", dataLength = " + (dataLength) + ".");

	/* set fragmentLength */
	if (this->lengthIncluded)
		this->fragmentLength = dataLength + (EAP_TNC_HEADER_FLAGS_SIZE + EAP_TNC_HEADER_DATA_LENGTH_SIZE);
	else
		this->fragmentLength = dataLength + EAP_TNC_HEADER_FLAGS_SIZE;

	/* allocate memory */
	this->fragment = new TNC_Buffer[sizeof(TNC_Buffer)*this->fragmentLength];

	/* set version in fragment */
	*this->fragment = 0x01;
	/* add length included bit */
	*this->fragment |= (this->lengthIncluded?0x80:0x00);
	/* add more fragments bit */
	*this->fragment |= (this->moreFragments?0x40:0x00);

	/* set TNCCS-Data length */
	if (this->lengthIncluded) {
		/* in fragment */
		*(unsigned long int *)(this->fragment+1) = htonl(TNCCSDataLength);
		/* in local variable */
		this->TNCCSDataLength = TNCCSDataLength;
	}

	/* copy data */
	memcpy(this->lengthIncluded?this->fragment+(EAP_TNC_HEADER_FLAGS_SIZE + EAP_TNC_HEADER_DATA_LENGTH_SIZE):this->fragment+EAP_TNC_HEADER_FLAGS_SIZE, data, sizeof(TNC_Buffer)*dataLength);

	LOG4CXX_TRACE(logger, "LengthIncludet: " << this->lengthIncluded <<
			" moreFragments: " << this->moreFragments <<
			" TNCCSDataLength: " << this->TNCCSDataLength <<
			" dataLength: " << this->getDataLength());
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
EapTncFragment::EapTncFragment(const EapTncFragment & source)
:fragment(NULL), fragmentLength(source.fragmentLength),
TNCCSDataLength(source.TNCCSDataLength), lengthIncluded(source.lengthIncluded),
moreFragments(source.moreFragments)
{
	LOG4CXX_TRACE(logger, "Create EapTncFragment from other EapTncFragment " << &source << " " << this);

	this->fragment = new TNC_Buffer[fragmentLength];
	memcpy(this->fragment, source.fragment, fragmentLength*sizeof(TNC_Buffer));
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
EapTncFragment::~EapTncFragment()
{
	LOG4CXX_TRACE(logger, "Delete me. " << this);

	delete this->fragment;
	this->fragment = NULL;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
EapTncFragment & EapTncFragment::operator=(const EapTncFragment & source)
{
	LOG4CXX_TRACE(logger, this << "=" << &source);

	this->TNCCSDataLength = source.TNCCSDataLength;
	this->fragmentLength = source.fragmentLength;
	this->lengthIncluded = source.lengthIncluded;
	this->moreFragments = source.moreFragments;

	delete this->fragment;
	this->fragment = new TNC_Buffer[source.fragmentLength];
	memcpy(this->fragment, source.fragment, source.fragmentLength*sizeof(TNC_Buffer));

	return *this;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_BufferReference EapTncFragment::getData() const
{
	if (this->lengthIncluded){
		return this->fragment + (EAP_TNC_HEADER_FLAGS_SIZE + EAP_TNC_HEADER_DATA_LENGTH_SIZE);
	} else {
		return this->fragment  + EAP_TNC_HEADER_FLAGS_SIZE;
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_UInt32 EapTncFragment::getDataLength() const
{
	/* calculate attributes */
	if (this->lengthIncluded){
		return this->fragmentLength - (EAP_TNC_HEADER_FLAGS_SIZE + EAP_TNC_HEADER_DATA_LENGTH_SIZE);
	} else {
		return this->fragmentLength - (EAP_TNC_HEADER_FLAGS_SIZE);
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */#
TNC_BufferConstReference EapTncFragment::getFragment() const
{
	return this->fragment;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_UInt32 EapTncFragment::getFragmentLength() const
{
	return this->fragmentLength;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_UInt32 EapTncFragment::getTNCCSDataLength() const
{
	return this->TNCCSDataLength;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool EapTncFragment::hasLengthIncluded() const
{
	return this->lengthIncluded;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool EapTncFragment::hasMoreFragments() const
{
	return this->moreFragments;
}

} // namespace nal

} // namespace tncfhh
