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
 * Configuration.cpp
 *
 *  Created on: 16.02.2010
 *      Author: tncvpn
 */

#include "Configuration.h"

#include <log4cxx/logger.h>

namespace tncfhh {

/* for logging */
static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("TNCUtil.Configuration"));

void Configuration::addConfigurationFile(std::string filename) {
	std::ifstream file;
	char buffer[1024];

	file.open(filename.c_str(), std::ios::in);

	if (file.good()) {
		file.seekg(0L, std::ios::beg);

		while (!file.eof()) {
			file.getline(buffer, 1024);
			std::string line = std::string(buffer);

			/* ignore comments */
			if (line.size() < 1 || line.at(0) == '#')
				continue;

			size_t pos = line.find_first_of('=');

			/* ignore illegal lines */
			if (pos == std::string::npos) {
				continue;
			}

			/* get key */
			std::string key = line.substr(0, pos);

			/* get value */
			std::string value = line.substr(pos + 1, line.size());

			/* add key-value-pair */
			set(key, value);

		}
	} else {
		LOG4CXX_DEBUG(logger, "Configuration file not found: " + filename);
	}
}

void Configuration::set(std::string key, std::string value) {
	LOG4CXX_DEBUG(logger, key << " = " << value);
	map[key] = value;
}

std::string Configuration::get(std::string key) {
	return map[key];
}

Configuration* Configuration::instance() {
		static Configuration instance;
		return &instance;
	}
}
