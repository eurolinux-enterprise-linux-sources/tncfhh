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

#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <tncs/iel/Coordinator.h>

#include <tncvpn/ifttls/IFTMessages.h>
#include <tncvpn/iel/Endpoint.h>

namespace tnc {

/**
 * The message_handler is responsible for processing any
 * incoming IF-T message, independent of the type(negotiation
 * or TNCCS data).
 *
 * Only this class needs to get enhanced in order to support the
 * negotiation of further parameters.
 */
class MessageHandler {
private:

	/** The connection id for the TNC server */
	TNC_ConnectionID conn_id;
	tnc::Endpoint *ep;

	ifttls::Envelope* reply_msg;

	/** Indicates that the pre-negotiation phase has finished */
	bool pre_negotiation_finished;

	/** Indicates that the TNC server wants to read */
	bool want_read_;

	/** Indicates that the TNC server wants to write */
	bool want_write_;

	bool finished_;

	void clean();


protected:

	/**
	 * Handles and processes a TNCCS 2.0 message.
	 */
	void handleTnccs20Batch(ifttls::Envelope* message);


public:
	/**
	 * Create a message_handler.
	 */
	MessageHandler(tnc::Endpoint *ep);
	virtual ~MessageHandler();

	/**
	 * Handles any kind of IF-T binding to TLS
	 * message and invokes the corresponding method
	 * to process the message.
	 */
	void handleMessage(ifttls::Envelope* message);

	/**
	 * Indicates whether there is reply message.
	 */
	bool hasReplyMessage() const;

	/**
	 * Returns the IF-T message which shall be sent
	 * to the Access Requestor.
	 */
	ifttls::Envelope* getReplyMessage();


	/**
	 * Indicates that the TNC server wants to write.
	 */
	bool wantWrite() const;

	/**
	 * Indicates that the TNC server wants to read.
	 */
	bool wantRead() const;

	bool isFinished() const { return finished_; }


	/**
	 * This method tells the message_handler that the data
	 * was successfully sent by the underlying network layer.
	 */
	void done();
};

}
#endif
