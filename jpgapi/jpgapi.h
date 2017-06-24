/* == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==
 * Notice : Copyright(C) 2017, Devuna
 * Distributed under LGPLv3(http ://www.gnu.org/licenses/lgpl.html)
 *
 * This file is part of Devuna - ScreenCaptureTools(https ://github.com/Devuna/Devuna-ScreenCaptureTools)
 *
 * Devuna - ScreenCaptureTools is free software : you can redistribute it and / or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Devuna - ScreenCaptureTools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Devuna - ScreenCaptureTools.If not, see <http://www.gnu.org/licenses/>.
 *
 *  jpgapi.h
 *
 *  Header file for Joint Photographic Experts Group (JPEG) API.  Provides
 *  function prototypes and constants for the following functions:
 *
 *  EncodeJPGFileFromDIB()        - Creates a JPG from a DIB
 *
 * See the file JPGAPI.TXT for more information about these functions.
 *
 */

#ifndef __IJL_H__
#include "IJL.h"
#endif

#define DllExport   __declspec( dllexport ) 

/* Handle to a DIB */
#define HDIB HANDLE

/* Function prototypes */

DllExport BOOL		FAR	EncodeJPGFileFromDIB(HDIB hDib, LPCSTR lpszPathName);
