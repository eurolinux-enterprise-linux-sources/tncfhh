/*
 * This software is Copyright (C) 2006-2009
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

/**
 * FileCertManager
 *
 * Implementation of the CertManager Class
 *
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>08.12.2009 - create class skeleton and some logic (awe)</li>
 *   <li>16.12.2009 - added missing ifdef endif construction (awe)</li>
 * </ul>
 *
 * @date 08.12.09
 * @author Arne Welzel (awe)
 *
 */
#ifndef FILE_CERT_MANAGER_H_
#define FILE_CERT_MANAGER_H_

#include "CertManager.h"
#include <string>

/* log4cxx includes */
#include "log4cxx/logger.h"
using namespace log4cxx;
using namespace std;

class FileCertManager : public CertManager
{
private:
	/* map with certs */
	std::map<string, string> certMap;

	/* returns -1 on failure, 0 on success */
	int loadCertsFromFile(const char *certfile);

	/* parses one line from the cert and adds if it's good */
	int addCertFromConfigLine(std::string line);

public:
	/* constructor */
	FileCertManager(const char *certfile);

	/* destructor */
	virtual ~FileCertManager();

	/* implementation of abstract method */
	virtual bool isCertKnown(std::string dn, std::string fingerprint);
};

#endif //FILE_CERT_MANAGER_H
