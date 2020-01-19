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

#include "TNCCTNCSMessageXML.h"

#include <tncutil/XercesString.h>

#include <log4cxx/logger.h>

namespace tncfhh
{

namespace iel
{

namespace tnc1
{

/* for logging */
static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("TNCS.TNC1.TNCCTNCSMessageXML"));

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNCCTNCSMessageXML::TNCCTNCSMessageXML(const TNCCTNCSMessageXML& m) throw (std::runtime_error)
:TNCCTNCSMessage(m)
{
	throw std::runtime_error("Operation copy TNCCTNCSMessageXML not allowed (yet)!");
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNCCTNCSMessageXML& TNCCTNCSMessageXML::operator=(const TNCCTNCSMessageXML&) throw (std::runtime_error)
{
	throw std::runtime_error("Operation = to TNCCTNCSMessageXML not allowed (yet)!");
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNCCTNCSMessageXML::TNCCTNCSMessageXML(TNC_MessageType type, xercesc::DOMElement * xml) throw (std::runtime_error)
	:TNCCTNCSMessage(type), doc(NULL)
{
	/* check parameter */
	if (!xml)
		throw std::runtime_error("TNCCTNCSMessageXML::TNCCTNCSMessageXML: invalid parameter: null pointer");

	/* get THE XerxesC implementation */
	xercesc::DOMImplementation * impl = xercesc::DOMImplementationRegistry::getDOMImplementation(XercesString("LS").c_str());
	if (!impl)
		throw std::runtime_error("TNCCTNCSMessageXML::constructor: Xerces error: No DOMImplementation LS found!");

	// cleate a new XML-document
	this->doc = impl->createDocument();

	// (deep) copy the XML node and add as root
	this->doc->appendChild(this->doc->importNode(xml, true));
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNCCTNCSMessageXML::TNCCTNCSMessageXML(TNC_MessageType type, xercesc::DOMDocument * doc) throw (std::runtime_error)
	:TNCCTNCSMessage(type), doc(doc)
{
	/* check parameter */
	if (!doc)
		throw std::runtime_error("TNCCTNCSMessageXML::TNCCTNCSMessageXML: invalid parameter: null pointer");
	else if (!doc->getDocumentElement()) {
		doc->release();
		throw std::runtime_error("TNCCTNCSMessageXML::TNCCTNCSMessageXML: invalid parameter (root): null pointer");
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNCCTNCSMessageXML::~TNCCTNCSMessageXML()
{
	if (this->doc)
		this->doc->release();
	this->doc = NULL;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
xercesc::DOMElement * TNCCTNCSMessageXML::getXML()
{
	return this->doc->getDocumentElement();
}

} // namespace tnc1

} // namespace iel

} // namespace tncfhh
