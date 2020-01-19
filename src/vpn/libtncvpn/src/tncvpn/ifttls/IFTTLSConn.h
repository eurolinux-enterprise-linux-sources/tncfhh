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
 * IFTTLSConn.h
 *
 *  Created on: Aug 1, 2010
 *      Author: awelzel
 */

#ifndef IFTTLSCONN_H_
#define IFTTLSCONN_H_

#include "tncvpn/ifttls/IFTMessages.h"

#include <boost/asio.hpp>

/* forgive me */
using namespace boost::asio;

namespace ifttls {

/*
 * Encapsulate some of the functionality to send an receive if-t-ttls messages
 * in this class. A socket which is ready to read/write operations is expected.
 * TLS handshake needs to be finished before the a IFTTLSConnection object
 * may be created.
 */
class IFTTLSConnection {

public:

	IFTTLSConnection(ssl::stream<ip::tcp::socket>& sock);
	~IFTTLSConnection();

	void startVersionNegotiation();
	void expectVersionNegotiation();

	void sendMessage(Envelope *envelope);
	ifttls::Envelope *receiveMessage();

private:
	// Our socket, copied from Client.h
	ssl::stream<ip::tcp::socket>& socket_;

	/*
	 * We first receive the header. Its length is always IFT_HEADER_LENGTH.
	 */
	uint8_t curHeader[Envelope::IFT_HEADER_LENGTH];

	/*
	 * Field where the current message length is stored.
	 */
	uint32_t curMsgLength;

	/*
	 * Pointer to the whole message, the header will be copied in here.
	 */
	uint8_t *curMessage;

	/*
	 * the current identifier to be used
	 */
	uint32_t curIdentifier;

	uint32_t getNextIdentifier() {
		uint32_t tmp = curIdentifier;
		curIdentifier++;
		return tmp;
	}

	void readHeader();
	void allocateMessageBuffer();
	void readRestOfMessage();
	Envelope *constructEnvelope();
	void freeBuffers();
};

}

#endif /* IFTTLSCONN_H_ */
