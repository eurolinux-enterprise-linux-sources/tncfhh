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

#include "EndpointDB.h"


namespace tnc {

/*
 * See the header file for a description of the methods.
 */

EndpointDB::EndpointDB() {

}

EndpointDB::~EndpointDB() {

}


void
EndpointDB::add(Endpoint *ep) {
	boost::asio::ip::address* addr = ep->getAddress();

	unsigned long conn_id;

	// Only IPv4 is supported at the moment
	if (addr->is_v4()) {
		conn_id = addr->to_v4().to_ulong();
	} else if(addr->is_v6()) {
		std::cerr << "IPv6 isn't support!" << std::endl;
		return;
	}

	// Add the endpoint to the db
	endpoints[conn_id] = ep;
}


void
EndpointDB::remove(Endpoint *ep) {

}

EP_HashMap*
EndpointDB::getEndpoints() {
	return &endpoints;
}

void
EndpointDB::printAllEndpoints() const {
	for(EP_HashMap::const_iterator it = endpoints.begin(); it != endpoints.end(); ++it) {
//		struct tm* ts = localtime(it->second->getLastAssessmentTime());
//		printf("Item found for IP: %d\n", it->second->getIP()->getHostAddress());
//		printf("Item found: %d\n", it->first);

		std::cout << "[Endpoint DB] Endpoint: " << it->second->getAddress()->to_string() << std::endl;
	}
}


}
