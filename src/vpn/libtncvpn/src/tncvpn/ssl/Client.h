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

#ifndef SSL_CLIENT_H
#define SSL_CLIENT_H

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

namespace tnc {

namespace ssl {

enum {
	max_length = 1024
};


/**
 * Base class for all TLS related client functions. A few
 * parts of the code are based on the examples provides by
 * the boost asio examples - see
 * http://www.boost.org/doc/libs/1_36_0/doc/html/boost_asio/examples.html
 */
class Client {

protected:
	boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;
	char request_[max_length];
	char reply_[max_length];


public:
	/**
	 * Creates a ssl_client and initializes the socket and tries to establish
	 * a connection with the target host.
	 */
	Client(boost::asio::io_service& io_service, boost::asio::ssl::context& context,
	      boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
			: socket_(io_service, context) {

		boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
		socket_.lowest_layer().connect(endpoint);
		socket_.handshake(boost::asio::ssl::stream_base::client);
	}


	virtual ~Client()
	{
		socket_.lowest_layer().close();
	}
};
} // namespace ssl
} // namespace tnc

#endif
