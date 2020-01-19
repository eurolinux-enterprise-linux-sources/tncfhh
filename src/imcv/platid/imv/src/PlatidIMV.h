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

/**
 * PlatidIMV
 *
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>24.11.2009 - create class skeleton (awe)</li>
 *   <li>  .11.2009 - simple prototype which sends "something" and checks the
 *   			signature against the given certificate (awe)</li>
 *   <li>06.12.2009 - Use RAND_bytes() to generate the nonce. (awe)</li>
 *   <li>08.12.2009 - Added CertManager member to be used for cert lookups (awe)</li>
 *   <li>10.12.2009 - Added missing "return TNC_RESULT_SUCCESS" (awe)</li>
 *   <li>16.12.2009 - Directly store the x509 cert on receiving (awe)</li>
 *   <li>16.12.2009 - noncesize is now RSA_size(ras) - 11 (awe)</li>
 *   <li>16.12.2009 - Refactoring (awe)</li>
 * </ul>
 *
 * @date 24.11.09
 * @author Arne Welzel (awe)
 *
 *
 * TODO:
 * - generate nonce with OpenSSL rand()					(ok)
 *
 * - Is the nonce size dependent on the given x509 cert (or key)	(ok)
 *
 * - check if the given x509 cert is know				(ok)
 *   look it up, "somewhere",  config file with DNs?,
 *   should be implemented in the library, as every IMV would
 *   use the same lookup method
 *
 * - Known x509 cert, Unknown x509 cert, x509 cert from a tpm key?	(NICE TO HAVE)
 *   signature was ok?	
 *   Differ the outcomes of a handshake with a policy.
 */

#ifndef PLATIDIMV_H_
#define PLATIDIMV_H_

/* default includes */
#include "tcg/tnc/tncifimc.h"
#include "imunit/imv/AbstractIMV.h"
#include "PlatidIMVLibrary.h"
#include "CertManager.h"

/* openssl includes */
#include <openssl/rsa.h>
#include <openssl/rand.h>

using namespace tncfhh::iml;
using namespace std;


class PlatidIMV : public tncfhh::iml::AbstractIMV
{
private:
	X509			*x509Cert;
	EVP_PKEY		*pKey;
	RSA			*rsa;
	TNC_BufferReference	randNonce;
	TNC_UInt32		randNonceLength;
	bool			nonceSent;
	CertManager		*certManager;
	bool			nothingWrong;

public:
	PlatidIMV(TNC_ConnectionID conID,
			PlatidIMVLibrary *imclib,
			CertManager * cm);

	~PlatidIMV();

	TNC_Result receiveMessage(TNC_BufferReference message, TNC_UInt32 length,
			TNC_MessageType type);

	TNC_Result notifyConnectionChange(TNC_ConnectionState newState);

	TNC_Result solicitRecommendation();

private:
	/**
	 * Uses the next three methods to process the first message of the
	 * IMC which contains the X509 Certificate.
	 */
	int processFirstMessage(TNC_BufferReference message, TNC_UInt32 length);

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
	int generateAndSendNonce();


	/**
	 * Check if the signature of the IMV is good.
	 * returns the recommendation to be given to the TNCS
	 */
	TNC_IMV_Action_Recommendation
	verifySignature(TNC_BufferReference sig, TNC_UInt32 length);

	/**
	 * frees the possible allocated OpenSSL objects and
	 * nonce
	 */
	void cleanup();

};

#endif // PLATIDIMV_H_
