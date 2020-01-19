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

#ifndef EAPTNCFRAGMENT_H_
#define EAPTNCFRAGMENT_H_

#include <tcg/tnc/tncifimv.h>
#include <tcg/tnc/fhhaddon.h>
#include <stdexcept>

namespace tncfhh
{

namespace nal
{

/**
 * This Class represent a EAP-TNC Packet. A EAP-TNC packet is green color-marked in
 * following figure. This has all information about a EAP-TNC packet, except for
 * some flags and version.
 * <pre>
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |     Code      | Identifier    |            Length             |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |      Type     |<span style="background-color: lightgreen;" title="green area">  Flags  | Ver |       TNCCS Data Length       |</span>
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * <span style="background-color: lightgreen;" title="green area">|       TNCCS Data Length       |            Data ...           </span>|
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * </pre>
 * @see https://www.trustedcomputinggroup.org/specs/TNC/TNC_IFT_v1_1_r10.pdf page 29
 * 
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>17.02.2008 - create class (ib)</li>
 *   <li>18.02.2008 - add some comments and methods (mbs)</li>
 *   <li>22.07.2009 - redesign 0.6.0 (mbs)</li>
 * </ul>
 *
 * @class EapTncFragment
 * @brief a fragmented EAP-TNC message
 * @date 17.02.2008
 * @author Ingo Bente (ib)
 * @author Mike Steinmetz (mbs)
 */
class EapTncFragment
{
public:
	
	/**
	 * Ctor for EapTncFragment.
	 *
	 * @param fragment Data Pointer to the EAP-TNC packet fragment (deep copy)
	 * @param fLength Length of the EAP-TNC packet fragment
	 */
	EapTncFragment(TNC_BufferReference fragment, TNC_UInt32 fLength) throw (std::invalid_argument);
	
	/**
	 * Create a EAP-TNC-Fragmented Message. With getFragment() you can get
	 * the EAP-Data.
	 *
	 * @see https://www.trustedcomputinggroup.org/specs/TNC/TNC_IFT_v1_1_r10.pdf page 29
	 * @see getFragment()
	 * 
	 * @param fragment Pointer to the data in EAP-TNC packet fragment (deep copy)
	 * @param fdLength Length of the data
	 * @param lengthIncluded if dataLength is not 0 (null)
	 * @param dataLength the data length (see specification)
	 * @param moreFragments if more EapTncFragments follow
	 */
	EapTncFragment(TNC_BufferConstReference data, TNC_UInt32 dataLength, bool lengthIncluded, TNC_UInt32 TNCCSDataLength, bool moreFragments) throw (std::invalid_argument);

	/**
	 * Copy Constructor.
	 * Create a EAP-TNC-Fragmented message from another EAP-TNC-Fragmented message.
	 *
	 * @param source the source of copy
	 */
	EapTncFragment(const EapTncFragment & source);

	/**
	 * Dtor for EapTncFragment.
	 */
	virtual ~EapTncFragment();
	
	EapTncFragment & operator=(const EapTncFragment & source);

	/**
	 * Pointer (red) to the data (green) of the current fragment.
	 * 
	 * <pre>
	 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	 * |     Code      | Identifier    |            Length             |
	 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	 * |      Type     |  Flags  | Ver |       TNCCS Data Length       |
	 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	 * |       TNCCS Data Length       |<span style="background-color: lightgreen;" title="green area">            	 ...           </span>|
	 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+<span style="color: red;">^</span>+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	 *                                  <span style="color: red;">|</span>
	 *                              <span style="color: red;" title="pointer">fragmentData</span>
	 * </pre>
	 * @see https://www.trustedcomputinggroup.org/specs/TNC/TNC_IFT_v1_1_r10.pdf page 29
	 * @see getDataLength()
	 *
	 * @return the data from this fragment
	 */
	TNC_BufferReference getData() const;

	/**
	 * Length of the data (with green background) of the current fragment.
	 * 
	 * <pre>
	 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	 * |     Code      | Identifier    |            Length             |
	 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	 * |      Type     |  Flags  | Ver |       TNCCS Data Length       |
	 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	 * |       TNCCS Data Length       |<span style="background-color: lightgreen;" title="green area">            Data ...           </span>|
	 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	 * </pre>
	 * @see https://www.trustedcomputinggroup.org/specs/TNC/TNC_IFT_v1_1_r10.pdf page 29
	 * @see getData()
	 * 
	 * @return the length of data in <b>this</b> fragment
	 */
	TNC_UInt32 getDataLength() const;

