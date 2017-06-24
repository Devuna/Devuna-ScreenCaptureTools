//********************************************************************
//
//  print.c
//
//  Source file for Device-Independent Bitmap (DIB) API.  Provides
//  the following functions:
//
//  PrintWindow()       - Prints all or part of a window
//  PrintScreen()       - Prints the entire screen
//  PrintDIB()          - Prints the specified DIB
//
// Development Team: Mark Bader
//                   Patrick Schreiber
//                   Garrett McAuliffe
//                   Eric Flo
//                   Tony Claflin
//                   Dan Ruder
//
// Written by Microsoft Product Support Services, Developer Support.
// COPYRIGHT:
//
//   (C) Copyright Microsoft Corp. 1993.  All rights reserved.
//
//   You have a royalty-free right to use, modify, reproduce and
//   distribute the Sample Files (and/or any modified version) in
//   any way you find useful, provided that you agree that
//   Microsoft has no warranty obligations or liability for any
//   Sample Application Files which are modified.
//
//********************************************************************

#include <windows.h>
#include <string.h>
#include "dibdll.h"     // Header for printing dialog & DLL instance handle
#include "dibapi.h"     // Header for DIB functions
#include "dibutil.h"    // Auxiliary functions


extern HANDLE $ghDLLInst;     // Global handle to DLL's instance

/***************************************************************
 * Typedefs
 **************************************************************/

/* Structure used for Banding */

typedef struct
{
   BOOL bGraphics;
   BOOL bText;
   RECT GraphicsRect;
} BANDINFOSTRUCT;


/****************************************************************
 * Variables
 ***************************************************************/

HWND hDlgAbort;                    // Handle to Abort Dialog
char szPrintDlg[] = "Printing";    // Name of Print dialog from .RC
BOOL bAbort = FALSE;               // Abort a print operation?
char gszDevice[50];                // Keeps track out device (e.g. "HP LaserJet")
char gszOutput[50];                // Output device (e.g. "LPT1:")

/***************************************************************
 * Function prototypes for functions local to this module
 **************************************************************/


BOOL FAR PASCAL PrintAbortProc(HDC, short);
BOOL FAR PASCAL PrintAbortDlg(HWND, unsigned, WORD, LPARAM);
WORD PrintBand(HDC, LPRECT, LPRECT, BOOL, BOOL, LPBITMAPINFOHEADER, LPSTR);
HDC GetPrinterDC(void);
void CalculatePrintRect(HDC, LPRECT, WORD, DWORD, DWORD);


/**********************************************************************
 *
 * PrintWindow()
 *
 *
 * Description:
 *
 * This function prints the specified window on the default
 * printer.
 *
 * Parameters:
 *
 * HWND hWnd       - Specifies the window to print.  The window must
 *                   not be iconic and must be topmost on the display.
 *
 * WORD fPrintArea - Specifies the area of the window to print.  Must be
 *                   one of PW_ALL, PW_CLIENT, PW_CAPTION,  or PW_MENUBAR
 *
 * WORD fPrintOpt  - Print options (one of PW_BESTFIT, PW_STRETCHTOPAGE, or
 *                   PW_SCALE)
 *
 * WORD wXScale, wYScale - X and Y scaling factors if PW_SCALE is specified
 *
 * LPSTR szJobName - Name that you would like to give to this print job (this
 *                   name shows up in the Print Manager as well as the
 *                   "Now Printing..." dialog box).
 * Return Value:
 *      ERR_DIBFUNCTION or any return value from PrintDIB
 *
 * History:   
 * 
 *     Date      Author       Reason         
 *     9/15/91   Mark Bader   Created         
 *
 **********************************************************************/
