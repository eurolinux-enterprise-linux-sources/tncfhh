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

#ifndef PEPNOTIFIER_H
#define PEPNOTIFIER_H

#include <tncvpn/libtnac/AllowDenyPacket.h>
#include <tncvpn/ssl/Client.h>
#include <tncvpn/iel/Endpoint.h>

namespace tnc {

/**
 * The pep_notifier is responsible for sending a recommendation
 * to the Policy Enforcement Point. At the moment there is only
 * binay-based isolation and the simplified IF-PEP version supproted.
 */
class PEPNotifier {
protected:

	/**
	 * Builds the packet and sends the message
	 */
	void sendBinaryRecommendation(Endpoint* ep, char recommendation);


	/**
	 * Splits an IPv4 address into 4 octets and stores them in
	 * the 4 byte long buffer oct.
	 */
	void splitIpv4(std::string ip, char *oct);

	/**
	 * Prints an IPv4 address on the basis of the octets
	 */
	void printAddress(char oct[]) {
		std::printf("%d %d %d %d\n", (unsigned char)oct[0], (unsigned char)oct[1], (unsigned char)oct[2], (unsigned char)oct[3]);
	}

public:

	PEPNotifier() {}
	virtual ~PEPNotifier() {}


	void sendAllow(Endpoint* ep);
	void sendDeny(Endpoint* ep);



	/**
	 * Determines the responsible PEP for a certain Endpoint on the basis of
	 * the Endpoints IPv4 address and the defined mappings. These mappings are
	 * retieved by the configuration service (abstract from the configuration
	 * source like file or LDAP).
	 *
	 * IPv4 only at the moment!
	 *
	 * @return The IPv4 address of the PEP or 0.0.0.0 if no corresponding
	 * mapping was found.
	 */
	std::string getPEPForEndpoint(boost::asio::ip::address *ip);
};

}

#endif
