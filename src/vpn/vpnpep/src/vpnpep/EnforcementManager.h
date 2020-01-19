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

#ifndef ENFORCEMENT_MANAGER_H
#define ENFORCEMENT_MANAGER_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

#include <tncutil/Configuration.h>

void enforceBinaryIso(char* ip, char recommendation) {
	// Create a new child process
	if (fork() == 0) {
		/** Script for the "allow" case */
		const char* allowScript = tncfhh::Configuration::instance()->get("ALLOW_SCRIPT").c_str();

		/** Script for the "deny" case */
		const char* denyScript = tncfhh::Configuration::instance()->get("DENY_SCRIPT").c_str();

		/** Interpreter for the shell script */
		const char* shell = tncfhh::Configuration::instance()->get("SHELL").c_str();

		// Prepare the invocation of the shell script
		char* args[4];
		args[0] = const_cast<char*> ( shell );
		args[1] = (recommendation=='Y') ? const_cast<char*> ( allowScript ) : const_cast<char*> ( denyScript );
		args[2] = ip;
		args[3] = 0;

		// Execute the shell script
		execv(args[0], args);

		perror("[PEP daemon] execv() failed");
		exit(0);
	}

	int w;
	wait(&w);
}

#endif
