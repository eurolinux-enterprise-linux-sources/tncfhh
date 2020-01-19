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

#ifndef SERVER_H
#define SERVER_H

#include <tncutil/Configuration.h>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

namespace tnc {

namespace ssl {

/**
 * Handles incoming SSL request and redirects them
 * to the tnc_session object.
 */
class Server {

protected:
    boost::asio::io_service& io_service_;
    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::ssl::context context_;

    /**
     * SSL password callback, just a dummy password. The certificates
     * are not intended to be used in production environments since
     * they are taken from the boost examples.
     */
    std::string getPassword() const {
      return tncfhh::Configuration::instance()->get("SERVER_KEY_PASSWORD");
    }

public:

	/**
	 * Initializes the TLS context (including the certificates)
	 */
	Server(boost::asio::io_service& io_service, unsigned short port) :
		io_service_(io_service),
		acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
		context_(io_service, boost::asio::ssl::context::sslv23)
	{
		// Initializing the SSL context object
		context_.set_options(
				boost::asio::ssl::context::default_workarounds
				| boost::asio::ssl::context::no_sslv2
				| boost::asio::ssl::context::single_dh_use);

		context_.set_password_callback(boost::bind(&Server::getPassword, this));
		context_.use_certificate_chain_file(tncfhh::Configuration::instance()->get("SERVER_KEY"));
		context_.use_private_key_file(tncfhh::Configuration::instance()->get("SERVER_KEY"), boost::asio::ssl::context::pem);
		context_.use_tmp_dh_file(tncfhh::Configuration::instance()->get("DH_FILE"));
	}

};

} // namespace ssl

} // namespace tnc

#endif
