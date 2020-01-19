/*
 * This software is Copyright (C) 2006-2010
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

#include "LibtncTNCC.h"

#include <iostream>

namespace tncsim {

namespace client {

client::AbstractTNCC * getClient(std::string &tncConfig)
{
	return new client::libtnc::LibtncTNCC(tncConfig);
}

namespace libtnc {

#define CHECK(x) if ((x)!=TNC_RESULT_SUCCESS){std::cerr<<"error in "<<__FILE__<<":"<<__LINE__<<std::endl;throw std::runtime_error("Error in libtnc.");}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
LibtncTNCC::LibtncTNCC(std::string &tncConfig)
	:AbstractTNCC(tncConfig), myImcConn(NULL)
{

	CHECK(libtnc_tncc_Initialize(this->tncConfig.c_str()));
	CHECK(libtnc_tncc_PreferredLanguage("de"));
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
LibtncTNCC::~LibtncTNCC() {
	if (myImcConn != NULL)
		libtnc_tncc_DeleteConnection(myImcConn);
	CHECK(libtnc_tncc_Terminate());
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void LibtncTNCC::createConnection(TNC_ConnectionID)
{
	this->myImcConn = libtnc_tncc_CreateConnection(NULL);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
static TNCCSData data(0);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNCCSData LibtncTNCC::beginHandshake()
{
	CHECK(libtnc_tncc_BeginSession(this->myImcConn));
	return tncsim::client::libtnc::data;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNCCSData LibtncTNCC::receiveTNCCSData(const TNCCSData & data)
{
	CHECK(libtnc_tncc_ReceiveBatch(this->myImcConn, (const char *)data.getData(), data.getLength()));
	return tncsim::client::libtnc::data;
}

}

}

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_Result TNC_TNCC_SendBatch(
    /*in*/ libtnc_tncc_connection* conn,
    /*in*/ const char* messageBuffer,
    /*in*/ size_t messageLength)
{
	tncsim::client::libtnc::data.setData((const unsigned char *)messageBuffer, messageLength);

	return TNC_RESULT_SUCCESS;
}
