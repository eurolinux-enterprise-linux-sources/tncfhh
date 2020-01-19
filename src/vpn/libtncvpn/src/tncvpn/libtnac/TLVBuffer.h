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



#ifndef TLV_BUFFER_H
#define TLV_BUFFER_H


#include <stdint.h>
#include <iostream>
#include <cstring>

#include <exception>


using namespace std;


/**
 * Simplifies the handling of arbitrary TLV packets.
 * @author Alexander Reich
 */
template<typename T>
class TLVBuffer {


private:
	/** TLV offset in the packet header */
	unsigned offset;

	/** Current len of the buffer */
	unsigned buf_len;

	/** size of the buffer */
	unsigned buf_size;

	unsigned max_pkt_size;
	char* buffer;
	char* packet;

	/** New packet is available */
	bool packet_complete;

	/** bytes read of the packet */
	unsigned read_len;

	bool new_packet;

	/** Length of the packet */
	T packet_len;


public:
	TLVBuffer(unsigned offset, unsigned max_pkt_size, unsigned buf_size = 4096)
		: offset(offset), buf_len(0), max_pkt_size(max_pkt_size), buf_size(buf_size),
		  packet_complete(true), new_packet(false), read_len(0) {

		buffer = new char[2*buf_size];
		packet = new char[max_pkt_size];
	}


	~TLVBuffer() {
		delete[] buffer;
		delete[] packet;
		buffer = 0;
		packet = 0;
	}


	void addToBuffer(char* data, unsigned len) {
		if (buf_len + len > 2*buf_size) throw std::exception();

		memcpy(buffer+buf_len, data, len);
		buf_len += len;
		parse();
	}


	bool isPacketComplete() {
		// packet_complete just indicates whether a packet is in progress or not
		return packet_complete && buf_len > 0;
	}

	bool isNewPacket() {
		return new_packet;
	}

	void copyData(unsigned packet_len) {

		// buffer contains more than just one packet
		if (buf_len > packet_len) {
			// Copy the whole packet into the packet buffer
			memcpy(packet, buffer, packet_len);

			// Adapt the buffer
			buf_len -= packet_len;
			memcpy(buffer, buffer+packet_len, buf_len);

			packet_complete = true;
			new_packet = true;
		}
		// buffer contains exactly one packet
		else if (buf_len == packet_len) {
			memcpy(packet, buffer, packet_len);
			packet_complete = true;
			buf_len = buf_len - packet_len;
			new_packet = true;
		}
		// buffer contains less than one packet
		else {
			read_len = buf_len;
			packet_complete = false;
			new_packet = false;
		}

	}

	void nextPacket() {
		new_packet = false;

		if (packet_complete)
			read_len = 0;

		if (buf_len > 0)
			parse();

	}

	void parse() {
		memcpy(&packet_len, buffer+offset, sizeof(T));
		copyData(packet_len);
	}

	T getPacketLenght() {
		return packet_len;
	}

	char* getPacket() {
		return packet;
	}
};

#endif
