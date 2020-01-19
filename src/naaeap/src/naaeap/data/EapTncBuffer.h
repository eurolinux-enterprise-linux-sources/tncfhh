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

#ifndef EAPTNCBUFFER_H_
#define EAPTNCBUFFER_H_

#include "EapTncFragment.h"

#include <tncs/iel/TNCCSData.h>

namespace tncfhh
{

namespace nal
{

/**
 * TODO_Comment
 *
 * @see ~TNCCSBatchBuffer() 
 * 
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>17.02.2008 - create class (ib)</li>
 *   <li>19.02.2008 - some comments, addTNCCSBatchFragment and getter (mbs)</li>
 *   <li>22.07.2009 - redesign 0.6.0 (mbs)</li>
 * </ul>
 *
 * @class TNCCSBatchBuffer
 * @brief TODO_Brief
 * @date 17.02.2008
 * @author Ingo Bente (ib)
 * @author Mike Steinmetz (mbs)
 */
class EapTncBuffer
{
public:
	
	/**
	 * Default constructor
	 */
	EapTncBuffer();
	
	/**
	 * Constructor. Sets the batch to tnccsBatchFragment;
	 * 
	 * @param tnccsBatchFragment The first batch fragment for this buffer.
	 */
	EapTncBuffer(const EapTncFragment &eapTncFragment);
	
	/**
	 * Copy constructor (flat copy).
	 *
	 * @param tnccsBatchBuffer The buffer that shall be copied.
	 */
	EapTncBuffer(const EapTncBuffer &tnccsBatchBuffer);
	
	/**
	 * Destructor. Does not free any memory. The caller must delete tnccsBatch
	 * (normally it is the Defragmentation).
	 * 
	 * @see getTNCCSBatch
	 */
	virtual ~EapTncBuffer();
	
	/**
	 * TODO_Comment
	 *
	 * @param enclosing_method_arguments
	 */
	EapTncBuffer &operator=(const EapTncBuffer &tnccsBatchBuffer);
	
	/**
	 * Adding a EapTncFragment behind at last fragment.
	 *
	 * @param batchFragment the TNCCS-Batch-Fragment
	 * @param isLast true if batchFragment is the last fragment
	 * 
	 * @trow 
	 */
	void addEapTncFragment(const EapTncFragment &fragment, bool isLast) throw (std::domain_error);
	
	/**
	 * Get the TNCCSBatch.
	 *
	 * @return the tnccsBatch
	 * 
	 * @see ~EapTncBuffer()
	 */
	iel::TNCCSData getTNCCSData() const;
	
	/**
	 * Get the current position of tnccsData is filled.
	 *
	 * @return the position
	 */
	TNC_UInt32 getPosition() const;
	
private:
	
	/**
	 * Pointer to the tnccsData
	 */
	iel::TNCCSData tnccsData;
	
	/**
	 * Current position in the tnccsData.
	 */
	TNC_UInt32 position;
};

} // namespace nal

} // namespace tncfhh

#endif /*EAPTNCBUFFER_H_*/
