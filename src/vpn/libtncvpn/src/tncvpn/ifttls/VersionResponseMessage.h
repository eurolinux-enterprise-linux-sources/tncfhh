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

#ifndef VERSION_RESPONSE_MESSAGE_H_
#define VERSION_RESPONSE_MESSAGE_H_


/*
 * More information regarding the structure of the packets is
 * available in the official specification of IF-T binding to TLS.
 */

namespace ifttls {

/**
 * This class represents the version response message. This message is send as
 * a reply to a version request message. Belongs to the pre negotiation phase.
 *
 *
 *                       1                   2                   3
 *	 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	|                 Reserved                      |    Version    |
 *	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 */
class VersionResponseMessage {
private:
	char reserved[3];

public:
	uint8_t version;


	/**
	 * Create a version_response_message with default version of 1
	 */
	VersionResponseMessage() : version(1)
	{
		memset(reserved, 0, 3);
	}


	/**
	 * Create a version_response_message with a certain version number
	 */
	VersionResponseMessage(uint8_t version) : version(version)
	{
		memset(reserved, 0, 3);
	}


	/**
	 * Creates a version_response_message on the basis of a given payload
	 * which should be of length 4
	 */
	VersionResponseMessage(char* msg)
	{
		memcpy(&reserved, msg, 3);
		memcpy(&version, msg+3, 1);
	}


	~VersionResponseMessage()
	{
		/* nothing */
	}


	/**
	 * Returns the payload as 4 byte long buffer, the buffer must be freed
	 * by the caller
	 */
	char* getMessage() {
		char *msg = new char[4];
		memcpy(msg, reserved, 3);
		memcpy(msg+3, &version, 1);
		return msg;
	}


	/**
	 * Returns the length of the message.
	 */
	uint32_t getLength() {
		return 4;
	}

	uint8_t getVersion() const { return version; }
};

} //namespace ifttls

#endif
