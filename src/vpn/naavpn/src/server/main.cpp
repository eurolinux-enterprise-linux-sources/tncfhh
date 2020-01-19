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


#include "../naavpn/TNCServer.h"
#include <tncutil/Configuration.h>

#include <tncs/iel/Coordinator.h>

/**
 * main function of the NAL-TLS enabled Policy Decision Point.
 */
int main(int argc, char* argv[]) {

	// We expect the host and port number as parameters
	if (argc != 2) {
		std::cerr << "Usage: pdp <configfile>\n";
		return 1;
	}

	try {
		// read the configuration file for the naavpn
		std::string filename = argv[1];
		tncfhh::Configuration* config = tncfhh::Configuration::instance();
		config->addConfigurationFile(filename);

		// Initialize the NAL module, including the TLS socket
		boost::asio::io_service io_service;
		tnc::TNCServer s(io_service);


		// Starting the TNC server (IEL service)
		tncfhh::iel::coordinator.initialize();

		// Starting the NAL service
		s.accept();
		io_service.run();

	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}



