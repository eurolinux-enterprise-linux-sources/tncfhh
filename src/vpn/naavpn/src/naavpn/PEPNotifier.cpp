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

#include "PEPNotifier.h"
#include "PEPClient.h"
#include <tncutil/ConfigurationService.h>
#include <tncutil/Configuration.h>

namespace tnc {

void PEPNotifier::sendBinaryRecommendation(Endpoint* ep, char recommendation) {


	// Determine the responsible PEP for the Endpoint
	boost::asio::ip::address *address = ep->getAddress();
	std::string pep_address = getPEPForEndpoint(address);


	if (pep_address.compare("0.0.0.0") == 0) {
		std::cerr << "[PEP-CLIENT] ERROR: No PEP found for " << *address << " in " << tncfhh::Configuration::instance()->get("CONFIGURATION_SERVICE_FILE") << std::endl;
		return;
	}

	std::cout << "[PEP-CLIENT] Responsible PEP for Endpoint: " << pep_address << std::endl;

	// Create the TLS tunnel to the PEP using boost asio and
	// send the message.
	try {
		boost::asio::io_service io_service;

		std::string pep_port = tncfhh::Configuration::instance()->get("PEP_PORT");
		std::string verify_file = tncfhh::Configuration::instance()->get("PEP_KEY");

		std::cout << "[PEP-CLIENT] pep_port=" << pep_port << " verify_file=" << verify_file << std::endl;
		boost::asio::ip::tcp::resolver resolver(io_service);
		boost::asio::ip::tcp::resolver::query query(pep_address, pep_port);
		boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);

		boost::asio::ssl::context ctx(io_service, boost::asio::ssl::context::sslv23);
		ctx.set_verify_mode(boost::asio::ssl::context::verify_peer);
		ctx.load_verify_file(verify_file);

		PEPClient c(io_service, ctx, iterator, address, recommendation);
		io_service.run();

	} catch (std::exception& e) {
		std::cerr << "[PEP-CLIENT] Exception: " << e.what() << "\n";
	}
}

void PEPNotifier::splitIpv4(std::string ip, char *oct) {

	// Find first octet
	std::size_t pos = ip.find(".");
	oct[0] = atoi(ip.substr(0, pos).c_str());
	ip = ip.substr(pos+1, ip.length()-pos);

	// Find second octet
	pos = ip.find(".");
	oct[1] = atoi(ip.substr(0, pos).c_str());
	ip = ip.substr(pos+1, ip.length()-pos);

	// Find third octet
	pos = ip.find(".");
	oct[2] = atoi(ip.substr(0, pos).c_str());
	ip = ip.substr(pos+1, ip.length()-pos);

	// Find last octet
	oct[3] = atoi(ip.substr(0, ip.length()).c_str());

}


void PEPNotifier::sendAllow(Endpoint* ep) {
	// Y flag indicates that access shall be granted
	sendBinaryRecommendation(ep, 'Y');
}

void PEPNotifier::sendDeny(Endpoint* ep) {
	// N flag indicates that access shall be denied
	sendBinaryRecommendation(ep, 'N');
}

std::string PEPNotifier::getPEPForEndpoint(boost::asio::ip::address *ip) {

	// Endpoint IP address
	std::string target_str = ip->to_string();

	// Load the contents from the configuration service
	property_t properties =	tncfhh::ConfigurationService::instance()->getProperties();

	// Iterate over all mappings
	for (property_t::iterator iter = properties.begin(); iter
			!= properties.end(); ++iter) {

		std::string net_str = iter->second;

		// Determine the netmask of the mapping
		std::size_t pos = net_str.rfind("/");
		int x = atoi(net_str.substr(pos + 1, net_str.length()).c_str());
		unsigned int netmask;
		if (x == 0)
			netmask = -1;
		else
			netmask = (-1 ^ (unsigned int) pow(2., 32. - x)) + 1;

		// Split the network address into the octets
		char net[4];
		splitIpv4(net_str.substr(0, pos), net);
		//print_addr(net);

		// Split the endpoint IP address into the octets
		char ip[4];
		splitIpv4(target_str, ip);
		//print_addr(ip);


		unsigned char *ho;
		unsigned char mask[4];
		ho = (unsigned char*) &netmask;


		// Switch the byte order
		mask[0] = ho[3];
		mask[1] = ho[2];
		mask[2] = ho[1];
		mask[3] = ho[0];
		// print_addr((char*)mask);


		// binary and of the endpoint's IP address and netmask
		char und[4];
		und[0] = ip[0] & mask[0];
		und[1] = ip[1] & mask[1];
		und[2] = ip[2] & mask[2];
		und[3] = ip[3] & mask[3];


		if (und[0] == net[0] && und[1] == net[1] && und[2] == net[2] && und[3] == net[3])
			return iter->first;
	}


	// If no mapping was found, retrieve the 0.0.0.0 address
	return "0.0.0.0";
}

}
