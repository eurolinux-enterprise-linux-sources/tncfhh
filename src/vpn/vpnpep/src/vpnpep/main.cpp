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

#include <boost/thread.hpp>

#include <tncutil/Configuration.h>
#include "PEPServer.h"

/**
 * The PEP daemon main method
 */
int main(int argc, char **argv) {
	// We expect the host and port number as parameters
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <configfile>\n";
		return 1;
	}

	std::cout << "[PEP daemon] Awaiting IF-PEP messages" << std::endl;

	tnc::EndpointDB db;

	tnc::AssessmentScheduler scheduler(&db);
	boost::thread* scheduler_thread = 0;

	// Creating and starting the assessment scheduler in an own thread
	scheduler_thread = new boost::thread(scheduler);

	try {
		// read the configuration file for the naavpn
		std::string filename = argv[1];
		tncfhh::Configuration* config = tncfhh::Configuration::instance();
		config->addConfigurationFile(filename);

		boost::asio::io_service io_service;
		tnc::PEPServer s(io_service, &db);
		io_service.run();

		// Wait for the thread to finish
		scheduler_thread->join();
	}
	catch (std::exception& e) {
		std::cerr << "[PEP daemon] Exception: " << e.what() << "\n";
	}


	return 0;
}
