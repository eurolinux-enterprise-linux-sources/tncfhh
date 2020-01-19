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

/**
 * Simple Wrapper for a TCPA_PCR_SELECTION struct
 *
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>02.03.10 - create class skeleton (awe)</li>
 * </ul>
 *
 * @date 02.03.10
 * @author Arne Welzel (awe)
 *
 */
#ifndef PCR_SELECTION_H_
#define PCR_SELECTION_H_

#include <tss/tspi.h>
#include <tss/tpm.h>
#include <tcg/tnc/tncifimc.h>
#include <list>

class PcrSelection {
public:
	PcrSelection(TNC_BufferReference sel, UINT16 length);

	virtual ~PcrSelection();

	std::list<long>& getPcrList(void);

	long getHighestPcr(void);

	UINT16 getPcrCount(void);

private:
	std::list<long> selectedPcrs;
	long maxPcr;
	void init(TNC_BufferReference bitmask, UINT16 bitMaskLength);
};

#endif // PCR_SELECTION_H_
