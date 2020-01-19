/*
 * This software is Copyright (C) 2006-2011
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

#ifndef CONFIGURATIONSERVICE_H
#define CONFIGURATIONSERVICE_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include <boost/thread.hpp>

typedef std::vector<std::pair<std::string,std::string> > property_t;

namespace tncfhh {

/**
 * Singleton implementation of a configuration service object. This
 * implementation can be used as an interface to a central LDAP server.
 *
 */
class ConfigurationService {

private:

	property_t properties;


	// private default contructor since it is a singleton
	ConfigurationService() {
		readConfiguration();
	}

	// private copy contructor since it is a singleton
	ConfigurationService(ConfigurationService& service) { }

	~ConfigurationService() {}


public:

	/**
	 * retrieve the service instance
	 */
	static ConfigurationService* instance() {
		static ConfigurationService instance;
		return &instance;
	}


	/**
	 * returns the configuration properties
	 */
	property_t getProperties() const {
		return properties;
	}

protected:

	/**
	 * read the configuration properties. A few parts of the following source code
	 * are taken from the IMVHostScanner.
	 */
	std::vector<std::pair<std::string,std::string> > readConfiguration();

};

}
#endif
