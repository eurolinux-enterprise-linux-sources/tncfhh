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
 * PlatidIMC.
 *
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>10.11.2009 - create class skeleton (awe)</li>
 *   <li>24.11.2009 - first prototype for use with mod. openssl_tpm_engine (awe)</li>
 *   <li>05.12.2009 - prototype which additionally supports software keys (awe)</li>
 *   <li>15.12.2009 - added code to read a config file given in the PlatidIMCConfig.h(awe)</li>
 *   <li>16.12.2009 - added error handling to the encryption of the nonce</li>
 * </ul>
 *
 * @date 10.11.09
 * @author Arne Welzel (awe)
 *
 * TODO:
 * 	- Use a config file for the key locations			(done)
 *
 * 	- Options to set whether tpm should be used or not?		(TODO)
 *
 * 	- Fix conversion warnings from char* to string			(done)
 */

#ifndef PLATIDIMC_H_
#define PLATIDIMC_H_


/* some defines */
#define	PLATIDIMC_TPM_ENGINE			"tpm"
#define PLATIDIMC_CONFIG_USE_WKS		"use_wks_srk"
#define PLATIDIMC_CONFIG_KEY_FILE		"private_key_file"
#define PLATIDIMC_CONFIG_CERTIFICATE_FILE	"x509_certificate_file"

/* Control index to set the srk secret */
#define TPM_CMD_PIN				ENGINE_CMD_BASE + 1

/* default includes */
#include "tcg/tnc/tncifimc.h"
#include "imunit/imc/AbstractIMC.h"
#include "PlatidIMCLibrary.h"

/* openssl includes */
#include "openssl/rsa.h"
#include "openssl/engine.h"


using namespace tncfhh::iml;
using namespace std;

class PlatidIMC : public AbstractIMC
{


private:
	/* engine handle to tpm engine */
	ENGINE *engine;
	
	/* RSA structure */
	RSA *rsa;

	/* place to store the X509 certificate,
	 * as string ! */
	string certificate;

	/* able to start a handshake */
	bool initialized;

	/* set if we succeed in initializing the openssl_tpm_engine */
	bool useTpm;

	/* those are read from the config file */
	bool useWksSrk;
	string certificateFile;
	string privateKeyFile;


public:
	PlatidIMC(TNC_ConnectionID conID, PlatidIMCLibrary *imclib);

	virtual ~PlatidIMC();

	TNC_Result beginHandshake();

	TNC_Result receiveMessage(TNC_BufferReference message,
	                          TNC_UInt32 length, TNC_MessageType messageType);

	TNC_Result batchEnding();

	TNC_Result notifyConnectionChange();


private:
	/**
	 * Parse config file and set variables concerning:
	 *
	 * 	- use WKS for SRK
	 * 	- path to private key
	 * 	- path to X509 certificate
	 *
	 */
	int loadConfigFile(void);


	/*
	 * The next three deal config lines with
	 * for special entries.
	 */
	void processUseWksLine(string configLine);
	void processPrivateKeyLine(string configLine);
	void processCertificateFileLine(string configLine);



	/**
	 * Process one config line, can be comment, or one of the three settings:
	 *
	 * 	use_wks_srk
	 * 	private_key_file
	 * 	x509_certificate_file
	 *
	 * private_key_file and x509_certificate_file must be set. use_wks_srk
	 * is default "no".
	 *
	 */
	int processConfigLine(string configLine);

	/**
	 * Initialize openssl engine to be used
	 *
	 *
	 * returns	0 if we use the tpm_engine
	 * 		1 if we use another engine (software)
	 *		-1 on failure;
	 */
	int initializeEngine(void);

	/*
	 * returns 0 on success -1 on failure
	 */
	int loadCertificate(void);


	/*
	 * return 0 on success -1 on failure
	 */
	int loadRsa(void);

	/*
	 * return a pointer to the EVP_PKEY structure
	 * NULL on failure!
	 */
	EVP_PKEY * swLoadEvpPkey();
	EVP_PKEY * tpmLoadEvpPkey();

	/*
	 * sign the data given in nonce and store the signature into
	 * dest.
	 * dest should have a length of RSA_size(rsa) bytes.
	 *
	 * returns the length of the signature in dest or -1 on error
	 */
	int signNonce(TNC_BufferReference nonce, TNC_UInt32 length,
			TNC_BufferReference dest);
};

#endif // PLATIDIMC_H_
