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

#include "TNCServer.h"
#include <tncutil/Configuration.h>


#define LOGNAME "[TNCServer]"
#include <log4cxx/logger.h>
static log4cxx::LoggerPtr logger = log4cxx::Logger::getLogger(LOGNAME);

namespace tnc {

const short tncServerPort() {
	short i;
	std::istringstream iss(tncfhh::Configuration::instance()->get("PDP_PORT"));
	iss >> i;
	return i;
}
	
TNCServer::TNCServer(boost::asio::io_service& io_service) :
	tnc::ssl::Server(io_service, tncServerPort()) {

	//accept();
}
	
void TNCServer::accept()  {
	TNCSession* new_session = new TNCSession(io_service_, context_);
	// "Wait" for the first incoming client request
	acceptor_.async_accept(new_session->socket(), boost::bind(
			&TNCServer::handleAccept, this, new_session,
			boost::asio::placeholders::error));
}

void TNCServer::handleAccept(TNCSession* new_session, const boost::system::error_code& error) {
	if (!error) {
		// create a new session to accept
		TNCSession* another_session = new TNCSession(io_service_, context_);
		// this calls immediately returns
		acceptor_.async_accept(another_session->socket(), boost::bind(
				&TNCServer::handleAccept, this, another_session,
				boost::asio::placeholders::error));

		// Handle the client connection and create a corresponding
		// session object for the endpoint.
		LOG4CXX_INFO(logger, "New Client Connection");
		new_session->doHandshake();
	}
	LOG4CXX_INFO(logger, "Remove Client Connection");
	delete new_session;
}

}
