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

/*
 * Configuration.h
 *
 *  Created on: 16.02.2010
 *      Author: Alexander Schulz
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

namespace tncfhh {

class Configuration {

private:
	std::map<std::string,std::string> map;

	// private default contructor since it is a singleton
	Configuration() {
	}

	// private copy contructor since it is a singleton
	Configuration(Configuration& config) { }

	~Configuration() {}

public:
	void addConfigurationFile(std::string filename);

	void set(std::string key, std::string value);

	std::string get(std::string key);

	/**
	 * retrieve the config instance
	 */
	static Configuration* instance();
};

}

#endif /* CONFIGURATION_H_ */