/*
WORD FAR PrintWindow(HWND hWnd,         // Window to be printed
                 WORD fPrintArea,   // Area of window to be printed
                 WORD fPrintOpt,    // Print options
                 WORD wXScale,      // X Scaling factor if PW_SCALE is used
                 WORD wYScale,      // Y Scaling factor if PW_SCALE is used
                 LPSTR szJobName)   // Name of print job
{
	POINT origin;
	origin.x = 0;
	origin.y = 0;
    return (PrintWindow2(hWnd,fPrintArea,fPrintOpt,wXScale,wYScale,szJobName,&origin));
}
*/

	
WORD FAR PrintWindow2(HWND hWnd,    // Window to be printed
                 WORD fPrintArea,   // Area of window to be printed
                 WORD fPrintOpt,    // Print options
                 WORD wXScale,      // X Scaling factor if PW_SCALE is used
                 WORD wYScale,      // Y Scaling factor if PW_SCALE is used
                 LPSTR szJobName,   // Name of print job
				 LPPOINT lpOrigin)	// image origin on printed page 
{
   HDIB hDib;          // Handle to the DIB
   WORD wReturn;       // our return value


   /*
    * Parameter validation
    */
   if (!hWnd)
      return (ERR_INVALIDHANDLE);  // Invalid Window

   /*
    * Copy the Window to a DIB and print it.
    */
   hDib = CopyWindowToDIB(hWnd, fPrintArea);
   if (!hDib)
      return (ERR_DIBFUNCTION); // CopyWindowToDIB failed!
   wReturn = PrintDIB2(hDib, fPrintOpt, wXScale, wYScale, szJobName, lpOrigin);

   /*
    * Call DestroyDIB to free the memory the dib takes up.
    */
   DestroyDIB(hDib);
   return wReturn;   // return the value from PrintDIB
}



/**********************************************************************
 *
 * PrintScreen()
 *
 *
 * Description:
 *
 * This function prints the specified portion of the display screen on the
 * default printer using the print options specified.  The print
 * options are listed in dibapi.h.
 *
 * Parameters:
 *
 * LPRECT rRegion  - Specifies the region of the screen (in screen
 *                   coordinates) to print
 *
 * WORD fPrintOpt  - Print options  (PW_BESTFIT, PW_STRETCHTOPAGE, or PW_SCALE)
 *
 * WORD wXScale, wYScale - X and Y scaling factors if PW_SCALE is specified
 *
 * LPSTR szJobName - Name that you would like to give to this print job (this
 *                   name shows up in the Print Manager as well as the
 *                   "Now Printing..." dialog box).
 *
 * Return Value:
 *      ERR_DIBFUNCTION or any return value from PrintDIB
 *
 * History:   
 * 
 *     Date      Author       Reason         
 *     9/15/91   Mark Bader   Created         
 *
 **********************************************************************/

WORD FAR PrintScreen(LPRECT rRegion,    // Region to print (in screen coords)
                 WORD fPrintOpt,    // print options
                 WORD wXScale,      // X scaling (used if PW_SCALE specified)
                 WORD wYScale,      // Y scaling (used if PW_SCALE specified)
                 LPSTR szJobName)   // Name of print job
{
	POINT origin;
	origin.x = 0;
	origin.y = 0;
	return (PrintScreen2(rRegion,fPrintOpt,wXScale,wYScale,szJobName, &origin));
}



WORD FAR PrintScreen2(LPRECT rRegion,   // Region to print (in screen coords)
                 WORD fPrintOpt,		// print options
                 WORD wXScale,			// X scaling (used if PW_SCALE specified)
                 WORD wYScale,			// Y scaling (used if PW_SCALE specified)
                 LPSTR szJobName,		// Name of print job
				 LPPOINT lpOrigin)		// image origin on printed page
{
   HDIB hDib;          // A Handle to our DIB
   WORD wReturn;       // Return value

   /*
    * Copy the screen contained in the specified rectangle to a DIB
    */
   hDib = CopyScreenToDIB(rRegion);
   if (!hDib)
      return (ERR_DIBFUNCTION);   // CopyScreenToDIB failed!
   wReturn = PrintDIB2(hDib, fPrintOpt, wXScale, wYScale, szJobName, lpOrigin);
   DestroyDIB(hDib);
   return wReturn; // Return the value that PrintDIB returned
}






