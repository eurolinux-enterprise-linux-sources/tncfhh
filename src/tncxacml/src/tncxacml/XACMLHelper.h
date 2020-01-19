/*
 * This software is Copyright (C) 2006-2011
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

#ifndef XACMLHELPER_H_
#define XACMLHELPER_H_

#include <tcg/tnc/tncifimv.h>
#include <tncutil/XercesString.h>

// Mandatory for using any feature of Xerces.
#include <xercesc/util/PlatformUtils.hpp>

// Use the Document Object Model (DOM) API
#include <xercesc/dom/DOM.hpp>

// Required for outputing a Xerces DOMDocument to a standard output stream (Also see: XMLFormatTarget)
#include <xercesc/framework/StdOutFormatTarget.hpp>

// Required for outputing a Xerces DOMDocument to the file system (Also see: XMLFormatTarget)
#include <xercesc/framework/LocalFileFormatTarget.hpp>

#include <xercesc/parsers/XercesDOMParser.hpp>

// The following includes are only used to create sample data in this tutorial. If you don't need the sample data, then you don't need these headers.
#include <string>
#include <sstream>

/**
 * Handling of the XACML-network traffic
 */
#include <iostream>
#include <boost/asio.hpp>

XERCES_CPP_NAMESPACE_USE

namespace tncfhh {

namespace iml {

/**
 * Class that .
 *
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>17.01.2011 - first version (bhl)</li>
 * </ul>
 *
 * @date 17.01.2011
 * @author Bastian Hellmann (bhl)
 */
class XACMLHelper {
public:
	static xercesc::DOMDocument* createRequest();

	static xercesc::DOMElement* createSubject(/*in*/ xercesc::DOMDocument* request);

	static xercesc::DOMElement* createSubject(/*in*/ xercesc::DOMDocument* request, /*in*/ std::string subjectCategory);

	static void addResourceActionEnvironmentToRequest(/*in*/ xercesc::DOMDocument* request);

	static xercesc::DOMElement* createAttribute(/*in*/ xercesc::DOMDocument* request, /*in*/ std::string attributeID, /*in*/ std::string dataType, /*in*/ TNC_BufferReference value);

	static xercesc::DOMElement* createAttribute(/*in*/ xercesc::DOMDocument* request, /*in*/ std::string attributeID, /*in*/ std::string dataType, /*in*/ std::string value);

	static void addSubjectToRequest(/*in*/ xercesc::DOMDocument* request, /*in*/ xercesc::DOMElement* subject);

	static void addAttributeToSubject(/*in*/ xercesc::DOMElement* subject, /*in*/ xercesc::DOMElement* attribute);

	static TNC_IMV_Action_Recommendation getXACMLRecommendation(/*in*/ xercesc::DOMDocument* request);

	static std::string writeRequestToString(/*in*/ xercesc::DOMDocument* request);

	XACMLHelper();
	virtual ~XACMLHelper();

private:
	static std::string exchangeXACMLData(/*in*/ xercesc::DOMDocument* request);

	static xercesc::DOMDocument* parseIncomingXMLData(/*in*/ std::string incomingString);

	static TNC_IMV_Action_Recommendation parseResponse(/*in*/ xercesc::DOMDocument* response);

	static std::string getObligation(/*in*/ DOMDocument* response);

	class XercesInit {
		public:
			XercesInit();
			~XercesInit();
	};

	static XercesInit xercesInit;
};

} // namespace iml

} // namespace tncfhh

#endif /* XACMLHELPER_H_ */
