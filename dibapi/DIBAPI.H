/*
 *  dibapi.h
 *
 *  Copyright (c) 1991 Microsoft Corporation. All rights reserved
 *
 *  Header file for Device-Independent Bitmap (DIB) API.  Provides
 *  function prototypes and constants for the following functions:
 *
 *  BitmapToDIB()        - Creates a DIB from a bitmap
 *  ChangeBitmapFormat() - Changes a bitmap to a specified DIB format
 *  ChangeDIBFormat()    - Changes a DIB's BPP and/or compression format
 *  CopyScreenToBitmap() - Copies entire screen to a standard Bitmap
 *  CopyScreenToDIB()    - Copies entire screen to a DIB
 *  CopyWindowToBitmap() - Copies a window to a standard Bitmap
 *  CopyWindowToDIB()    - Copies a window to a DIB
 *  CreateDIBPalette()   - Creates a palette from a DIB
 *  CreateDIB()          - Creates a new DIB
 *  DestroyDIB()         - Deletes DIB when finished using it
 *  DIBError()           - Displays message box with error message
 *  DIBHeight()          - Gets the DIB height
 *  DIBNumColors()       - Calculates number of colors in the DIB's color table
 *  DIBToBitmap()        - Creates a bitmap from a DIB
 *  DIBWidth()           - Gets the DIB width
 *  FindDIBBits()        - Sets pointer to the DIB bits
 *  GetSystemPalette()   - Gets the current palette
 *  LoadDIB()            - Loads a DIB from a file
 *  PaintBitmap()        - Displays standard bitmap in the specified DC
 *  PaintDIB()           - Displays DIB in the specified DC
 *  PalEntriesOnDevice() - Gets the number of palette entries
 *  PaletteSize()        - Calculates the buffer size required by a palette
 *  PrintDIB()           - Prints the specified DIB
 *  PrintScreen()        - Prints the entire screen
 *  PrintWindow()        - Prints all or part of a window
 *  SaveDIB()            - Saves the specified dib in a file
 *
 * See the file DIBAPI.TXT for more information about these functions.
 *
 */


#define NOMIRRORBITMAP      (DWORD)0x80000000 /* Do not Mirror the bitmap in this call */
#define CAPTUREBLT          (DWORD)0x40000000 /* Include layered windows */




/* Handle to a DIB */
#define HDIB HANDLE


/* Print Area selection */
#define PW_WINDOW        1
#define PW_CLIENT        2


/* Print Options selection */
#define PW_DEFAULT		 0
#define PW_BESTFIT       1
#define PW_STRETCHTOPAGE 2
#define PW_SCALE         3

/* DIB Macros*/

// WIDTHBYTES performs DWORD-aligning of DIB scanlines.  The "bits"
// parameter is the bit count for the scanline (biWidth * biBitCount),
// and this macro returns the number of DWORD-aligned bytes needed 
// to hold those bits.

#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)

/* Error constants */
enum {
      ERR_MIN = 0,                     // All error #s >= this value
      ERR_NOT_DIB = 0,                 // Tried to load a file, NOT a DIB!
      ERR_MEMORY,                      // Not enough memory!
      ERR_READ,                        // Error reading file!
      ERR_LOCK,                        // Error on a GlobalLock()!
      ERR_OPEN,                        // Error opening a file!
      ERR_CREATEPAL,                   // Error creating palette.
      ERR_GETDC,                       // Couldn't get a DC.
      ERR_CREATEDDB,                   // Error create a DDB.
      ERR_STRETCHBLT,                  // StretchBlt() returned failure.
      ERR_STRETCHDIBITS,               // StretchDIBits() returned failure.
      ERR_SETDIBITSTODEVICE,           // SetDIBitsToDevice() failed.
      ERR_STARTDOC,                    // Error calling StartDoc().
      ERR_NOGDIMODULE,                 // Couldn't find GDI module in memory.
      ERR_SETABORTPROC,                // Error calling SetAbortProc().
      ERR_STARTPAGE,                   // Error calling StartPage().
      ERR_NEWFRAME,                    // Error calling NEWFRAME escape.
      ERR_ENDPAGE,                     // Error calling EndPage().
      ERR_ENDDOC,                      // Error calling EndDoc().
      ERR_SETDIBITS,                   // Error calling SetDIBits().
      ERR_FILENOTFOUND,                // Error opening file in GetDib()
      ERR_INVALIDHANDLE,               // Invalid Handle
      ERR_DIBFUNCTION,                 // Error on call to DIB function
      ERR_MAX                          // All error #s < this value
     };

#define DllExport   __declspec( dllexport ) 

/* Function prototypes */

DllExport HDIB      FAR  BitmapToDIB (HBITMAP hBitmap, HPALETTE hPal);
DllExport HDIB      FAR  ChangeBitmapFormat (HBITMAP  hBitmap,
                                   WORD     wBitCount,
                                   DWORD    dwCompression,
                                   HPALETTE hPal);
DllExport HDIB      FAR  ChangeDIBFormat (HDIB hDIB, WORD wBitCount,
                                DWORD dwCompression);
DllExport HBITMAP   FAR  CopyScreenToBitmap (LPRECT);
DllExport HDIB      FAR  CopyScreenToDIB (LPRECT);
DllExport HBITMAP   FAR  CopyWindowToBitmap (HWND, WORD);
DllExport HDIB      FAR  CopyWindowToDIB (HWND, WORD);
DllExport HPALETTE  FAR  CreateDIBPalette (HDIB hDIB);
DllExport HDIB      FAR  CreateDIB(DWORD, DWORD, WORD);
DllExport WORD      FAR  DestroyDIB (HDIB);
DllExport CHAR *    FAR  DIBError (int ErrNo);
DllExport DWORD     FAR  DIBHeight (LPSTR lpDIB);
DllExport WORD      FAR  DIBNumColors (LPSTR lpDIB);
DllExport HBITMAP   FAR  DIBToBitmap (HDIB hDIB, HPALETTE hPal);
DllExport DWORD     FAR  DIBWidth (LPSTR lpDIB);
DllExport LPSTR     FAR  FindDIBBits (LPSTR lpDIB);
DllExport HPALETTE  FAR  GetSystemPalette (void);
DllExport HDIB      FAR  LoadDIB (LPSTR);
DllExport BOOL      FAR  PaintBitmap (HDC, LPRECT, HBITMAP, LPRECT, HPALETTE);
DllExport BOOL      FAR  PaintDIB (HDC, LPRECT, HDIB, LPRECT, HPALETTE);
DllExport int       FAR  PalEntriesOnDevice (HDC hDC);
DllExport WORD      FAR  PaletteSize (LPSTR lpDIB);
DllExport WORD      FAR  PrintDIB (HDIB, WORD, WORD, WORD, LPSTR);
DllExport WORD      FAR  PrintDIB2 (HDIB, WORD, WORD, WORD, LPSTR, LPPOINT);
DllExport WORD      FAR  PrintScreen (LPRECT, WORD, WORD, WORD, LPSTR);
DllExport WORD      FAR  PrintScreen2 (LPRECT, WORD, WORD, WORD, LPSTR, LPPOINT);
/*DllExport WORD      FAR  PrintWindow (HWND, WORD, WORD, WORD, WORD, LPSTR);*/
DllExport WORD      FAR  PrintWindow2 (HWND, WORD, WORD, WORD, WORD, LPSTR, LPPOINT);
DllExport WORD      FAR  SaveDIB (HDIB, LPSTR);