/**********************************************************************
 *
 * PrintDIB()
 *
 * Description:
 *
 * This routine prints the specified DIB.  The actual printing is done
 * in the PrintBand() routine (see below), this procedure drives the
 * printing operation.  PrintDIB() has the code to handle both banding
 * and non-banding printers.  A banding printer can be distinguished by
 * the GetDeviceCaps() API (see the code below).  On banding devices,
 * must repeatedly call the NEXTBAND escape to get the next banding
 * rectangle to print into.  If the device supports the BANDINFO escape,
 * it should be used to determine whether the band "wants" text or
 * graphics (or both).  On non-banding devices, we can ignore all this
 * and call PrintBand() on the entire page.
 *
 * Parameters:
 *
 * HDIB hDib       - Handle to dib to be printed
 *
 * WORD fPrintOpt  - tells which print option to use (PW_BESTFIT,
 *                   PW_STRETCHTOPAGE, OR PW_SCALE)
 *
 * WORD wXScale, wYScale - X and Y scaling factors (integers) for
 *                   printed output if the PW_SCALE option is used.
 *
 * LPSTR szJobName - Name that you would like to give to this print job (this
 *                   name shows up in the Print Manager as well as the
 *                   "Now Printing..." dialog box).
 *
 * Return Value:  (see errors.h for description)
 *
 * One of: ERR_INVALIDHANDLE
 *         ERR_LOCK
 *         ERR_SETABORTPROC
 *         ERR_STARTDOC
 *         ERR_NEWFRAME
 *         ERR_ENDDOC
 *         ERR_GETDC
 *         ERR_STRETCHDIBITS
 *
 * History:   
 * 
 *     Date      Author       Reason         
 *     9/15/91   Mark Bader   Created, based on DIBVIEW's DibPrint()
 *
 ********************************************************************/

WORD FAR PrintDIB(HDIB hDib,    // Handle to the DIB
              WORD fPrintOpt,   // Print Options
              WORD wXScale,     // X Scaling factor
              WORD wYScale,     // Y Scaling factor
              LPSTR szJobName)  // Name of print job
{
	POINT origin;
	origin.x = 0;
	origin.y = 0;
    return (PrintDIB2(hDib,fPrintOpt,wXScale,wYScale,szJobName,&origin));	
}

