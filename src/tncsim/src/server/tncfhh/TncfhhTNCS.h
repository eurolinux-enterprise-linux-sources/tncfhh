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

#ifndef TncfhhTNCS_H_
#define TncfhhTNCS_H_

#include "../AbstractTNCS.h"

#include <tncs/iel/Coordinator.h>

namespace tncsim {

namespace server {

namespace tncfhh {

/**
 * Wrapper class for tncsim and TNC@FHH tncs.
 *
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>16.7.2009 - first implementation (mbs)</li>
 *   <li>16.03.2010 - integrated tncsim from branches to tncfhh (ib)</li>
 * </ul>
 *
 * @date 16.03.2010
 * @author Mike Steinmetz (mbs)
 * @author Ingo Bente (ib)
 */
class TncfhhTNCS: public tncsim::server::AbstractTNCS {
public:
	TncfhhTNCS(std::string &tncConfig);
	virtual ~TncfhhTNCS();

	virtual void createConnection(TNC_ConnectionID);
	virtual TNCCSData receiveTNCCSData(const TNCCSData & data) throw(Finished);
private:
	TNC_ConnectionID cid;
};

}

}

}

#endif /* TncfhhTNCS_H_ */
