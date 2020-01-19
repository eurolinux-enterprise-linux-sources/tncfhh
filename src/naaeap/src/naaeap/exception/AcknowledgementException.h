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

#ifndef ACKNOWLEDGEMENTEXCEPTION_H_
#define ACKNOWLEDGEMENTEXCEPTION_H_

#include <exception>

namespace tncfhh {

namespace nal {

/**
 * TODO_Comment
 *
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>22.07.2009 - create class(mbs)</li>
 * </ul>
 *
 * @class AcknowledgementException
 * @brief TODO_Brief
 * @date 22.07.2009
 * @author Mike Steinmetz (mbs)
 */
class AcknowledgementException : public std::exception {
public:
	AcknowledgementException() throw ();
	virtual ~AcknowledgementException() throw ();
};

}

}

#endif /* ACKNOWLEDGEMENTEXCEPTION_H_ */
