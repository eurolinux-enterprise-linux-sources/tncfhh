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
#ifndef TNCS_TNCCTNCSMESSAGEXML_H_
#define TNCS_TNCCTNCSMESSAGEXML_H_

#include "TNCCTNCSMessage.h"
#include <stdexcept>
//#include "../../exception/TNCCSProtocolNotSupportedException.h"

#include <xercesc/dom/DOM.hpp>

namespace tncfhh {

namespace iel {

namespace tnc1 {

/**
 * This Class represent an TNCC-TNCS-Message with XML data. This message
 * is specified in TNC IF-TNCCS.
 * 
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>05.03.2008 - create class (mbs)</li>
 *   <li>20.07.2009 - redesign for 0.6.0 (mbs)</li>
 *   <li>28.08.2009 - redesign the small classes (remove xml)
 *   	and write doc (mbs)</li>
 * </ul>
 *
 * @class TNCCTNCSMessageXML
 * @brief Represent a TNCC-TNCS-Message with XML data
 * @date 05.03.2008
 * @author Mike Steinmetz (mbs)
 * @see TNCCTNCSMessage
 * @see TNCCTNCSMessageBase64
 */
class TNCCTNCSMessageXML : public TNCCTNCSMessage
{
public:
	/**
	 * Create an TNCCTNCSMessageXML based on an XML element.
	 *
	 * @param type The MessageType (see spec).
	 * @param xml Create an deep copy from this XML document.
	 */
	TNCCTNCSMessageXML(TNC_MessageType type, xercesc::DOMElement * xml) throw (std::runtime_error);

	/**
	 * Create an TNCCTNCSMessageXML based on a DOM document. The root element
	 * of this document is append below XML tag in TNCC-TNCS-Message (see spec).
	 *
	 * <b>NOTE:</b> Please do not release the DOMDocument, because this class
	 * release the parameter <code>doc</code>.
	 *
	 * @param type The MessageType (see spec).
	 * @param doc DOMDucument with root element (this released by this class).
	 */
	TNCCTNCSMessageXML(TNC_MessageType type, xercesc::DOMDocument * doc) throw (std::runtime_error);
	
	/**
	 *
	 */
	virtual ~TNCCTNCSMessageXML();

	/**
	 * Get the DOM document below the XML tag in TNCC-TNCS-Message (see
	 * IF-TNCCS specification).
	 *
	 * @return The XML content. Return <code>NULL</code> if no XML content found.
	 *
	 */
	virtual xercesc::DOMElement * getXML();

private:
	/**
	 * This Constructor is not allowed.
	 */
	TNCCTNCSMessageXML(const TNCCTNCSMessageXML&) throw (std::runtime_error);

	/**
	 * This Function is not allowed.
	 */
	TNCCTNCSMessageXML& operator=(const TNCCTNCSMessageXML&) throw (std::runtime_error);

	/**
	 * The document that contain the 'any' XML tag as root element.
	 */
	xercesc::DOMDocument * doc;
};

}  // namespace tnc1

}  // namespace iel

}  // namespace tncfhh

#endif /*TNCCTNCSMESSAGEXML_H_*/
