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
#include "XercesString.h"
#include <xercesc/util/XMLString.hpp>

namespace tncfhh
{

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *                  XercesString::XercesString(const char*)                  *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

XercesString::XercesString(const char * str)
{
//	std::cout << "XercesString::ctor" << std::endl;
	XMLCh * xstr = xercesc::XMLString::transcode(str);
	this->operator=(xstr);
	xercesc::XMLString::release(&xstr);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *                XercesString::XercesString(const std::string&)             *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
XercesString::XercesString(const std::string & str)
{
	XMLCh * xstr = xercesc::XMLString::transcode(str.c_str());
	this->operator=(xstr);
	xercesc::XMLString::release(&xstr);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *                      XercesString::XercesString(const XMLCh*)             *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
XercesString::XercesString(const XMLCh * xstr)
	:std::basic_string<XMLCh>(xstr)
{
//	std::cout << "XercesString::c-ctor" << std::endl;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *                        XercesString::~XercesString()                      *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
XercesString::~XercesString()
{
//	std::cout << "XercesString::dtor" << std::endl;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *         XercesString & XercesString::operator=(const XMLCh * xstr)        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
XercesString & XercesString::operator=(const XMLCh * xstr)
{
	std::basic_string<XMLCh>::operator=(xstr);
	return *this;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *           std::string& XercesString::copyToString(std::string&)           *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
std::string & XercesString::copyToString(std::string & sstr)
{
	const char * str = xercesc::XMLString::transcode(this->c_str());
	sstr.operator=(str);
	delete str;
	return sstr;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *                    std::string XercesString::toString()                   *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
std::string XercesString::toString()
{
	const char * str = xercesc::XMLString::transcode(this->c_str());
	std::string sstr(str);
	delete str;
	return sstr;
}

} // tncfhh
