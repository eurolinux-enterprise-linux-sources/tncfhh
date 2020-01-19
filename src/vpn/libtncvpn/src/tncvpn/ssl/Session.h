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

#ifndef SESSION_H
#define SESSION_H

#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

namespace tnc {

namespace ssl {
	
typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_socket;
	
/**
 * Base class for all TLS session related boost methods.
 * A few parts of the code are based on the examples provides
 * by the boost asio examples - see
 * http://www.boost.org/doc/libs/1_36_0/doc/html/boost_asio/examples.html
 */
class Session {

protected:
	ssl_socket socket_;
	enum { max_length = 1024 };
	char data_[max_length];


public:
	/**
	 *Initializes the socket for the TLS session.
	 */
	Session (boost::asio::io_service& io_service, boost::asio::ssl::context& context)
		: socket_(io_service, context) {}

	virtual ~Session() { }


	/**
	 * Returns the underlying socket
	 */
	ssl_socket::lowest_layer_type& socket() {
		return socket_.lowest_layer();
	}


	/**
	 * Start with the handshake
	 */
	void doHandshake() {
		std::cout << "[Session] socket handshake" << std::endl;
		socket_.handshake(boost::asio::ssl::stream_base::server);
		handleClient();
	}


	virtual void handleClient() = 0;
};
	
} // namespace ssl

} // namespace tnc

#endif
