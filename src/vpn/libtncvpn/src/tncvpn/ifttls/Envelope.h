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

#ifndef IFT_ENVELOPE_H_
#define IFT_ENVELOPE_H_


/*
 * More information regarding the structure of the packets is
 * available in the official specification of IF-T binding to TLS.
 */

#include <string>
#include <iostream>

#include <boost/asio/ssl.hpp>
#include <boost/thread.hpp>

namespace ifttls {

/**
 * This represents the IF-T message envelop
 *
 *                       1                   2                   3
 *	 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	|    Reserved   |           Message Type Vendor ID              |
 *	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	|                          Message Type                         |
 *	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	|                         Message Length                        |
 *	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	|                       Message Identifier                      |
 *	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	|           Message Value (e.g. IF-TNCCS Message) . . . .       |
 *	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *
 */
class Envelope {

private:
	uint8_t  reserved;
	uint32_t message_type;
	uint32_t message_length;
	uint32_t message_identifier;
	char*    message_value;


protected:
	static const int header_len = 16;
	static char message_type_vendor_id[];

public:
	static const uint32_t IFT_HEADER_LENGTH = 0x10;

	static const uint32_t IFT_HEADER_LENGTH_OFFSET = 0x08;
	
	/** Data Transport */
	static const uint32_t IFT_TYPE_EXPERIMENT = 0;
	/** IF-T Pre-Negotiation */
	static const uint32_t IFT_VERSION_REQUEST = 1;
	/** IF-T Pre-Negotiation */
	static const uint32_t  IFT_VERSION_RESPONSE = 2;
	/** IF-T Pre-Negotiation */
	static const uint32_t  IFT_CLIENT_AUTH_REQUEST = 3;
	/** IF-T Pre-Negotiation */
	static const uint32_t IFT_CLIENT_AUTH_SELECTION = 4;
	/** IF-T Pre-Negotiation */
	static const uint32_t IFT_CLIENT_AUTH_CHALLENGE = 5;
	/** IF-T Pre-Negotiation */
	static const uint32_t IFT_CLIENT_AUTH_RESPONSE = 6;
	/** IF-T Pre-Negotiation */
	static const uint32_t IFT_CLIENT_AUTH_SUCCESS = 7;
	/** Data Transport */
	static const uint32_t IFT_TNCCS_20_BATCH = 8;


	/**
	 * Constructs an empty IF-T message
	 */
	Envelope();


	/**
	 * Constructs an IF-T message on the basis of a given
	 * and length.
	 */
	Envelope(const char* message, uint32_t len);


	/**
	 * Constructs an IF-T message on the basis of a message type, payload and
	 * the corresponding length.
	 */
	Envelope(uint32_t type, const char* message_value, uint32_t len);
	virtual ~Envelope();


	/**
	 * Returns the message type
	 */
	uint32_t getMessageType() const;


	/**
	 * Returns the message length
	 */
	uint32_t getMessageLength() const;


	/**
	 * Returns the message as buffer, the returned buffer must be freed
	 * by the caller. The values for identifier, version etc. are in network
	 * byte order.
	 */
	char* getMessage();


	/**
	 * Returns the length of the message value (payload)
	 */
	uint32_t getMessageValueLength() const;


	/**
	 * Returns the message value (payload) as buffer, the returned buffer
	 * must be freed by the caller
	 */
	char* getMessageValue();

	uint32_t getIdentifier() const
	{
		return message_identifier;
	}

	void setIdentifier(uint32_t identifier) {
		message_identifier = identifier;
	}


	/**
	 * Prints the messages on stdout
	 */
	void printMessage();
};

}

#endif
