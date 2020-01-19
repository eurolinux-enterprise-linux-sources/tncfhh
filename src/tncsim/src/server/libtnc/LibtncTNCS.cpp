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

#include "LibtncTNCS.h"

#include <iostream>

namespace tncsim {

namespace server {

server::AbstractTNCS * getServer(std::string &tncConfig)
{
	return new libtnc::LibtncTNCS(tncConfig);
}

namespace libtnc {

#define CHECK(x) if ((x)!=TNC_RESULT_SUCCESS){std::cerr<<"error in "<<__FILE__<<":"<<__LINE__<<std::endl;throw std::runtime_error("Error in libtnc.");}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
LibtncTNCS::LibtncTNCS(std::string &tncConfig)
	:AbstractTNCS(tncConfig), myImvConn(NULL)
{
	CHECK(libtnc_tncs_Initialize(this->tncConfig.c_str()));
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
LibtncTNCS::~LibtncTNCS()
{
	if (myImvConn != NULL)
		libtnc_tncs_DeleteConnection(myImvConn);
	CHECK(libtnc_tncs_Terminate());
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void LibtncTNCS::createConnection(TNC_ConnectionID)
{
	this->myImvConn = libtnc_tncs_CreateConnection(NULL);
	CHECK(libtnc_tncs_BeginSession(myImvConn));
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
TNCCSData LibtncTNCS::receiveTNCCSData(const TNCCSData & data) throw(Finished)
{
	TNC_IMV_Action_Recommendation recommendation = 0;
	TNC_IMV_Evaluation_Result evaluation = 0;

	CHECK(libtnc_tncs_ReceiveBatch(this->myImvConn, (const char *)data.getData(), data.getLength()));
	if (libtnc_tncs_HaveRecommendation(myImvConn, &recommendation, &evaluation) == TNC_RESULT_SUCCESS)
		throw Finished(recommendation, tncsim::server::libtnc::data);
	return tncsim::server::libtnc::data;
}

}

}

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *        *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
TNC_Result TNC_TNCS_SendBatch(
    /*in*/ libtnc_tncs_connection* conn,
    /*in*/ const char* messageBuffer,
    /*in*/ size_t messageLength)
{
	tncsim::server::libtnc::data.setData((const unsigned char *)messageBuffer, messageLength);

	return TNC_RESULT_SUCCESS;
}
