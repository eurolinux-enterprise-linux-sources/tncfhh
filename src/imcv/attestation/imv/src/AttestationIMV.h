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
 * AttestationIMV
 *
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>08.03.2010 - create class skeleton (ib)</li>
 *   <li>24.03.2010 - renamed to AttestationIMV (awe)</li>
 * </ul>
 *
 * @date 08.03.10
 * @author Ingo Bente (ib)
 *
 */

#ifndef ATTESTATIONIMV_H_
#define ATTESTATIONIMV_H_

/* default includes */
#include "tcg/tnc/tncifimc.h"
#include "imunit/imv/AbstractIMV.h"
#include "AttestationIMVLibrary.h"
#include "AttestationIMVPolicyManager.h"

/* openssl includes */
#include <openssl/rsa.h>
#include <openssl/rand.h>
#include <openssl/sha.h>

#include <vector>

using namespace tncfhh::iml;
using namespace std;


class AttestationIMV : public tncfhh::iml::AbstractIMV
{
private:
	X509				*x509Cert;
	EVP_PKEY			*pKey;
	RSA					*rsa;
	AttestationIMVPolicyManager	*policyManager;
	bool				nothingWrong;
	bool				firstMessage;
	TNC_Buffer			quoteDigest[SHA_DIGEST_LENGTH];
	QuoteType			quoteType;
	vector<PcrEntry>	entries;
	int				currentEntry;

public:
	AttestationIMV(TNC_ConnectionID conID,
			AttestationIMVLibrary *imclib,
			AttestationIMVPolicyManager * pm);

	~AttestationIMV();

	TNC_Result receiveMessage(TNC_BufferReference message, TNC_UInt32 length,
			TNC_MessageType type);

	TNC_Result notifyConnectionChange(TNC_ConnectionState newState);

	TNC_Result solicitRecommendation();

private:
	/**
	 * Uses the next three methods to process the first message of the
	 * IMC which contains the X509 Certificate. We need to extract
	 * the Public Key and the corresponding RSA object.
	 */
	int processFirstMessage(TNC_BufferReference message, TNC_UInt32 length);

	/**
	 * Detect if a blob is ASN.1 encoded
	 */
	bool isASN1(TNC_BufferReference message, TNC_UInt32 length);

	/**
	 * The first message should be the X509 Certificate,
	 * this method creates a X509 object to work with.
	 * OpenSSLs BIO is used to do this.
	 *
	 * returns 0 on success -1 on failure
	 */
	int loadX509Cert(TNC_BufferReference message, TNC_UInt32 length);


	/**
	 * Extract a EVP_PKEY object from the X509 Certificate
	 *
	 * returns 0 on success -1 on failure
	 */
	int loadPKey(void);

	/**
	 * Extract a RSA object from the EVP_PKEY object
	 *
	 * return 0 on success -1 on failure
	 */
	int loadRSA(void);


	/**
	 * Generate a nonce with RAND_bytes() from Openssl
	 */
	
	bool checkClientKnown();

	int sendQuoteRequest(std::vector<PcrEntry>& entries);

	int calculateQuoteDigest(unsigned int maskLen,
			unsigned char *buf, std::vector<PcrEntry>& entries);

	void cleanup();

};

#endif // ATTESTATIONIMV_H_
