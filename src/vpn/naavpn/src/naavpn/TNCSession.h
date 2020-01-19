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

#ifndef TNCSESSION_H
#define TNCSESSION_H

#include "tncvpn/ssl/Session.h"
#include "tncvpn/ifttls/Envelope.h"
#include "tncvpn/ifttls/IFTTLSConn.h"

#include "MessageHandler.h"

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

namespace tnc {

/**
 * The tnc_session class represents one TLS session between
 * Access Requestor and Policy Decision Point. This class handles
 * the IF-T binding to TLS message exchange and forwards the IF-T
 * messages to the message_handler.
 */

class TNCSession : public tnc::ssl::Session {
private:

	/* space where the header and message body gets stored */
	unsigned char header_[ifttls::Envelope::IFT_HEADER_LENGTH];
	unsigned char *curMsg_;
	uint32_t curMsgLength_;

	MessageHandler *handler;
	tnc::Endpoint *ep;
	ifttls::IFTTLSConnection *ifttlsConnection;

public:

	/**
	 * Default constructor, initializes the object with some default values.
	 */
	TNCSession (boost::asio::io_service& io_service, boost::asio::ssl::context& context);


	~TNCSession();

	/*
	 * Method called after TLS handshake is completed
	 */
	void handleClient();


	/**
	 * The do_operations method invokes the read and write operations
	 * asynchronous in order to realize that more than one read or write
	 * operation can be performed until the first one finishes.
	 */
	void doOperations();


	/**
	 * Callback gets invoked as far as we have received any data. Passes the IF-T
	 * to the TNC server via the message_handler.
	 *
	void handleReadCompleted(const boost::system::error_code& error, size_t bytes_transferred);
	*/


	/**
	 * Callback gets invoked as far as we have received any data. Passes the IF-T
	 * to the TNC server via the message_handler.
	 *
	void handleWriteCompleted(const boost::system::error_code& error);
	*/

	/*
	void handleReadHeader(const boost::system::error_code& error, size_t bytes_transferred);
	void handleReadBody(const boost::system::error_code& error, size_t bytes_transferred);
	*/
};

}

#endif


