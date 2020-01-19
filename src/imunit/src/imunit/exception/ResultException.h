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
#ifndef TNCFHH_IML_RESULTEXCEPTION_H_
#define TNCFHH_IML_RESULTEXCEPTION_H_


#include <exception>
#include <string>
#include <tcg/tnc/tncifimv.h>
#include <tcg/tnc/tncifimc.h>

namespace tncfhh
{

namespace iml
{

/**
 * Inherits from std::exception. Contains additional information as TNC_Result.
 *
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>07.02.2008 - create class (mbs)</li>
 *   <li>18.02.2008 - changed to ResultException (ib)</li>
 *   <li>16.06.2009 - redesign 0.6.0 (ib)</li>
 * </ul>
 *
 * @class ResultException
 * @brief An exception class with TNC_Result
 * @date 07.02.2008
 * @author Mike Steinmetz (mbs)
 */
class ResultException : public std::exception
{
public:

	/**
	 * Ctor.
	 *
	 * @param message A message (as std::string) providing information regarding the exception.
	 * @param returnValue A TNC_Result value that is of importance regarding the ResultException.
	 *
	 * @todo Change order of parameters to comply with other ctor.
	 */
	ResultException(std::string message, TNC_Result returnValue) throw();

	/**
	 * Ctor.
	 *
	 * @param returnValue A TNC_Result value that is of importance regarding the ResultException.
	 * @param formatString A message (as printf-like format string) providing information regarding the exception.
	 */
//	ResultException(TNC_Result returnValue, const char *formatString, ...);

	/**
	 * Destructor
	 */
	virtual ~ResultException() throw();

	/**
	 * Getter for @link #returnValue @endlink
	 */
	TNC_Result getReturnValue() const;

    /** Returns a C-style character string describing the general cause
     *  of the current error.  */
    virtual const char* what() const throw();

private:
	/**
	 * Message describing the exception.
	 */
    std::string message;

	/**
	 * The returnvalue for TNCC or TNCS.
	 */
	TNC_Result returnValue;

};

} // namespace iml

} // namespace tncfhh

#endif /*TNCFHH_IML_RESULTEXCEPTION_H_*/
