/*
 * This software is Copyright (C) 2010-2011
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

#ifndef ENDPOINT_H
#define ENDPOINT_H

#include <string>
#include <ctime>

#include <boost/asio.hpp>


namespace tnc {


/**
 * Represents an Access Requestor identified by an IP address.
 * Stores an additional attribute which indicates the time of the
 * last assessment.
 */
class Endpoint {
	boost::asio::ip::address address;
	time_t last_assessment;

public:
	/**
	 * Creates an new Endpoint based on the IP address.
	 */
	Endpoint(boost::asio::ip::address);

	/**
	 * Creates an new Endpoint based on the IP address.
	 */
	Endpoint(const char*);
	virtual ~Endpoint();


	/**
	 * Returns the IP address of an Endpoint.
	 */
	boost::asio::ip::address* getAddress();


	/**
	 * Returns the timestamp of the last assessment.
	 */
	const time_t* getLastAssessment() const;
};

}

#endif
