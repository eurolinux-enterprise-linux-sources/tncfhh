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
 * AttestationIMC
 *
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>01.03.10 - create class skeleton (awe)</li>
 *   <li>24.03.10 - renamed to AttestationIMC (awe)</li>
 * </ul>
 *
 * @date 24.03.10
 * @author Arne Welzel (awe)
 *
 */

#ifndef ATTESTATIONIMC_H_
#define ATTESTATIONIMC_H_


/* some defines */
#define ATTESTATIONIMC_X509_CERT		"x509_certificate_file"
#define	ATTESTATIONIMC_AIK_KEY			"aik_key_file"


/* Trousers TSS */
#include <trousers/tss.h>
#include <trousers/trousers.h>

/* IFIMC */
#include <tcg/tnc/tncifimc.h>

#include "imunit/imc/AbstractIMC.h"
#include "AttestationIMCLibrary.h"
#include "PcrSelection.h"


using namespace tncfhh::iml;
using namespace std;

class AttestationIMC : public AbstractIMC
{


private:
	
	/* context handle */
	TSS_HCONTEXT 	hContext;
	/* tpm handle */
	TSS_HTPM	hTPM;

	/* srk handle */
	TSS_HKEY	hSRK;

	/* srk policy handle */
	TSS_HPOLICY srkPolicy;

	/* aik handle */
	TSS_HKEY	hAIK;

	/* number of PCRs */
	UINT32		nPCR;


	/* able to start a handshake */
	bool				initialized;
	bool				certificateSent;

	/* place to store the x509 certificate */
	TNC_UInt32			certificateLength;
	TNC_BufferReference		certificate;

	/* place to store the aik blob */
	TNC_UInt32			aikBlobLength;
	TNC_BufferReference		aikBlob;

	TNC_UInt32			signatureLength;
	TNC_BufferReference		signature;

	string				certificateFile;
	string				aikBlobFile;


public:
	AttestationIMC(TNC_ConnectionID conID, AttestationIMCLibrary *imclib);

	~AttestationIMC();

	TNC_Result beginHandshake();

	TNC_Result receiveMessage(TNC_BufferReference message,
	                          TNC_UInt32 length, TNC_MessageType messageType);

	TNC_Result batchEnding();

	TNC_Result notifyConnectionChange();

private:
	/**
	 * Parse config file and set variables concerning:
	 *
	 * 	- path to public key file
	 *  - path to the aik blob file
	 */
	int loadConfigFile(void);


	/*
	 * Process one config line, can be comment...
	 */
	int processConfigLine(string configLine);
	void processCertificateLine(string configLine);
	void processAikKeyLine(string configLine);




	int loadX509Certificate(void);

	int loadAikBlob(void);

	/* helper to read files */
	int loadBlobToBuf(TNC_BufferReference *buf, const char *filename);

	 /*
	  * connect to tss,
	  * get tpm object, get number of pcrs
	  */
	int initTpmStuff(void);

	/*
	 * set number of Pcrs in nPCR using the before initialized context
	 */
	int setNumberOfPcrs(void);

	/*
	 * do the quote
	 */
	int doQuote(PcrSelection& ps, TNC_BufferReference nonce);

	void cleanup1(void);
	void cleanup2(void);
	void cleanup3(void);
	void cleanup4(void);
	void cleanup5(void);
};

#endif // ATTESTATIONIMC_H_
