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

#include "TNCSession.h"
#include <arpa/inet.h>

#include <log4cxx/logger.h>

#define LOGNAME "[TNCSession]"
static log4cxx::LoggerPtr logger = log4cxx::Logger::getLogger(LOGNAME);

namespace tnc {

TNCSession::TNCSession (boost::asio::io_service& io_service, boost::asio::ssl::context& context)
	: tnc::ssl::Session(io_service, context), 
	handler(0), 
	ep(0),
	ifttlsConnection(0)
{

}

TNCSession::~TNCSession()
{
	LOG4CXX_TRACE(logger, "Destructor");
	delete handler;
	delete ep;
	delete ifttlsConnection;
}

void TNCSession::handleClient() {
    	// Create an Endpoint object on the basis of the IP address
    	boost::asio::ip::tcp::endpoint remote_ep = socket_.lowest_layer().remote_endpoint();
	boost::asio::ip::address remote_ad = remote_ep.address();
	ep = new tnc::Endpoint(remote_ad);

	LOG4CXX_INFO(logger, "New Request from endpoint: " << remote_ad);

	// Creating the message_handler
	handler = new MessageHandler(ep);

	ifttlsConnection = new ifttls::IFTTLSConnection(socket_);

	// Start with the operations
	doOperations();
}


void TNCSession::doOperations() {
	try {
		LOG4CXX_TRACE(logger, "Expecting Version Negotiation");
		ifttlsConnection->expectVersionNegotiation();


		while (!handler->isFinished()) {
			ifttls::Envelope *env;
			// Does the TNC server want to read?
			if (handler->wantRead()) {
				LOG4CXX_TRACE(logger, "handler wants some data");
				env = ifttlsConnection->receiveMessage();
				handler->handleMessage(env);

			} else if (handler->wantWrite()) {
				LOG4CXX_TRACE(logger, "handler wants to send data");

				// Are there any messages to send?
				if (handler->hasReplyMessage()) {
					env = handler->getReplyMessage();
					ifttlsConnection->sendMessage(env);
				}
			}
			delete env;
			handler->done();
		}
		// send the last message, which should be the recommendation
		if (handler->hasReplyMessage()) {
			ifttls::Envelope *reply = handler->getReplyMessage();
			ifttlsConnection->sendMessage(reply);
			delete reply;
		}
		LOG4CXX_INFO(logger, "Session Over");
		// TODO: could be more specific here
	} catch (...) {
		LOG4CXX_ERROR(logger, "Exception");
		// just do nothing for now... :-/
	}
}
};
