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
 * LibTNCClient.h
 *
 *  Created on: Jul 31, 2010
 *      Author: awelzel
 */

#ifndef LIBTNCCLIENT_H_
#define LIBTNCCLIENT_H_

/* libtnc header */
#include <libtnctncc.h>

#include "tncvpn/ifttls/Envelope.h"

namespace tnc {

class LibTNCClient {

public:
	LibTNCClient();
	~LibTNCClient();

	void beginSession();

	/* you are responsible for freeing the returned pointer */
	ifttls::Envelope *getMessage();

	/* you are responsible for freeing the pointer given */
	void putData(ifttls::Envelope *env);

	bool wantRead() const { return wantRead_; };
	bool wantWrite() const { return wantWrite_; };

	bool isFinished() const { return finished_; };


private:
	bool wantRead_, wantWrite_, finished_;
	libtnc_tncc_connection *connection;
};

} // namespace tnc

extern "C" {

TNC_Result TNC_TNCC_SendBatch( libtnc_tncc_connection *conn, const char *buffer,
			       size_t len);

TNC_Result TNC_TNCS_SendBatch( libtnc_tncc_connection *conn, const char *buffer,
			       size_t len);
}




#endif /* LIBTNCCLIENT_H_ */
