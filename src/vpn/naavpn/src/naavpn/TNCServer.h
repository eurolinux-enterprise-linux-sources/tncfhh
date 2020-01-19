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

#ifndef TNCSERVER_H
#define TNCSERVER_H

#include "tncvpn/ssl/Server.h"
#include "TNCSession.h"

namespace tnc {

/**
 * The tnc_server extends the ssl_server object in order to
 * inherit also the TLS related functions. Accepts TLS connections
 * from the Access Requestors
 */
class TNCServer: public tnc::ssl::Server {

public:

	/**
	 * Initializes the tnc_server object and awaits endpoint
	 * connections.
	 */
	TNCServer(boost::asio::io_service& io_service);

	/**
	 * Await a connection attempt.
	 */
	void accept();

	/**
	 * This method is invoked as far as a client connection has been established.
	 * Creates a tnc_session object for that connection and performs an accept call
	 * in order to handle further client requests.
	 */
	void handleAccept(TNCSession* new_session, const boost::system::error_code& error);

};

}

#endif

