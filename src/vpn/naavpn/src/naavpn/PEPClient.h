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

#ifndef PEPCLIENT_H
#define PEPCLIENT_H

#include "tncvpn/ssl/Client.h"
#include "tncvpn/libtnac/AllowDenyPacket.h"

#include <iostream>

namespace tnc {

/**
 * The pep_client class is responsible for sending an IF-PEP
 * message to the Policy Enforcement Point. The class extends
 * the tnc::ssl::Client base class since it sends the messages through
 * a TLS encrypted tunnel.
 */
class PEPClient : public tnc::ssl::Client {

private:
	/** Recommendation flag
	 * 		N: No access will be granted
	 * 		Y: Access will be granted
	 */
	char recommendation;

	/** Access Requestor IP address */
	boost::asio::ip::address *address;


public:

	/**
	 * Default constructor, just initializes the pep_client class
	 */
	PEPClient(boost::asio::io_service& io_service,
			boost::asio::ssl::context& context,
			boost::asio::ip::tcp::resolver::iterator endpoint_iterator,
			boost::asio::ip::address *address,
			char recommendation);

	/**
	 * Creates an IF-PEP message and sends it to the Policy Enforcement
	 * Point. The contents of this methods will be adapted in the future
	 * in order to support IF-PEP binding to RADIUS.
	 *
	 * This method gets invoked as far as the SSL handshake successfully returns.
	 */
	void handleHandshakeCompleted();

	/**
	 * Indicates that the IF-PEP message was sent to the PEP. Just used to print a
	 * log message to on stdout.
	 */
	void handleWrite(const boost::system::error_code& error, size_t bytes_transferred);

};

}

#endif
