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
 * TNCClient.h
 *
 *  Created on: 25.02.2010
 *      Author: tnc
 */

#ifndef TNCCLIENT_H_
#define TNCCLIENT_H_

#include "tncvpn/ssl/Client.h"
#include "tncvpn/ifttls/IFTMessages.h"

#include "LibTNCClient.h"
#include "tncvpn/ifttls/IFTTLSConn.h"

namespace tnc {

class TNCClient : public tnc::ssl::Client {

	LibTNCClient libTncClient;
	ifttls::IFTTLSConnection ifttlsConnection;

	/** Indicates whether the pre nogotiation phase has finished */
	bool pre_negotiation_finished;

	char header[ifttls::Envelope::IFT_HEADER_LENGTH];
	char *curMsg_;
	uint32_t curMsgLength_;


public:

	/**
	 * Just initializes the tnc_client, does start the TLS handshake.
	 */
	TNCClient(boost::asio::io_service& io_service,
			boost::asio::ssl::context& context,
			boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

	~TNCClient();

	/**
	 * Checks whether the TNC client wants to send or receive any data.
	 * The corresponding read and write operations are implemented
	 * asynchronously.
	 */
	void doOperations();
};

};

#endif /* TNCCLIENT_H_ */
