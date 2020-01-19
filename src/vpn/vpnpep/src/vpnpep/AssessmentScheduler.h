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

#ifndef ASSESSMENT_SCHEDULER_H
#define ASSESSMENT_SCHEDULER_H

#include <iostream>
#include <string>

#include "EndpointDB.h"
#include "EnforcementManager.h"

namespace tnc {


/**
 * The assessment scheduler performs checks every 10 seconds
 * wether a new assessment for an endpoint is required or not.
 */
class AssessmentScheduler {
private:

	/**
	 * The endpoint db stores all endpoints and the corresponding
	 * timstamp of their last assessment
	 */
	tnc::EndpointDB *db;

protected:


public:
	/**
	 * Constructs a new assessment_scheduler and initializes
	 * the endpoint_db.
	 */
	AssessmentScheduler(EndpointDB *db)
		: db(db) { }

	virtual ~AssessmentScheduler() {

	}


	/**
	 * Main method of the assessment_scheduler. The operator() is
	 * used by the boost thread library as "main" method of the
	 * thread.
	 */
	void operator()() {
		while (true) {
			std::cout << "[Scheduler] Looking for reassessments" << std::endl;

			// Getting the current time
			time_t current_time = time(NULL);
			struct tm current_ts;
			localtime_r(&current_time, &current_ts);


			// For each endpoint in the database
			for(EP_HashMap::iterator it = db->getEndpoints()->begin(); it != db->getEndpoints()->end(); ++it) {
				Endpoint* ep = it->second;
				if (ep == 0) continue;

				struct tm ts;
				localtime_r(ep->getLastAssessment(), &ts);

				// Calculating the difference
				int min = current_ts.tm_min - ts.tm_min;

				// Reassessment are expected within an interval of 5 minutes
				if (min > 5) {
					std::string ip = ep->getAddress()->to_string();
					std::cout << "[Scheduler] WARN: Reassessment for " << ip << " is missing!" << std::endl;
					std::cout << "[Scheduler] WARN: Last assessment was on " << ts.tm_hour << ":" << ts.tm_min << ":" << ts.tm_sec << std::endl;

					// Revoking the access to the network
					enforceBinaryIso((char*)ip.c_str(), 'N');

					// Deleting the endpoint from the db
					delete ep;
					it->second = 0;


				}

			}

			sleep(10);
		}
	}

};

}

#endif