WORD FAR PrintDIB2(HDIB hDib,   // Handle to the DIB
              WORD fPrintOpt,   // Print Options
              WORD wXScale,     // X Scaling factor
              WORD wYScale,     // Y Scaling factor
              LPSTR szJobName,  // Name of print job
			  LPPOINT lpOrigin)	// printer origin
{
   HDC hPrnDC;                  // DC to the printer
   RECT rect;                   // Rect structure used for banding
   LPSTR lpBits;                // pointer to the DIB bits
   LPBITMAPINFOHEADER lpDIBHdr; // Pointer to DIB header
   int nBandCount = 0;          // used for print dialog box to count bands
   WORD wErrorCode = 0;         // Error code to return
   RECT rPrintRect;             // Rect which specifies the area on the printer
                                // (in printer coordinates) which we
                                // want the DIB to go to
   char szBuffer[70];           // Buffer to hold message for "Printing" dlg box
   char szJobNameTrunc[35];     // szJobName truncated to 31 characters, since
                                // STARTDOC can't accept a string longer than 31
   DOCINFO di;

   /*
    * Paramter validation
    */
   if (!hDib)
      return (ERR_INVALIDHANDLE);

   /*
    * Get pointer to DIB header
    */
   lpDIBHdr = (LPBITMAPINFOHEADER)GlobalLock(hDib);
   if (!lpDIBHdr) // Check that we have a valid pointer
      return (ERR_LOCK);
   lpBits = FindDIBBits((LPSTR)lpDIBHdr); // Find pointer to DIB bits
   if (hPrnDC = GetPrinterDC())
   {
      SetStretchBltMode(hPrnDC, COLORONCOLOR);

      /*
       * Determine rPrintRect (printer area to print to) from the
       * fPrintOpt.  Fill in rPrintRect.right and .bottom from wXScale and
       * wYScale just in case we use PW_SCALE (see the function
       * CalculatePrintRect).
       */

	  rPrintRect.left = lpOrigin->x;
	  rPrintRect.top = lpOrigin->y;
      rPrintRect.right = wXScale;
      rPrintRect.bottom = wYScale;
      CalculatePrintRect(hPrnDC, &rPrintRect, fPrintOpt, lpDIBHdr->biWidth,
                         lpDIBHdr->biHeight);

      /*
       * Initialize the abort procedure.
       */
      hDlgAbort = CreateDialog($ghDLLInst, szPrintDlg, GetFocus(), (DLGPROC)PrintAbortDlg);

      /*
       * Set the text inside the dialog to the name of our print job
       */
      lstrcpy(szJobNameTrunc, szJobName);
      szJobNameTrunc[31] = '\0';           // Truncate string to 31 chars
      wsprintf(szBuffer, "Printing '%s'", (LPSTR)szJobNameTrunc);
      SetDlgItemText(hDlgAbort, IDC_PRINTTEXT1, (LPSTR)szBuffer);

      /*
       * Set global variable bAbort to FALSE.  This will get set to TRUE
       * in our PrintAbortDlg() procedure if the user selects the
       * CANCEL button in our dialog box
       */
      bAbort = FALSE;

      /*
       * Set up the Abort Procedure
       */
      if (SetAbortProc(hPrnDC,(ABORTPROC)PrintAbortProc) == SP_ERROR)
           return (ERR_SETABORTPROC);


      // Prepare the DOCINFO.
      ZeroMemory(&di, sizeof(di));
      di.cbSize = sizeof(di);
      di.lpszDocName = szJobNameTrunc;

      // Initialize the print job.
      if ((wErrorCode = StartDoc(hPrnDC, &di)) > 0) {

          // Prepare to send a page.
          if ((wErrorCode = StartPage(hPrnDC)) > 0) {

			  rect = rPrintRect;
			  SetDlgItemText(hDlgAbort, IDC_PERCENTAGE, (LPSTR)
				            "Sending bitmap to printer...");
			  wErrorCode = PrintBand(hPrnDC, &rPrintRect, &rect, TRUE, TRUE,
                                lpDIBHdr, lpBits);

              // Let the driver know the page is done.
              EndPage(hPrnDC);
          }

          // Let the driver know the document is done.
          EndDoc(hPrnDC);
      }

      /*
       * All done, clean up.
       */
      DestroyWindow(hDlgAbort);
      DeleteDC(hPrnDC);
   }
   else
      wErrorCode = ERR_GETDC;   // Couldn't get Printer DC!
   GlobalUnlock(hDib);
   return (wErrorCode);
}




// *******************************************************************
// Auxiliary Functions
//     -- Local to this module only
// *******************************************************************


/*********************************************************************
 *
 * CalculatePrintRect()
 *
 * Given fPrintOpt and a size of the DIB, return the area on the
 * printer where the image should go (in printer coordinates).  If
 * fPrintOpt is PW_SCALE, then lpPrintRect.right and .bottom should
 * contain WORDs which specify the scaling factor for the X and
 * Y directions, respecively.
 *
 * History:   
 * 
 *     Date      Author       Reason         
 *     9/15/91   Mark Bader   Created based on DIBVIEW
 *
 ********************************************************************/


