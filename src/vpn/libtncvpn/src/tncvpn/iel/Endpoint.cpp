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

#include "Endpoint.h"

namespace tnc {

/*
 * See the header file for a description of the methods.
 */

Endpoint::Endpoint(boost::asio::ip::address address)
	: address(address) {

	// Initialize with current time
	last_assessment = time(NULL);
}


Endpoint::Endpoint(const char* ip) {

	// Create a boost address object by a char*
	address = boost::asio::ip::address::from_string(ip);

	// Initialize with current time
	last_assessment = time(NULL);
}

Endpoint::~Endpoint() {

}


boost::asio::ip::address*
Endpoint::getAddress() {
	return &address;
}

const time_t*
Endpoint::getLastAssessment() const {
	return &last_assessment;
}

}
