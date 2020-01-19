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


#include "AttestationIMVPolicyManager.h"

/* log4cxx includes */
#include "log4cxx/logger.h"
using namespace log4cxx;
using namespace std;

/* our logger */
static LoggerPtr
logger(Logger::getLogger("AttestationIMVPolicyManager"));

#include <sstream>
#include <iomanip>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <algorithm> // std::remove


namespace tncfhh {

namespace iml {

PcrEntry::PcrEntry(unsigned int index, std::string valueAsString)
	:index(index), valueAsString(valueAsString)
{
	stringToByteArray(valueAsString);
}

void PcrEntry::stringToByteArray(const std::string &valueAsString)
{
	unsigned int sha1SizeAsString = 40;
	// check if size matches SHA-1
	if(valueAsString.size() != sha1SizeAsString)
	{
		LOG4CXX_WARN(logger, "PcrEntry valueAsString must be 40 characters long, but length is " << valueAsString.size());
		memset(value, 0, sha1SizeAsString/2);
		index = 0;
		this->valueAsString = "0000000000000000000000000000000000000000";
	} else { // size is OK
		std::stringstream ss(valueAsString);
		// go through characters
		for (unsigned int i = 0; i < valueAsString.size()/2; i++) {
			char c1, c2;
			uint8_t d1, d2;

			// read two characters per loop
			ss >> c1 >> c2;
			// convert characters to uint8_t
			// code taken from http://www.codeguru.com/forum/showthread.php?t=316299
			if(isdigit(c1)) d1 = c1 - '0';
			else if(c1>='A' && c1<='F') d1 = c1 - 'A' + 10;
			else if(c1>='a' && c1<='f') d1 = c1 - 'a' + 10;
			if(isdigit(c2)) d2 = c2 - '0';
			else if(c2>='A' && c2<='F') d2 = c2 - 'A' + 10;
			else if(c2>='a' && c2<='f') d2 = c2 - 'a' + 10;

			// save value of two characters in one byte
			value[i] = d1*16 + d2;
		}
	}
}

PcrEntry::~PcrEntry()
{
	// intentionally left blank
}


AttestationIMVPolicyManager::AttestationIMVPolicyManager(const char *policyFile)
{
	LOG4CXX_TRACE(logger, "AttestationIMVPolicyManager()");
	parsePolicy(policyFile);
}

AttestationIMVPolicyManager::~AttestationIMVPolicyManager()
{
	LOG4CXX_TRACE(logger, "~AttestationIMVPolicyManager");
}

void AttestationIMVPolicyManager::parsePolicy(const char * policyFile)
{
	LOG4CXX_DEBUG(logger, "Parsing policy file " << policyFile);

	// clear old entries
	this->pcrEntries.clear();
	this->knownAiks.clear();

	std::ifstream file(policyFile);
	std::string line;

	// read file
	if(file.is_open()){
		while (std::getline(file, line)) {
			parsePolicyLine(line);
		}
	} else {
		LOG4CXX_WARN(logger, "Could not open file!");
	}
	file.close();

	for (unsigned int i = 0; i < this->knownAiks.size(); ++i) {
		LOG4CXX_TRACE(logger, "AIK " << i << " " << knownAiks[i]);
	}

	for (unsigned int i = 0; i < this->pcrEntries.size(); ++i) {
		LOG4CXX_DEBUG(logger, "pcr" << (unsigned int) pcrEntries[i].index << " " << pcrEntries[i].valueAsString);
	}

	LOG4CXX_TRACE(logger, "quoteType = " << (quoteType == single ? "single" : "complete"));
}

void AttestationIMVPolicyManager::parsePolicyLine(std::string &line)
{
	// remove any spaces
	line.erase(std::remove(line.begin(), line.end(), ' '), line.end());

	// skip empty lines
	if (line.length() == 0)
		return;
	// skip comments
	if (line[0] == '#')
		return;

	// in this version, there are three possible valid entries
	// pcr, aik, quoteType
	std::string saik("aik");
	std::string spcr("pcr");
	std::string squoteType("quoteType");

	if(!line.compare(0, saik.size(), saik.c_str())) {
		// an aik line
		parsePolicyLineAik(line);
	} else if(!line.compare(0, spcr.size(), spcr.c_str())) {
		// an pcr line
		parsePolicyLinePcr(line);
	} else if (!line.compare(0, squoteType.size(), squoteType.c_str())) {
		// an quoteType line
		parsePolicyLineQuoteType(line);
	} else {
		// an invalid line
		LOG4CXX_WARN(logger, "Invalid policy line: " << line);
	}
}

void AttestationIMVPolicyManager::parsePolicyLineAik(std::string &line)
{
	// format: aik=DC:30:E6:EA:F1:97:5D:90:E6:AE:D0:A3:C8:62:5C:61:93:9B:96:4B
	int pos = line.find_first_of('=');
	this->knownAiks.push_back(line.substr(pos+1));
}

void AttestationIMVPolicyManager::parsePolicyLinePcr(std::string &line)
{
	unsigned int index;
	std::stringstream hashValue;
	int pos;
	std::stringstream ss;

	// format: pcrX=<20 byte SHA-1 hash as 40 characters ASCII string>
	pos = line.find_first_of('=');
	// get pcr index
	ss << line.substr(3, pos - 3);
	LOG4CXX_DEBUG(logger, "ss = " << ss.str());
	ss >> index;

	// get hash value
	hashValue << line.substr(pos+1);

	// save pcr entry
	this->pcrEntries.push_back(PcrEntry(index, hashValue.str()));

}

void AttestationIMVPolicyManager::parsePolicyLineQuoteType(std::string &line)
{
	int pos;
	std::stringstream ss;

	// format: quoteType=complete
	//         quoteType=single
	pos = line.find_first_of('=');
	ss << line.substr(pos+1);
	if(!ss.str().compare("single")){
		quoteType = single;
	} else if (!ss.str().compare("complete")){
		quoteType = complete;
	} else {
		LOG4CXX_WARN(logger, "Invalid quoteType. Using 'complete' as default.");
		quoteType = complete;
	}
}


bool AttestationIMVPolicyManager::isAikKnown(std::string fingerprint)
{
	LOG4CXX_TRACE(logger, "isAikKnown()");
	std::vector<std::string>::iterator it;
	it = find(this->knownAiks.begin(), this->knownAiks.end(), fingerprint);
	return it == this->knownAiks.end() ? false : true;
}

QuoteType AttestationIMVPolicyManager::getQuoteType()
{
	LOG4CXX_TRACE(logger, "getQuoteType()");
	return this->quoteType;
}

std::vector<PcrEntry> AttestationIMVPolicyManager::getPcrEntries()
{
	LOG4CXX_TRACE(logger, "getPcrEntries()");
	return this->pcrEntries;
}

} // namespace iml

} // namespace tncfhh