void CalculatePrintRect(HDC hDC,             // HDC to printer DC
                        LPRECT lpPrintRect,  // Returned PrintRect
                        WORD fPrintOpt,      // Options
                        DWORD cxDIB,         // Size of DIB - x
                        DWORD cyDIB)         // Size of DIB - y
{
   int cxPage, cyPage, cxInch, cyInch;

   if (!hDC)
      return;

   /*
    * Get some info from printer driver
    */
   cxPage = GetDeviceCaps(hDC, HORZRES);     // Width of printr page - pixels
   cyPage = GetDeviceCaps(hDC, VERTRES);     // Height of printr page - pixels
   cxInch = GetDeviceCaps(hDC, LOGPIXELSX);  // Printer pixels per inch - X
   cyInch = GetDeviceCaps(hDC, LOGPIXELSY);  // Printer pixels per inch - Y
   switch (fPrintOpt)
      {

   /*
    * Best Fit case -- create a rectangle which preserves
    * the DIB's aspect ratio, and fills the page horizontally.
    *
    * The formula in the "->bottom" field below calculates the Y
    * position of the printed bitmap, based on the size of the
    * bitmap, the width of the page, and the relative size of
    * a printed pixel (cyInch / cxInch).
    */
   case PW_BESTFIT:
//      lpPrintRect->top = 0;
//      lpPrintRect->left = 0;
      lpPrintRect->bottom = (int)(((double)cyDIB * cxPage * cyInch) / ((double
                            )cxDIB * cxInch));
      lpPrintRect->right = cxPage;
      break;

   /*
    * Scaling option -- lpPrintRect's bottom/right contain
    * multipliers to multiply the DIB's height/width by.
    */

   case PW_SCALE:
   {
      int cxMult, cyMult;

      cxMult = lpPrintRect->right;
      cyMult = lpPrintRect->bottom;
//      lpPrintRect->top = 0;
//      lpPrintRect->left = 0;
      lpPrintRect->bottom = (int)(cyDIB * cyMult);
      lpPrintRect->right = (int)(cxDIB * cxMult);
   }
      break;

   /*
    * Stretch To Page case -- create a rectangle
    * which covers the entire printing page (note that this
    * is also the default).
    */
   case PW_STRETCHTOPAGE:
//      lpPrintRect->top = 0;
//      lpPrintRect->left = 0;
      lpPrintRect->bottom = cyPage;
      lpPrintRect->right = cxPage;
      break;

   case PW_DEFAULT:
   default:
      lpPrintRect->bottom = lpPrintRect->top + (cyDIB * cyInch / 72);
      lpPrintRect->right = lpPrintRect->left + (cxDIB * cxInch / 72);
      break;
      }
}



/*********************************************************************
 *
 * PrintBand()
 *
 * This routine does ALL output to the printer.  It is called from
 * the PrintDIB() routine.  It is called for both banding and non-
 * banding printing devices.  lpRectClip contains the rectangular
 * area we should do our output into (i.e. we should clip our output
 * to this area).  The flags fDoText and fDoGraphics should be set
 * appropriately (if we want any text output to the rectangle, set
 * fDoText to true).  Normally these flags are returned on banding
 * devices which support the BANDINFO escape.
 *
 * History:   
 * 
 *     Date      Author       Reason         
 *     9/15/91   Mark Bader   Created based on DIBVIEW
 *
 ********************************************************************/


WORD PrintBand(HDC hDC,           // Handle to the Printer DC
               LPRECT lpRectOut,  // Rect where entire DIB is to go
               LPRECT lpRectClip, // Clippping rect where this portion goes
               BOOL fDoText,      // TRUE if this band is for text
               BOOL fDoGraphics,  // TRUE if this band is for graphics
               LPBITMAPINFOHEADER lpDIBHdr,   // Pointer to DIB header
               LPSTR lpDIBBits)   // Pointer to DIB bits
{
   RECT rect;                   // Temporary rectangle
   double dblXScaling,          // X and Y scaling factors
          dblYScaling;
   WORD wReturn = 0;            // Return code

   if (fDoGraphics)
   {
      dblXScaling = ((double)lpRectOut->right - lpRectOut->left) / (double)
                    lpDIBHdr->biWidth;
      dblYScaling = ((double)lpRectOut->bottom - lpRectOut->top) / (double)
                    lpDIBHdr->biHeight;
      /*
       * Now we set up a temporary rectangle -- this rectangle
       *  holds the coordinates on the paper where our bitmap
       *  WILL be output.  We can intersect this rectangle with
       *  the lpClipRect to see what we NEED to output to this
       *  band.  Then, we determine the coordinates in the DIB
       *  to which this rectangle corresponds (using dbl?Scaling).
       */
      IntersectRect(&rect, lpRectOut, lpRectClip);
      if (!IsRectEmpty(&rect))
      {
         RECT rectIn;

         rectIn.left = (int)((rect.left - lpRectOut->left) / dblXScaling + 0.5
                       );
         rectIn.top = (int)((rect.top - lpRectOut->top) / dblYScaling + 0.5);
         rectIn.right = (int)(rectIn.left + (rect.right - rect.left) /
                        dblXScaling + 0.5);
         rectIn.bottom = (int)(rectIn.top + (rect.bottom - rect.top) /
                         dblYScaling + 0.5);
         if (!StretchDIBits(hDC,                              // DestDC
                            rect.left,                        // DestX
                            rect.top,                         // DestY
                            rect.right - rect.left,           // DestWidth
                            rect.bottom - rect.top,           // DestHeight
                            rectIn.left,                      // SrcX
                            (int)(lpDIBHdr->biHeight) -       // SrcY
                            rectIn.top - (rectIn.bottom - rectIn.top),
                            rectIn.right - rectIn.left,       // SrcWidth
                            rectIn.bottom - rectIn.top,       // SrcHeight
                            lpDIBBits,                        // lpBits
                            (LPBITMAPINFO)lpDIBHdr,           // lpBitInfo
                            DIB_RGB_COLORS,                   // wUsage
                            SRCCOPY))                         // dwROP
            wReturn = ERR_STRETCHDIBITS; // StretchDIBits() failed!
      }
   }
   return wReturn;
}


