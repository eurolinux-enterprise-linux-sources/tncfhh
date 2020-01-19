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


#ifndef ALLOW_DENY_PACKET_H
#define ALLOW_DENY_PACKET_H


#include <string>
#include <boost/asio.hpp>
#include <stdint.h>


namespace pep {


/**
 * The only packet type of the simplified IF-PEP
 * protocol. Supports only binary-based isolation.
 */
class AllowDenyPacket {
private:

	/* The ip address of the Access Requestor */
	char* ip;

	/* The recommendation, either 'Y' or 'N' */
	char recommendation;

	/** The packet buffer */
	char* packet;

	/** Used for some packetz manipulation operations */
	char* pck_ptr;

	/** Size of the packet */
	unsigned int pck_size;


protected:
	/**
	 * Adds an element to packet.
	 */
	char* addElement(const void*, int);


public:
	/**
	 * Creates a new packet on the basis of a buffer.
	 */
	AllowDenyPacket(const char* packet);


	/**
	 * Creates a new packet on the basis of the IP address
	 * of an Access Requestor and a recommendation flag.
	 */
	AllowDenyPacket(boost::asio::ip::address*, char);

	virtual ~AllowDenyPacket();


	/**
	 * Returns the packet as a pointer to a buffer.
	 */
	char* getPacket();


	/**
	 * Returns the size of the packet.
	 */
	unsigned int getPacketSize() const;


	/**
	 * Prints the packet information on stdout.
	 */
	void printMessage() const;


	/**
	 * Returns the IP address used within the packet.
	 */
	char* getIp() const;


	/**
	 * Returns the recommendation
	 */
	char getRecommendation() const;
};

}
#endif
