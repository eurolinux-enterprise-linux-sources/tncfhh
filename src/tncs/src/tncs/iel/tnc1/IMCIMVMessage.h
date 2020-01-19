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
#ifndef TNCS_IMCIMVMESSAGE_H_
#define TNCS_IMCIMVMESSAGE_H_

#include <tcg/tnc/tncifimv.h>
#include <tcg/tnc/fhhaddon.h>

namespace tncfhh
{

namespace iel
{

namespace tnc1
{

/**
 * TODO_Comment
 * 
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>25.02.2008 - create class (mbs)</li>
 *   <li>28.02.2008 - add content (mbs)</li>
 *   <li>16.07.2009 - redesign 0.6.0 (ib)</li>
 * </ul>
 *
 * @class IMCIMVMessage
 * @brief TODO_Brief
 * @date 25.02.2008
 * @author Mike Steinmetz (mbs)
 *         Ingo Bente (ib)
 */
class IMCIMVMessage
{
public:
	/**
	 * Create an IMC-IMV-Message.
	 *
	 * @param data this binary data is delete by ~IMCIMVMessage() (delete[])
	 * @param dataLength the length of binary data
	 * @param type the MessageType
	 */
	IMCIMVMessage(TNC_BufferReference data, TNC_UInt32 dataLength, TNC_MessageType type);
	virtual ~IMCIMVMessage();
	
	virtual TNC_BufferReference getData();
	virtual TNC_UInt32 getDataLength();
	virtual TNC_MessageType getType();
private:
	TNC_BufferReference data;
	TNC_UInt32 dataLength;
	TNC_MessageType type;
};

}  // namespace tnc1

}  // namespace iel

}  // namespace tncfhh

#endif /*TNCS_IMCIMVMESSAGE_H_*/
