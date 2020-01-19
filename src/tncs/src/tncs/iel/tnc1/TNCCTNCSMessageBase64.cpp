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
#include "TNCCTNCSMessageBase64.h"

#include <tcg/tnc/fhhaddon.h>
#include <string.h>

namespace tncfhh
{

namespace iel
{

namespace tnc1
{

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNCCTNCSMessageBase64::TNCCTNCSMessageBase64(TNC_MessageType type, TNC_BufferReference data, TNC_UInt32 dataLength)
	:TNCCTNCSMessage(type), data(data), dataLength(dataLength)
{
	/* copy data only if length is != 0 */
	if (dataLength != 0) {
		this->data = new TNC_Buffer[dataLength];
		memcpy(this->data, data, dataLength * sizeof(TNC_Buffer));
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNCCTNCSMessageBase64::~TNCCTNCSMessageBase64()
{
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_BufferReference TNCCTNCSMessageBase64::getData()
{
	return this->data;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_UInt32 TNCCTNCSMessageBase64::getDataLength()
{
	return this->dataLength;
}

} // namespace tnc1

} // namespace iel

} // namespace tncfhh