	/**
	 * Pointer (red) to the current fragment (green).
	 * 
	 * <pre>
	 *              <span style="color: red;" title="pointer">fragment</span>
	 *                  <span style="color: red;">|</span>
	 * +-+-+-+-+-+-+-+-+<span style="color: red;">|</span>+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	 * |     Code      |<span style="color: red;">|</span> Identifier   |            Length             |
	 * +-+-+-+-+-+-+-+-+<span style="color: red;">V</span>+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	 * |      Type     |<span style="background-color: lightgreen;" title="green area">  Flags  | Ver |       TNCCS Data Length       |</span>
	 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	 * <span style="background-color: lightgreen;" title="green area">|       TNCCS Data Length       |            Data ...           </span>|
	 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	 * </pre>
	 * @see https://www.trustedcomputinggroup.org/specs/TNC/TNC_IFT_v1_1_r10.pdf page 29
	 * @see getFragmentLength()
	 * 
	 * @return this fragment
	 */
	TNC_BufferConstReference getFragment() const;
	
	/**
	 * Length of the current fragment (with green background).
	 * 
	 * <pre>
	 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	 * |     Code      | Identifier    |            Length             |
	 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	 * |      Type     |<span style="background-color: lightgreen;" title="green area">  Flags  | Ver |       TNCCS Data Length       |</span>
	 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	 * <span style="background-color: lightgreen;" title="green area">|       TNCCS Data Length       |            Data ...           </span>|
	 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	 * </pre>
	 * @see https://www.trustedcomputinggroup.org/specs/TNC/TNC_IFT_v1_1_r10.pdf page 29
	 * @see getFragment()
	 * 
	 * @return the length of <b>this</b> fragment
	 */
	TNC_UInt32 getFragmentLength() const;
	
	/**
	 * Accumulated length of all fragments for this TNCCS message (the value
	 * of green colored field). Only present in the first fragment. In any
	 * other fragment, this value is set to 0.
	 * 
	 * <pre>
	 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	 * |     Code      | Identifier    |            Length             |
	 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	 * |      Type     |  Flags  | Ver |<span style="background-color: lightgreen;" title="green area">       TNCCS Data Length       |</span>
	 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	 * <span style="background-color: lightgreen;" title="green area">|       TNCCS Data Length       </span>|            Data ...           |
	 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	 * </pre>
	 * @see https://www.trustedcomputinggroup.org/specs/TNC/TNC_IFT_v1_1_r10.pdf page 29
	 *
	 * @return the data length about 'all' coherently fragments (only set for
	 *         the fist message)
	 */
	TNC_UInt32 getTNCCSDataLength() const;
	
	/**
	 * Length included flag
	 * 
	 * <pre>
	 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	 * |     Code      | Identifier    |            Length             |
	 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	 * |      Type     |<span style="background-color: lightgreen;" title="green area"> </span> Flags  | Ver |       TNCCS Data Length       |
	 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	 * |       TNCCS Data Length       |            Data ...           |
	 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	 * </pre>
	 * @see https://www.trustedcomputinggroup.org/specs/TNC/TNC_IFT_v1_1_r10.pdf page 29
	 *
	 * @return if more fragments following
	 */
	bool hasLengthIncluded() const;
	
	/**
	 * Flag that indicates if there come more fragments after the current one. Must NOT be set on the
	 * last fragment. If a fragment with this flag set is received, an ACK has to be sent. (That is,
	 * the reception of the last fragment does not result in an ACK!)
	 * 
	 * <pre>
	 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	 * |     Code      | Identifier    |            Length             |
	 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	 * |      Type     |  <span style="background-color: lightgreen;" title="green area">F</span>lags  | Ver |       TNCCS Data Length       |
	 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	 * |       TNCCS Data Length       |            Data ...           |
	 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	 * </pre>
	 * @see https://www.trustedcomputinggroup.org/specs/TNC/TNC_IFT_v1_1_r10.pdf page 29
	 *
	 * @return if more fragments following
	 */
	bool hasMoreFragments() const;
	
private:
	
	/**
	 * @see getFragment()
	 */
	TNC_BufferReference fragment;
	
	/**
	 * @see getFragmentLength()
	 */
	TNC_UInt32 fragmentLength;
	
	/**
	 * @see getTNCCSDataLength()
	 */
	TNC_UInt32 TNCCSDataLength;
	
	/**
	 * @see hasLengthIncluded()
	 */
	bool lengthIncluded;
	
	/**
	 * @see hasMoreFragments()
	 */
	bool moreFragments;
};

} // namespace nal

} // namespace tncfhh

#endif /*EAPTNCFRAGMENT_H_*/
