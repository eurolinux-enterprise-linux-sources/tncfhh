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
 * TNC@FHH specific addons to the TCG specifications
 *
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>15.08.2006 - create (MS)</li>
 *   <li>15.02.2008 - comments/change (ib)</li>
 *   <li>11.04.2008 - add connectionCreate (mbs)</li>
 *   <li>22.07.2009 - redesign for TNC@FHH 0.6.0 (mbs)</li>
 * </ul>
 *
 * @date 15.08.2006
 * @author Martin Schmiedel (MS)
 * @author: Mike Steinmetz (mbs)
 * @author: Ingo Bente (ib)
 */
#ifndef FHHADDON_H_
#define FHHADDON_H_

#define EAP_TNC_HEADER_FLAGS_SIZE        1
#define EAP_TNC_HEADER_DATA_LENGTH_SIZE  4

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32
#ifdef TNC_IMV_EXPORTS
#define TNC_IMV_API __declspec(dllexport)
#else
#define TNC_IMV_API __declspec(dllimport)
#endif
#else
#define TNC_IMV_API
#endif

/**
 * For convenience.
 */
typedef unsigned char TNC_Buffer;

/**
 * For convenience.
 */
typedef const unsigned char * TNC_BufferConstReference;

/**
 * For using user-specific policies
 */
#define TNC_ATTRIBUTEID_USERNAME ((TNC_AttributeID) 0x10000001)

#ifdef __cplusplus
}
#endif

#endif /*FHHADDON_H_*/
