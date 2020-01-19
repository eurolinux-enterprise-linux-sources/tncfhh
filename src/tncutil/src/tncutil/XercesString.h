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
#ifndef XERCESSTRING_H_
#define XERCESSTRING_H_

#include <string>
#include <xercesc/util/XercesDefs.hpp>

namespace tncfhh
{

/**
 * Class for mapping between C/C++ strings and Xerces Strings.
 *
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>26.02.2008 - create class (mbs)</li>
 *   <li>20.07.2009 - change namespace (mbs)</li>
 * </ul>
 *
 * @class XercesString
 * @date 26.02.2008
 * @author Mike Steinmetz (mbs)
 */
class XercesString : public std::basic_string<XMLCh>
{
public:

	/**
	 * Ctor.
	 *
	 * @param const char*
	 *
	 */
	XercesString(const char * str);

	/**
	 * Ctor.
	 *
	 * @param const std::string&
	 *
	 */
	XercesString(const std::string & str);

	/**
	 * Ctor.
	 *
	 * @param const XMLCh*
	 *
	 */
	XercesString(const XMLCh * xstr);

	/**
	 * Dtor.
	 *
	 * @param
	 *
	 */
	virtual ~XercesString();

	/**
	 * Operator=
	 *
	 * @param xstr
	 *
	 * @return return_type
	 */
	virtual XercesString & operator=(const XMLCh * xstr);

	/**
	 * Copy content of this to sstr.
	 *
	 * @param sstr
	 *
	 * @return return_type
	 */
	virtual std::string & copyToString(std::string & sstr);

	/**
	 * Get a std::string.
	 *
	 * @return return_type
	 */
	virtual std::string toString();
};

} // tncfhh

#endif /*TNCS_XERCESSTRING_H_*/
