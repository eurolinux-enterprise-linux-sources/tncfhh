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

#include <iostream>
#include <string>

#include "EndpointDB.h"
#include "AssessmentScheduler.h"
#include "EnforcementManager.h"

#include "tncvpn/ssl/Session.h"
#include "tncvpn/libtnac/AllowDenyPacket.h"
#include "tncvpn/libtnac/TLVBuffer.h"


namespace tnc {

/**
 * The pep_session class represents a TLS session between the
 * PEP daemon and the Policy Decision Point. It extends the ssl_session
 * object to inherit commonly used functions.
 */
class PEPSession : public ssl::Session {
private:
	/**
	 * Each recommendation results in an entry in
	 * the endpoint_db.
	 */
	tnc::EndpointDB *db;

public:
	/**
	 * Creates a pep_session object and initializes the session.
	 */
	PEPSession (boost::asio::io_service& io_service, boost::asio::ssl::context& context,
				tnc::EndpointDB *db)
	    : ssl::Session(io_service, context), db(db)
	{
	}


	void handleClient() {

    	std::cout << "[PEP daemon] TLS tunnel established!" << std::endl;
	std::cout << "[PEP daemon] Awaiting IF-PEP message..." << std::endl;

	// We expect any data from the PDP
    	socket_.async_read_some(boost::asio::buffer(data_, max_length),
    			boost::bind(&PEPSession::handleReadCompleted, this,
    			boost::asio::placeholders::error,
    			boost::asio::placeholders::bytes_transferred));
	}


	/**
	 * This method is invoked as far as data were received.
	 */
	void handleReadCompleted(const boost::system::error_code& error, size_t bytes_transferred) {
		if (!error) {
			// Read a simplified IF-PEP packet and print
			// the contents on stdout
			pep::AllowDenyPacket pkt(data_);
			pkt.printMessage();

			char recommendation = pkt.getRecommendation();
			char* ip = pkt.getIp();
			Endpoint *ep = new Endpoint(ip);
			db->add(ep);

			enforceBinaryIso(ip, recommendation);

		}
	    else {
	        delete this;
	    }
	}

};

}
