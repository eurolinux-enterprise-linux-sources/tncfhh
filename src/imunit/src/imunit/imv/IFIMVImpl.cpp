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

#include "IMVLibrary.h"

#ifdef __WINDOWS__
#  include <windows.h>
#endif // __WINDOWS__


/**
 * @file
 * @see TNCFHH_IMVLIBRARY_INITIALIZE macro
 *
 * TODO - remove this file in next release > 0.6.0
 *
 * <h3>Changelog:</h3>
 * <ul>
 *   <li>09.05.2006 - create class (Daniel Wuttke)</li>
 *   <li>00.02.2008 - completely redesign (ib & mbs)</li>
 *   <li>12.02.2008 - attributeFunctions set to NULL in terminate (ib)</li>
 *   <li>08.05.2008 - change namespace (mbs)</li>
 *   <li>10.05.2008 - add some try/catch-blocks and remove some bugs (mbs)</li>
 *   <li>10.05.2008 - add getImvInstances() code (mbs)</li>
 *   <li>16.06.2009 - redesign (ib)</li>
 *   <li>30.08.2009 - insert this cpp in the macro TNCFHH_IMVLIBRARY_INITIALIZE in IMVLibrary.h (mbs)</li>
 * </ul>
 *
 * @date 09.05.2006
 * @author Daniel Wuttke
 * @author Ingo Bente (ib)
 * @author Mike Steinmetz
 *
 */
