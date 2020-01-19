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

#include "TNCClient.h"
#include <tncutil/Configuration.h>

/**
 * Starts the demo prototype of the TNC related part of the
 * Access Requestor.
 */
int main(int argc, char* argv[]) {
	try {
		// We expect the host and port number as parameters
		if (argc != 2) {
			std::cerr << "Usage: " << argv[0] << " <config>\n";
			return 1;
		}

		// read the configuration file for the naavpn
		std::string filename = argv[1];
		tncfhh::Configuration* config = tncfhh::Configuration::instance();
		config->addConfigurationFile(filename);
		config->get("VERIFY_FILE");

		// Initialize the boost networking related parts
		boost::asio::io_service io_service;
		boost::asio::ip::tcp::resolver resolver(io_service);
		boost::asio::ip::tcp::resolver::query query(
				config->get("PDP_ADDR"),
				config->get("PDP_PORT"));


		boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);
		boost::asio::ssl::context ctx(io_service, boost::asio::ssl::context::sslv23);
		ctx.set_verify_mode(boost::asio::ssl::context::verify_peer);
		ctx.load_verify_file(config->get("VERIFY_FILE"));

		// Create the TNC client
		tnc::TNCClient c(io_service, ctx, iterator);
		// start the tnc client
		c.doOperations();

	} catch (...) {
		std::cerr << "Exception.....: " << std::endl;
	}

	std::cerr << "Huh, is it over? Can I go now? Please..." << std::endl;

	return 0;
}
