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
 * IFTTLSConn.cpp
 *
 *  Created on: Aug 1, 2010
 *      Author: awelzel
 */
#include "tncvpn/ifttls/IFTTLSConn.h"
#include "tncvpn/ifttls/exceptions/ReceiveException.h"
#include "tncvpn/ifttls/exceptions/VersionException.h"

/* general stuff */
#include <arpa/inet.h>

/* logging stuff */
#include <log4cxx/logger.h>
#define LOGNAME "[IFTTLSConn]"
static log4cxx::LoggerPtr logger = log4cxx::Logger::getLogger(LOGNAME);

static void output_hex(const char *msg, size_t size);

using namespace boost::asio;
namespace ifttls {


IFTTLSConnection::IFTTLSConnection(ssl::stream<ip::tcp::socket>& sock) :
		socket_(sock),
		curMessage(NULL),
		curMsgLength(0),
		curIdentifier(0)
{
	LOG4CXX_TRACE(logger, "Constructor");
	memset(curHeader, 0, Envelope::IFT_HEADER_LENGTH);
}
IFTTLSConnection::~IFTTLSConnection()
{
	LOG4CXX_TRACE(logger, "Destructor");
}

/**
 * TODO: as soon as more versions are out there, this need revisiting
 */
void IFTTLSConnection::startVersionNegotiation()
{
	LOG4CXX_DEBUG(logger, "Client side Version Negotiation...");
	// version 1
	VersionRequestMessage vrm;
	uint32_t payloadLen = vrm.getLength();
	char *payload = vrm.getMessage();
	Envelope *env = new Envelope(Envelope::IFT_VERSION_REQUEST, payload, payloadLen);
	sendMessage(env);

	/* free memory of message */
	delete[] payload;
	delete env;
	payload = NULL; env = NULL;

	/* get the version response */
	env = receiveMessage();
	payload = env->getMessageValue();
	VersionResponseMessage vrsp(payload);
	delete[] payload;
	delete env;
	payload = NULL; env = NULL;

	if (vrsp.getVersion() != 1) {
		LOG4CXX_ERROR(logger, "Unsupported Version received");
		throw VersionException("Unsupported Version received");
	}
	LOG4CXX_DEBUG(logger, "Client side Version Negotiation Finished... ");
}



/**
 * TODO: as soon as more versions are out there, this needs revisiting
 */
void IFTTLSConnection::expectVersionNegotiation()
{
	LOG4CXX_DEBUG(logger, "Server side Version Negotiation...");
	Envelope *env = receiveMessage();
	char *payload = env->getMessageValue();
	VersionRequestMessage vrm(payload);
	delete[] payload;
	delete env;
	payload = NULL; env = NULL;

	if (vrm.getMinVersion() > 1 || 1 < vrm.getMaxVersion()) {
		LOG4CXX_ERROR(logger, "Unsupported Version in request");
		// TODO: send back an error message
		throw VersionException("Unsupported Version in request");
	} else {
		VersionResponseMessage vresp(1);
		payload = vresp.getMessage();
		Envelope resp(Envelope::IFT_VERSION_RESPONSE, payload, vrm.getLength());
		delete[] payload;
		payload = NULL;
		sendMessage(&resp);
	}
	LOG4CXX_DEBUG(logger, "Server side Version Negotiation Finished... ");
}


void IFTTLSConnection::sendMessage(Envelope *env)
{
	env->setIdentifier(getNextIdentifier());
	LOG4CXX_DEBUG(logger, "Sending a message... Length=" << env->getMessageLength()
			<< " Identifier=" << env->getIdentifier());
	char *msg = env->getMessage();
	uint32_t length = env->getMessageLength();
	output_hex((const char*)msg, length);
	boost::asio::write(socket_, boost::asio::buffer(msg, length));
	delete[] msg;
}
Envelope *IFTTLSConnection::receiveMessage()
{
	LOG4CXX_DEBUG(logger, "Receiving a message...");
	Envelope *env = NULL;
	try {
		readHeader();
		allocateMessageBuffer();
		readRestOfMessage();
		env = constructEnvelope();
		output_hex((const char *)curMessage, curMsgLength);
		freeBuffers();
	} catch (ReceiveException e) {
		LOG4CXX_ERROR(logger, e.getMessage());
		freeBuffers();
		throw e;
	} catch (...) {
		// TODO: could be more specific
		LOG4CXX_ERROR(logger, "Oh well, something bad happend...");
		freeBuffers();
		throw ReceiveException("Unknown Exception catched");
	}
	return env;
}

void IFTTLSConnection::readHeader()
{
	//boost::asio::buffer buf(curHeader, Envelope::IFT_HEADER_LENGTH);
	size_t read = boost::asio::read(socket_,
			boost::asio::buffer(curHeader, Envelope::IFT_HEADER_LENGTH));

	if (read != Envelope::IFT_HEADER_LENGTH) {
		LOG4CXX_ERROR(logger, "Failed to read header!");
		throw ReceiveException(std::string("Failed to read header."));
	}
	curMsgLength = ntohl(*((uint32_t *)(curHeader + Envelope::IFT_HEADER_LENGTH_OFFSET)));
}


void IFTTLSConnection::allocateMessageBuffer()
{
	if (curMsgLength < 16 || curMessage != NULL) {
		throw ReceiveException("Length < 16 or curMessage not deleted.");
	}

	/* allocate memory for the whole message */
	curMessage = new uint8_t[curMsgLength];

	/* copy the header in the message buffer */
	memcpy(curMessage, curHeader, Envelope::IFT_HEADER_LENGTH);

	/* zero out the header buffer */
	memset(curHeader, 0, Envelope::IFT_HEADER_LENGTH);

}
void IFTTLSConnection::readRestOfMessage()
{
	uint32_t rest = curMsgLength - Envelope::IFT_HEADER_LENGTH;

	if (rest > 0) {
		size_t read = boost::asio::read(socket_,
			boost::asio::buffer(curMessage + Envelope::IFT_HEADER_LENGTH, rest));
	}
}

Envelope *IFTTLSConnection::constructEnvelope()
{
	Envelope *env = new Envelope((const char*)curMessage, curMsgLength);
	return env;
}

void IFTTLSConnection::freeBuffers()
{
	curMsgLength = 0;
	delete[] curMessage;
	curMessage = NULL;
}

}

