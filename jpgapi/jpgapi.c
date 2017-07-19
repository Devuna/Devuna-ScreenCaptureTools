/* == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==
 * Notice : Copyright(C) 2017, Devuna
 * Distributed under the MIT License (https://opensource.org/licenses/MIT)
 *
 * This file is part of Devuna - ScreenCaptureTools(https ://github.com/Devuna/Devuna-ScreenCaptureTools)
 *
 * Devuna - ScreenCaptureTools is free software : you can redistribute it and / or modify
 * it under the terms of the MIT License as published by the Open Source Initiative.
 *
 * Devuna - ScreenCaptureTools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 * MIT License for more details.
 *
 * You should have received a copy of the MIT License
 * along with Devuna - ScreenCaptureTools.If not, see <https://opensource.org/licenses/MIT>.
 *
 * jpgapi.c
 *
 */
#include <windows.h>
#include <assert.h>
#include <stdio.h>
#include "jpgapi.h"

//----------------------------------------------------------
// An example using the IntelR JPEG Library:
// -- Encode a JFIF file from Windows DIB.
//----------------------------------------------------------
BOOL EncodeJPGFileFromDIB(
  HDIB hDib,
  LPCSTR lpszPathName)
{
  LPBITMAPINFOHEADER bmih;
  BOOL bres;
  IJLERR jerr;
  DWORD dib_pad_bytes;

  // Allocate the IJL JPEG_CORE_PROPERTIES structure.
  JPEG_CORE_PROPERTIES jcprops;

  bres = FALSE;

  __try
  {
     // Initialize the IntelR JPEG Library.
     jerr = ijlInit(&jcprops);
     if(IJL_OK != jerr)
     {
       bres = TRUE;
       __leave;
     }

	 /*
     * Get pointer to DIB header
     */
    bmih = (LPBITMAPINFOHEADER)GlobalLock(hDib);
    if (!bmih) // Check that we have a valid pointer
    {
      bres = TRUE;
      __leave;
    }

    if(bmih->biBitCount != 24)
    {
      // not supported palette images
      bres = TRUE;
      __leave;
    }

    dib_pad_bytes = IJL_DIB_PAD_BYTES(bmih->biWidth,3);
    // Set up information to write from the pixel buffer.
    jcprops.DIBWidth = bmih->biWidth;
    jcprops.DIBHeight = -(bmih->biHeight); // Implies a top-down DIB.
    jcprops.DIBBytes = (BYTE*)(bmih) + sizeof(BITMAPINFOHEADER);
    jcprops.DIBPadBytes = dib_pad_bytes;
    // Note: the following are default values and thus
    // do not need to be set.
    jcprops.DIBChannels = 3;
    jcprops.DIBColor = IJL_BGR;
    jcprops.JPGFile = (LPSTR)(lpszPathName);
    // Specify JPEG file creation parameters.
    jcprops.JPGWidth = bmih->biWidth;
    jcprops.JPGHeight = bmih->biHeight;
    // Note: the following are default values and thus
    // do not need to be set.
    jcprops.JPGChannels = 3;
    jcprops.JPGColor = IJL_YCBCR;
    jcprops.JPGSubsampling = IJL_411; // 4:1:1 subsampling.
    jcprops.jquality = 75; // Select "good" image quality
    // Write the actual JPEG image from the pixel buffer.
    jerr = ijlWrite(&jcprops,IJL_JFILE_WRITEWHOLEIMAGE);

    if(IJL_OK!=jerr)
    {
      bres=TRUE;
      __leave;
    }
  }//__try

  __finally
  {
    //CleanuptheIntelRJPEGLibrary.
    ijlFree(&jcprops);
  }

  GlobalUnlock(hDib);
  return(bres);

}//EncodeJPGFileFromDIB()
