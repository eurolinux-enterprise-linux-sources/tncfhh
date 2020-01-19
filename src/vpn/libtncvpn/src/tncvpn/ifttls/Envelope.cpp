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

#include "Envelope.h"


namespace ifttls {
char Envelope::message_type_vendor_id[] = {0x00, 0x55, 0x97};


Envelope::Envelope()
	: reserved(0) {
}


Envelope::Envelope(uint32_t type, const char* _message_value, uint32_t len) :
		reserved(0),
		message_type(type),
		message_length(len+header_len),
		message_identifier(0)
{
	message_value = new char[len];
	memcpy(message_value, _message_value, len);
}


/*
 * we don't use len for more then checking the length???
 *
 */
Envelope::Envelope(const char* msg, uint32_t len) {
	if (len < header_len) {
		throw "Invalid Transport Message Packet";
	}
	memcpy(&reserved, msg, 1);
	memcpy(message_type_vendor_id, msg+1, 3);
	memcpy(&message_type, msg+4, 4);
	memcpy(&message_length, msg+8, 4);
	memcpy(&message_identifier, msg+12, 4);

	/* convert from big endian to host endianness */
	message_type = ntohl(message_type);
	message_length = ntohl(message_length);
	message_identifier = ntohl(message_identifier);

	message_value = new char[message_length-header_len];
	memcpy(message_value, msg + header_len, message_length-header_len);
}


Envelope::~Envelope() {
	delete[] message_value;
}


uint32_t
Envelope::getMessageLength() const {
	return message_length;
}


char* Envelope::getMessage()
{
	char* msg = new char[message_length];

	/* host to big endian */
	uint32_t n_message_type = htonl(message_type);
	uint32_t n_message_length = htonl(message_length);
	uint32_t n_message_identifier = htonl(message_identifier);


	memcpy(msg, &reserved, 1);
	memcpy(msg+1, message_type_vendor_id, 3);
	memcpy(msg+4, &n_message_type, 4);
	memcpy(msg+8, &n_message_length, 4);
	memcpy(msg+12, &n_message_identifier, 4);
	memcpy(msg+16, message_value, message_length-header_len);

	return msg;
}


uint32_t Envelope::getMessageValueLength() const
{
	return message_length - header_len;
}


char* Envelope::getMessageValue()
{
	char *ret = new char[getMessageValueLength()];
	memcpy(ret, message_value, getMessageValueLength());
	return ret;
}

uint32_t Envelope::getMessageType() const {
	return message_type;
}

void Envelope::printMessage() {
	std::cout << "Reserved: " << reserved << std::endl;
	std::cout << "Message Length: " << message_length << std::endl;
	std::cout << "Message Value: " << message_value << std::endl;
}

}
