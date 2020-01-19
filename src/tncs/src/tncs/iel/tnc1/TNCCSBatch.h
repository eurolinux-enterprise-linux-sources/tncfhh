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
#ifndef TNCS_IELTNCCSBATCH_H_
#define TNCS_IELTNCCSBATCH_H_

#include "../TNCCSData.h"
#include "IMCIMVMessage.h"
#include "TNCCTNCSMessage.h"
#include <tncutil/XercesString.h>
#include "../../exception/TNCCSProtocolNotSupportedException.h"

#include <list>
#include <exception>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>

namespace tncfhh {

namespace iel {

namespace tnc1 {

/**
 * TODO_Comment
 * 
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>25.02.2008 - create class (mbs)</li>
 *   <li>27.02.2008 - add first uncomplete XML parsing (mbs)</li>
 *   <li>28.02.2008 - add first uncomplete XML creating (mbs)</li>
 *   <li>22.04.2008 - add resetID [bug 9] (mbs)</li>
 *   <li>15.04.2008 - remove an XML (xsi:schemalocation) bug [bug] (mbs)</li>
 *   <li>20.07.2009 - redesign for 0.6.0 (mbs)</li>
 *   <li>28.08.2009 - replace old C code (for convert string to int) to C++ code (mbs)</li>
 *   <li>02.09.2009 - make XercesC 3.0 compatible [bug 24] (mbs)</li>
 *   <li>02.09.2009 - make XercesC 3.0.1 compatible (ib)</li>
 * </ul>
 *
 * @class TNCCSBatch
 * @brief TODO_Brief
 * @date 25.02.2008
 * @author Mike Steinmetz (mbs)
 */
class TNCCSBatch
{
public:
	enum Recipient {TNCS, TNCC};
	TNCCSBatch(Recipient recipient);
	virtual ~TNCCSBatch();
	virtual TNCCSBatch & operator=(const TNCCSData & tnccsData) throw (TNCCSProtocolNotSupportedException);

	/**
	 * TODO_Comment
	 *
	 * @param tnccTncsMessage the TNCC-TNCS-Message. NOTE: this class delete the tnccTncsMessage instance
	 */
	virtual void addTNCCTNCSMessage(TNCCTNCSMessage * tnccTncsMessage);

	/**
	 * TODO_Comment
	 *
	 * @param imcImvMessage the IMC-IMV-Message. NOTE: this class delete the imcImvMessage instance
	 */
	virtual void addIMCIMVMessage(IMCIMVMessage * imcImvMessage);
	
	virtual void deleteAllMessages();
	virtual void resetID();
	
	virtual TNCCSData getNewTnccsData() throw (std::runtime_error);
	
	virtual std::list<TNCCTNCSMessage *> getTnccTncsMessages();
	virtual std::list<IMCIMVMessage *> getImcImvMessages();

	static const XercesString iftnccsNamespaceURI;
private:
	explicit TNCCSBatch(const TNCCSBatch &batch) throw (std::runtime_error);

	virtual void addTnccTncsMessage(xercesc::DOMElement & tnccTncsMessage) throw (TNCCSProtocolNotSupportedException);
	virtual void addImcImvMessage(xercesc::DOMElement & imcImvMessage) throw (TNCCSProtocolNotSupportedException);
	virtual TNC_UInt32 getType(xercesc::DOMElement & type) throw (TNCCSProtocolNotSupportedException);
	
	TNC_UInt32 id;
	Recipient recipient;
	std::list<TNCCTNCSMessage *> tnccTncsMessages;
	std::list<IMCIMVMessage *> imcImvMessages;
	
	class XercesInit {
	public:
		XercesInit();
		~XercesInit();
	};
	static XercesInit xercesInit;

	/**
	 * Retrieves the value of an attribute of the specified node.
	 *
	 * @param node The node to search for the attribute.
	 * @param attName The name of the searched attribute.
	 * @throw An exception if the attribute was not found in the specified node.
	 *
	 */
	XercesString getAttributeValue(xercesc::DOMNode & node, const XercesString & attName) throw(TNCCSProtocolNotSupportedException);

	/**
	 * Writes at most 'size' bytes from 'format' to 'buf'. 'format' is a
	 * format-string as used by ordinary printf functions.
	 *
	 * @param buf The buffer where to write the array.
	 * @param size Size of the buffer.
	 * @param format A format string.
	 */
    void writeToArray(char *buf, const int size, const char *format, ...);
};

}  // namespace tnc1

}  // namespace iel

}  // namespace tncfhh

#endif /*TNCS_IELTNCCSBATCH_H_*/
