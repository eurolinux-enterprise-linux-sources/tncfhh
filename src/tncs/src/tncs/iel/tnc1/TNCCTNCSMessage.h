/*
 * This software is Copyright (C) 2006-2009
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
#ifndef TNCS_TNCCTNCSMESSAGE_H_
#define TNCS_TNCCTNCSMESSAGE_H_

#include <tcg/tnc/tncifimv.h>

namespace tncfhh {

namespace iel {

namespace tnc1 {


/**
 * This Class represent an TNCC-TNCS-Message. This message is specified in
 * TNC IF-TNCCS. It exist two types of TNCC-TNCS-Message, binary base and XML
 * base messages.
 * 
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>25.02.2008 - create class (mbs)</li>
 *   <li>29.02.2008 - (ib)</li>
 *   <li>05.03.2008 - split class (mbs)</li>
 *   <li>20.07.2009 - redesign for 0.6.0 (mbs)</li>
 * </ul>
 *
 * @class TNCCTNCSMessage
 * @brief This Class represent an TNCC-TNCS-Message.
 * @date 25.02.2008
 * @author Mike Steinmetz (mbs)
 * @author Ingo Bente (ib)
 * @see TNCCTNCSMessageBase64
 * @see TNCCTNCSMessageXML
 */
class TNCCTNCSMessage
{
public:
	virtual TNC_MessageType getType();
	virtual ~TNCCTNCSMessage();
	
protected:
	TNCCTNCSMessage(TNC_MessageType type);

private:
	TNC_MessageType type;
	
};

}  // namespace tnc1

}  // namespace iel

}  // namespace tncfhh

#endif /*TNCS_TNCCTNCSMESSAGE_H_*/
