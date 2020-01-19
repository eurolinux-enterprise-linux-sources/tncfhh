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

#ifndef VERSION_REQUEST_MESSAGE_H_
#define VERSION_REQUEST_MESSAGE_H_


namespace ifttls {


/**
 * This class represents the version request message. This message is send
 * in the pre negotiation phase.
 *
 *                       1                   2                   3
 *	 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	|    Reserved   |    Min Vers   |    Max Vers   |   Pref Vers   |
 *	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 */
class VersionRequestMessage {
private:
	uint8_t reserved;

public:
	uint8_t min_vers;
	uint8_t max_vers;
	uint8_t pref_vers;



	/**
	 * Create a version_request_message with default version of 1
	 */
	VersionRequestMessage() :
		reserved(0),
		min_vers(1),
		max_vers(1),
		pref_vers(1)
	{ /* nothing */}

	/**
	 * Create a version_request_message with a certain version number
	 */
	VersionRequestMessage(uint8_t v) :
		reserved(0),
		min_vers(v),
		max_vers(v),
		pref_vers(v)
	{ /* nothing */ }

	/**
	 * Create a version_request_message with offering a range of
	 * supported version.
	 */
	VersionRequestMessage(uint8_t min, uint8_t max, uint8_t pref) :
		reserved(0),
		min_vers(min),
		max_vers(max),
		pref_vers(pref)
	{ /* nothing */ }


	/**
	 * Create a version_request_message on the basis of a given payload
	 */
	VersionRequestMessage(char* msg)
	{
		memcpy(&reserved, msg, 1);
		memcpy(&min_vers, msg+1, 1);
		memcpy(&max_vers, msg+2, 1);
		memcpy(&pref_vers, msg+3, 1);
	}

	~VersionRequestMessage()
	{
		/* nothing */
	}


	/**
	 * Returns the payload as 4 byte long buffer, the buffer must be freed
	 * by the caller
	 */
	char* getMessage() {
		char *msg = new char[4];
		memcpy(msg, &reserved, 1);
		memcpy(msg+1, &min_vers, 1);
		memcpy(msg+2, &max_vers, 1);
		memcpy(msg+3, &pref_vers, 1);
		return msg;
	}

	/**
	 * Returns the length of the message.
	 */
	uint32_t getLength() {
		return 4;
	}

	/**
	 * Simple getters
	 */
	uint8_t getMinVersion() const { return min_vers; };
	uint8_t getMaxVersion() const { return max_vers; };
	uint8_t getPrefVersion() const { return pref_vers; };
};

}

#endif
