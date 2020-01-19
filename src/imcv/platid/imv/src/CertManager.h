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
 * CertManager
 *
 * Class with functions to check if a certificate is known.
 * This is done by comparing a DN Name with a given fingerprint.
 *
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>08.12.2009 - create class skeleton (awe)</li>
 * </ul>
 *
 * @date 08.12.09
 * @author Arne Welzel (awe)
 *
 */
#ifndef CERT_MANAGER_H_
#define CERT_MANAGER_H_

#include <iostream>



class CertManager
{
public:
	virtual ~CertManager() { /* EMPTY INLINE DEFINITON */ };
	virtual bool isCertKnown(std::string dn, std::string fingerprint) = 0;
};
#endif // CERT_MANAGER_H_
