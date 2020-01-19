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

#include <iostream>
#include <string>

#include "EndpointDB.h"
#include "AssessmentScheduler.h"
#include "EnforcementManager.h"
#include "PEPSession.h"

#include <tncvpn/ssl/Server.h>
#include <tncvpn/libtnac/AllowDenyPacket.h>
#include <tncvpn/libtnac/TLVBuffer.h>


namespace tnc {

/** PEP daemon listen on port 12346 */
const short TNC_PEPD_PORT = 12346;

/**
 * The pep_server listens for incoming IF-PEP messages.
 */
class PEPServer: public ssl::Server {

private:
	/** The endpoint_db is passed to the session objects */
	tnc::EndpointDB *db;

public:

	/**
	 * Creates the server and awaits the first connection.
	 */
	PEPServer(boost::asio::io_service& io_service, tnc::EndpointDB *db) :
		ssl::Server(io_service, TNC_PEPD_PORT), db(db) {

		accept();
	}


	/**
	 * Accept a connection and create a corresponding pep_session object.
	 */
	void accept() {
		PEPSession* new_session = new PEPSession(io_service_, context_, db);

		// "Wait" for the first incoming client request
		acceptor_.async_accept(new_session->socket(), boost::bind(
				&PEPServer::handleAcceptCompleted, this, new_session,
				boost::asio::placeholders::error));

	}


	/**
	 * This method is invoked as far as a connection between PEP and PDP has
	 * been established. Creates a pep_session object for the connection and
	 * executes an accept call in order to handle further PDP recommendations.
	 */
	void handleAcceptCompleted(PEPSession* new_session,
			const boost::system::error_code& error) {
		if (!error) {

			// Handle the client
			new_session->doHandshake();
			std::cout << "[PEP daemon] Recommendation received " << new_session << std::endl;
			new_session = new PEPSession(io_service_, context_, db);


			// Await the next connection
			acceptor_.async_accept(new_session->socket(), boost::bind(
					&PEPServer::handleAcceptCompleted, this, new_session,
					boost::asio::placeholders::error));
		} else {
			delete new_session;
		}
	}

};

}
