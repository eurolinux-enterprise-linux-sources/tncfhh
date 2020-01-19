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
 * For std::string + X.
 *
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>12.07.2009 - create & implement functions (mbs)</li>
 *   <li>20.07.2009 - added namespace (ib)</li>
 * </ul>
 *
 * @file string_helper.h
 * @date 12.07.2009
 * @author Mike Steinmetz (mbs)
 */

#ifndef STRING_HELPER_H_
#define STRING_HELPER_H_

#include <sstream>

namespace tncfhh
{

/* for std::string + std::string */
inline std::string operator+(std::string const& l, std::string const& r)
{
	std::stringstream s;
	s<<l<<r;
	return s.str();
}

/* for std::string + unsigned int */
inline std::string operator+(std::string const& l, unsigned int const& r)
{
	std::stringstream s;
	s<<l<<r;
	return s.str();
}

/* for std::string + "" */
inline std::string operator+(std::string const& l, char const r[])
{
	std::stringstream s;
	s<<l<<r;
	return s.str();
}

/* for std::string + pointer */
inline std::string operator+(std::string const& l, const void * r)
{
	std::stringstream s;
	s<<l<<r;
	return s.str();
}

} // namespace tncfhh

#endif /*STRING_HELPER_H_*/
