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

#include "EapTncBuffer.h"

#include <log4cxx/logger.h>
#include <tncs/iel/string_helper.h>
#include <string.h>

namespace tncfhh
{

namespace nal
{

/* for logging */
static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("NAA-EAP.EapTncBuffer"));

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
EapTncBuffer::EapTncBuffer()
	: tnccsData(0), position(0)
{
	//bzzzz...
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
EapTncBuffer::EapTncBuffer(const EapTncFragment &tnccsFragment)
	:tnccsData(tnccsFragment.getTNCCSDataLength()), position(0)
{
	addEapTncFragment(tnccsFragment, false);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
EapTncBuffer::EapTncBuffer(const EapTncBuffer &eapTncBuffer)
	:tnccsData(eapTncBuffer.tnccsData), position(eapTncBuffer.position)
{
	throw std::runtime_error("TODO ore not? That's the Question!");
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
EapTncBuffer::~EapTncBuffer()
{
	//Flower
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
EapTncBuffer &EapTncBuffer::operator=(const EapTncBuffer &tnccsBuffer)
{
	throw std::runtime_error("TODO ore not? That's the other Question!");

//
//	if(this == &tnccsBatchBuffer){
//		return *this;
//	}
//	this->tnccsBatch = tnccsBatchBuffer.tnccsBatch;
//	this->position = tnccsBatchBuffer.position;
//	return *this;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void EapTncBuffer::addEapTncFragment(const EapTncFragment &fragment, bool isLast) throw (std::domain_error)
{
	LOG4CXX_TRACE(logger, "Add a EapTncFragment (" << fragment.getDataLength() << " Bytes) at position " << this->position << " of " << this->tnccsData.getLength());

	TNC_UInt32 free = this->tnccsData.getLength() - this->getPosition();
	/* is dataFragment has to much data */
	if (free < fragment.getDataLength())
		throw std::domain_error(std::string("EapTncFragment has to much data (") + fragment.getDataLength() + " Bytes), but only " + free + " Bytes free.");


	/* copy DataFragment into tnccsData */
	memcpy(this->tnccsData.getData() + this->position, fragment.getData(), sizeof(TNC_Buffer)*fragment.getDataLength());
	this->position += fragment.getDataLength();

	/* check if the last fragment, the data must completely */
	if (isLast && this->position != this->tnccsData.getLength())
		throw std::domain_error(std::string("addEapTncFragment: EapTncFragment hasn't enough data. position = ") + (this->position) + ", dataLength = " + (this->tnccsData.getLength()) + ". I'am missing " + (this->tnccsData.getLength() - this->position) + " byte data.");
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
iel::TNCCSData EapTncBuffer::getTNCCSData() const
{
	//TODO - exception schmeißen wenn er nicht voll ist
	return this->tnccsData;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_UInt32 EapTncBuffer::getPosition() const
{
	return this->position;
}

} // namespace nal

} // namespace tncfhh
