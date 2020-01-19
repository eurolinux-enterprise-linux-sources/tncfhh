/* tncimunit.h
 *
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

/** @file
 * TNC@FHH specific addons to the TCG specifications
 *
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>10.11.2008 - created the header with remaining definitions from the old fhhaddon.h (bhl)</li>
 * </ul>
 *
 * @date 10.11.2008
 * @author: Bastian Hellmann (bhl)
 */

#ifndef TNC_IMUNIT_H_
#define TNC_IMUNIT_H_

/**
 * IMUnit ID is the generalization of IMC/IMV ID.
 */
typedef unsigned long TNC_IMUnitID;

/**
 * Function pointer to bind function.
 */
typedef TNC_Result (*TNC_BindFunctionPointer)(
               TNC_IMUnitID id,
              char *functionName,
               void **pOutfunctionPointer
);

#endif /* TNC_IMUNIT_H_ */