/***********************************************************************
 *
 * GetPrinterDC()
 *
 * Return a DC to the currently selected printer.
 * Returns NULL on error.
 *
 * History:   
 * 
 *     Date      Author       Reason         
 *     9/15/91   Mark Bader   Created based on DIBVIEW
 *
 ***********************************************************************/


HDC GetPrinterDC(void)
{
   static char szPrinter[64];
   char *szDevice, *szDriver, *szOutput;

   GetProfileString("windows", "device", "", szPrinter, 64);
   if ((szDevice = strtok(szPrinter, ",")) && (szDriver = strtok(NULL, ", "))
       && (szOutput = strtok(NULL, ", ")))
   {
      lstrcpy((LPSTR)gszDevice, (LPSTR)szDevice);    // Copy to global variables
      lstrcpy((LPSTR)gszOutput, (LPSTR)szOutput);
      return CreateDC(szDriver, szDevice, szOutput, NULL);
   }
   return NULL;
}


/**********************************************************************
 * PrintAbortProc()
 *
 * Abort procedure - contains the message loop while printing is
 * in progress.  By using a PeekMessage() loop, multitasking
 * can occur during printing.
 *
 * History:   
 * 
 *     Date      Author       Reason         
 *     9/15/91   Mark Bader   Created         
 *
 **********************************************************************/


BOOL FAR PASCAL PrintAbortProc(HDC hDC, short code)
{
   MSG msg;

   while (!bAbort && PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
      if (!IsDialogMessage(hDlgAbort, &msg))
      {
         TranslateMessage(&msg);
         DispatchMessage(&msg);
      }
   return (!bAbort);
}

/***********************************************************************
 *
 * PrintAbortDlg()
 *
 *
 * This is the Dialog Procedure which will handle the "Now Printing"
 * dialog box.  When the user presses the "Cancel" button, the
 * global variable bAbort is set to TRUE, which causes the
 * PrintAbortProc to exit, which in turn causes the printing
 * operation to terminate.
 *
 * History:   
 * 
 *     Date      Author       Reason         
 *     9/15/91   Mark Bader   Created         
 *
 ***********************************************************************/


BOOL FAR PASCAL PrintAbortDlg(HWND hWnd,    /* Handle to dialog box */ 
							 unsigned msg, /* Message */ 
							 WORD wParam, 
							 LPARAM lParam)
{
   switch (msg)
      {
   case WM_INITDIALOG:
   {
      char szBuffer[100];

      /*
       * Fill in the text which specifies where this bitmap
       * is going ("on HP LaserJet on LPT1", for example)
       */

      wsprintf(szBuffer, "on %s on %s", (LPSTR)gszDevice, (LPSTR)gszOutput);
      SetDlgItemText(hWnd, IDC_PRINTTEXT2, (LPSTR)szBuffer);
      SetFocus(GetDlgItem(hWnd, IDCANCEL));
   }
      return TRUE;     // Return TRUE because we called SetFocus()

   case WM_COMMAND:
      bAbort = TRUE;
      DestroyWindow(hWnd);
      return TRUE;
      break;
      }
   return FALSE;
}
