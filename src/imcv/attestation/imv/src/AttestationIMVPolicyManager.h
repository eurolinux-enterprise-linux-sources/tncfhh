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

/**
 * AttestationIMVPolicyManager.
 *
 * Class for querying AttestationIMV specific entries in the policy file.
 *
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>08.03.2010 - create class skeleton (ib)</li>
 *   <li>09.03.2010 - functionally complete (ib)</li>
 *   <li>24.03.2010 - renamed to AttestationIMVPolicyManager (awe)</li>
 * </ul>
 *
 * @date 08.03.2010
 * @author Ingo Bente (ib)
 *
 *
 */
#ifndef ATTESTATIONIMVPOLICYMANAGER_H_
#define ATTESTATIONIMVPOLICYMANAGER_H_

#include <iostream>
#include <vector> // vector
#include <stdint.h> // uint8_t
#include "attestationimvConfig.h"


namespace tncfhh {

namespace iml {

/**
 * This class represents a pcr entry from the policy.
 */
class PcrEntry {
public:
	unsigned int index;
	uint8_t value[20];
	std::string valueAsString;

	PcrEntry(unsigned int index = 0, std::string valueAsString = "0000000000000000000000000000000000000000");
	~PcrEntry();

private:
	/**
	 * Converts valueAsString to an array of byte.
	 *
	 * @param valueAsString SHA-1 hash string representation
	 */
	void stringToByteArray(const std::string &valueAsString);
};

/**
 * Enum that represents the possible values for the quoteType entry in the policy.
 */
enum QuoteType
{
	single,
	complete
};

class AttestationIMVPolicyManager
{
public:

	/**
	 * Ctor.
	 */
	AttestationIMVPolicyManager(const char *policyFile = IMV_CONFIG);

	/**
	 * Dtor.
	 */
	~AttestationIMVPolicyManager();


	/**
	 * Parses the policy file of the AttestationIMV.
	 */
	void parsePolicy(const char * policyFile);

	/**
	 * Checks if an AIK is known (i.e. properly configured in the policy file).
	 * This is done based upon the fingerprints of the AIKs.
	 *
	 * @param fingerprint - the fingerprint of the AIK that should be checked
	 *                      against the entries in the policy file.
	 */
	bool isAikKnown(std::string fingerprint);

	/**
	 * Returns the quoteType that was configured in the policy file.
	 */
	QuoteType getQuoteType();

	/**
	 * Returns a vector of PcrEntry objects. For each PCR entry in the
	 * policy file, this vector contains a corresponding object.
	 */
	std::vector<PcrEntry> getPcrEntries();

private:
	/**
	 * A list of all known AIKs.
	 * (fingerprint as std::string)
	 */
	std::vector<std::string> knownAiks;

	/**
	 * The quoteType.
	 */
	QuoteType quoteType;

	std::vector<PcrEntry> pcrEntries;

	/**
	 * Parses a line of the policy file
	 */
	void parsePolicyLine(std::string &line);
	void parsePolicyLineAik(std::string &line);
	void parsePolicyLinePcr(std::string &line);
	void parsePolicyLineQuoteType(std::string &line);
};

} // namespace iml

} // namespace tncfhh

#endif // ATTESTATIONIMVPOLICYMANAGER_H_
