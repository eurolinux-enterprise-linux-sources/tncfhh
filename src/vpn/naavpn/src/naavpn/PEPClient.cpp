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

#include "PEPClient.h"
#include "tncvpn/iel/Endpoint.h"

namespace tnc {

PEPClient::PEPClient(boost::asio::io_service& io_service,
		boost::asio::ssl::context& context,
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator,
		boost::asio::ip::address *address,
		char recommendation)
			: tnc::ssl::Client(io_service, context, endpoint_iterator),
			  recommendation(recommendation), address(address) {
	handleHandshakeCompleted();

}

void PEPClient::handleHandshakeCompleted() {
	std::cout << "[PEP-CLIENT] Connected to PEPd" << std::endl;

	// Create a packet of the simplified IF-PEP message.
	pep::AllowDenyPacket *pkt = new pep::AllowDenyPacket(address, recommendation);

	// Sends the packet to the PEP asynchronously
	boost::asio::async_write(socket_, boost::asio::buffer(
				 pkt->getPacket(), pkt->getPacketSize()),
				 boost::bind(&PEPClient::handleWrite, this,
						 boost::asio::placeholders::error,
						 boost::asio::placeholders::bytes_transferred));
}

void PEPClient::handleWrite(const boost::system::error_code& error, size_t bytes_transferred) {
	if (!error) {
			std::cout << "[PEP-CLIENT] Recommendation sent" << std::endl;
	} else {
		std::cout << "[PEP-CLIENT] Write failed: " << error << "\n";
	}
}

}
