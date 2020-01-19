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

#include "PcrSelection.h"

/* log4cxx includes */
#include <log4cxx/logger.h>
using namespace log4cxx;

static LoggerPtr
logger(Logger::getLogger("PcrSelection"));


PcrSelection::PcrSelection(TNC_BufferReference bitmask, UINT16 length)
	: selectedPcrs()
	  , maxPcr(0)
{
	init(bitmask, length);
}

PcrSelection::~PcrSelection() {
	// TODO Auto-generated destructor stub
}


/*
 * Main_TCG_Architecture_v1_1b 4.25.3
 *
 * The first two bytes of the message represent the length
 * of the bitmask that follows. The bitmask represents the
 * requested PCRs to be quoted.
 *
 * The bitmask is big endian and "should look like:"
 *
 *        BYTE 1             BYTE 2                   ...
 * Bit:   1 1 1 1 0 0 0 0    1  1  1  1  0  0  0 0    ...
 * Pcr:   7 6 5 4 3 2 1 0    15 14 13 12 11 10 9 8    ...
 *
 *
 */
void PcrSelection::init(TNC_BufferReference br, UINT16 length) {
	if (length < 2) {
		LOG4CXX_FATAL(logger, "PcrSelection length < 2");
		return;
	}
	LOG4CXX_TRACE(logger, "Bitmask length=" << length);

	// bytewise through the bitmask
	for(int i = 0; i < length; i++) {
		// bitwise through the byte
		for(int j = 0; j < 8; j++) {
			if (br[i] & (1 << j)) {
				selectedPcrs.push_back(i * 8 + j);
				maxPcr = i * 8 + j;
			}
		}
	}

	LOG4CXX_INFO(logger, "Requested PCRS:");

	for (std::list<long>::iterator it = selectedPcrs.begin(); it != selectedPcrs.end(); it++) {
		LOG4CXX_INFO(logger, "PCR" << *it);
	}
}

std::list<long>& PcrSelection::getPcrList(void)
{
	return selectedPcrs;
}

long PcrSelection::getHighestPcr(void)
{
	return maxPcr;
}

UINT16 PcrSelection::getPcrCount(void)
{
	return selectedPcrs.size();
}