/*
 * how i hate that stuff :-(
 */
static void output_hex(const char *msg, size_t size)
{
	char num[3];
	std::string output;

	if (size == 0)
		return;

	int curIndex = 0;
	int row = 0;
	int rows = (size / 16) + 1;
	int curCount = 0;
	int smallCount = 0;

	for (int i = 0; i < size; i++) {
		snprintf(num, 3, "%02hhx", msg[i]);
		output.append(num);
		curCount++;
		smallCount++;

		if (curCount == 16) {
			output.append(2, ' ');
			for (int j = 16; j > 0; j--) {
				if (isprint(msg[i - j]) && !isspace(msg[i - j])) {
					output.append(1, msg[i - j]);
				} else {
					output.append(".");
				}
			}
			LOG4CXX_TRACE(logger, output);
			smallCount = 0;
			curCount = 0;
			output.clear();
		} else if (smallCount == 2) {
			output.append(1, ' ');
			smallCount = 0;
		}
	}

	// nobody should ask...
	output.append(2 * (16 - curCount) + (16 - curCount) / 2 + 2, ' ');

	for (int j = curCount; j > 0; j--) {
		if (isprint(msg[size - j]) && !isspace(msg[size - j])) {
			output.append(1, msg[size - j]);
		} else {
			output.append(".");
		}
	}
	LOG4CXX_TRACE(logger, output);
}

