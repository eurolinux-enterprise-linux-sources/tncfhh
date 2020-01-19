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
 * TNCMockClient.h
 *
 *  Created on: 25.02.2010
 *      Author: tnc
 */

#ifndef TNCMOCKCLIENT_H_
#define TNCMOCKCLIENT_H_

#include <iostream>
#include <fstream>
#include <string>

#include <tncs/iel/Coordinator.h>


/**
 * Mock object which emulates a real TNC client. This
 * class replays already captured TNCCS data in order to
 * get access to the network.
 */
class TNCMockClient {


private:
	/**
	 * Indicates which message shall be send next.
	 */
	int msg_count;

	/** Indicates that the TNC client wants to read */
	bool _want_read;

	/** Indicates that the TNC client wants to write */
	bool _want_write;


protected:

	/**
	 * Reads an already captured TNCCS message from the file system
	 * and returns it as a std::string.
	 */
	std::string readFile(const char* file_name) {
		char line[1024];
		std::ifstream file;
		std::string file_str;

		file.open(file_name, std::ios::in);

		if (file.good()) {
			file.seekg(0L, std::ios::beg);

			while (!file.eof()) {
				file.getline(line, 1024);
				file_str.append(line);
			}
		}
		else {
			std::cout << "File not found!" << std::endl;
		}

		return file_str;
	}

public:
	/**
	 * Create a tncc object and initializes it.
	 */
	TNCMockClient() : msg_count(0), _want_read(false), _want_write(true) {}

	virtual ~TNCMockClient() {}


	/**
	 * Returns an already a TNCCS message which shall be
	 * send to the Policy Decision Point.
	 */
	tncfhh::iel::TNCCSData getMessage() {
		std::string snip;
		if (msg_count == 0) {
			snip = readFile("snip-1.xml");
			_want_read = true;
			_want_write = false;
		}
		else if (msg_count == 1) {
			snip = readFile("snip-3.xml");
			_want_read = false;
			_want_write = false;
		}


		TNC_BufferReference buf = (unsigned char*) snip.c_str();
		tncfhh::iel::TNCCSData data(buf, snip.length());
		return data;
	}

	/**
	 * Since this TNC client is just a dummy implementation, this
	 * method only increments the message counter.
	 */
	void putMessage(tncfhh::iel::TNCCSData data) {
		std::cout << "count++\n";
		msg_count++;

		_want_read = false;
		_want_write = true;
	}

	/**
	 * Indicates that the TNC client wants to read.
	 */
	bool wantRead() {
		return _want_read;
	}

	/**
	 * Indicates that the TNC client wants to write.
	 */
	bool wantWrite() {
		return _want_write;
	}

};

#endif /* TNCMOCKCLIENT_H_ */
