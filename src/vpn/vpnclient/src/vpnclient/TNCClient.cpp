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

/*
 * TNCClient.cpp
 *
 *  Created on: 25.02.2010
 *      Author: tnc
 */

#include "TNCClient.h"

#define LOGNAME "[TNCClient]"
#include <log4cxx/logger.h>
static log4cxx::LoggerPtr logger = log4cxx::Logger::getLogger(LOGNAME);

using namespace boost::asio;

namespace tnc {


TNCClient::TNCClient(io_service& io_service,
		boost::asio::ssl::context& context,
		ip::tcp::resolver::iterator endpoint_iterator) :
		tnc::ssl::Client(io_service,
		context, endpoint_iterator),
		pre_negotiation_finished(false),
		// we expect the socket to be constructed here
		ifttlsConnection(socket_)
{
	LOG4CXX_TRACE(logger, "Constructor");
}

TNCClient::~TNCClient()
{
	LOG4CXX_TRACE(logger, "Destructor");
}

void TNCClient::doOperations()
{
	LOG4CXX_TRACE(logger, "Let ifttlsConnection make version negotiation...");
	ifttlsConnection.startVersionNegotiation();

	LOG4CXX_TRACE(logger, "Let libTncClient initialize...");
	libTncClient.beginSession();
	LOG4CXX_INFO(logger, "Begin Handshake Loop");

	while(!libTncClient.isFinished()) {
		ifttls::Envelope *env = NULL;
		if (libTncClient.wantWrite()) {
			LOG4CXX_TRACE(logger, "libTncClient has data to send.");
			env = libTncClient.getMessage();
			ifttlsConnection.sendMessage(env);
		} else if (libTncClient.wantRead()) {
			LOG4CXX_TRACE(logger, "libTncClient wants some data from us.");
			env = ifttlsConnection.receiveMessage();
			libTncClient.putData(env);
		}
		delete env;
	}
	LOG4CXX_INFO(logger, "Finished Handshake Outcome ???");
}

} //namespace tnc

