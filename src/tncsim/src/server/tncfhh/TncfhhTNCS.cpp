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

#include "TncfhhTNCS.h"

namespace tncsim {

namespace server {

server::AbstractTNCS * getServer(std::string &tncConfig)
{
	return new tncfhh::TncfhhTNCS(tncConfig);
}

namespace tncfhh {

TncfhhTNCS::TncfhhTNCS(std::string &tncConfig)
	:AbstractTNCS(tncConfig)
{
	::tncfhh::iel::coordinator.initialize(this->tncConfig);
}

TncfhhTNCS::~TncfhhTNCS()
{
	::tncfhh::iel::coordinator.terminate();
}

void TncfhhTNCS::createConnection(TNC_ConnectionID)
{
	this->cid = ::tncfhh::iel::coordinator.getConnection("");
}

TNCCSData TncfhhTNCS::receiveTNCCSData(const TNCCSData & data) throw(Finished)
{
	try {
		::tncfhh::iel::TNCCSData ielInData(data.getData(), data.getLength());
		::tncfhh::iel::TNCCSData ielOutData = ::tncfhh::iel::coordinator.processTNCCSData(cid, ielInData);
		return TNCCSData(ielOutData.getData(), ielOutData.getLength());
	} catch (::tncfhh::iel::ConnectionStateExceptionWithTNCCSData & e) {
		throw Finished(e.getConnectionState(), TNCCSData(e.getLastTnccsData().getData(), e.getLastTnccsData().getLength()));
	} catch (::tncfhh::iel::ConnectionStateException & e) {
		throw Finished(e.getConnectionState(), TNCCSData(0));
	}
}

}

}

}
