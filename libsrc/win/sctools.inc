!region Notices
! ================================================================================
! Notice : Copyright (C) 2017, Devuna
!          Distributed under LGPLv3 (http://www.gnu.org/licenses/lgpl.html)
!
!    This file is part of Devuna-ScreenCaptureTools (https://github.com/Devuna/Devuna-ScreenCaptureTools)
!
!    Devuna-ScreenCaptureTools is free software: you can redistribute it and/or modify
!    it under the terms of the GNU General Public License as published by
!    the Free Software Foundation, either version 3 of the License, or
!    (at your option) any later version.
!
!    Devuna-ScreenCaptureTools is distributed in the hope that it will be useful,
!    but WITHOUT ANY WARRANTY; without even the implied warranty of
!    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
!    GNU General Public License for more details.
!
!    You should have received a copy of the GNU General Public License
!    along with Devuna-ScreenCaptureTools.  If not, see <http://www.gnu.org/licenses/>.
! ================================================================================
!endregion Notices

  SECTION('SCToolsEquates')
! Print Options selection
PW_DEFAULT          EQUATE(0)
PW_BESTFIT          EQUATE(1)
PW_STRETCHTOPAGE    EQUATE(2)
PW_SCALE            EQUATE(3)

! Print Area selection
PW_WINDOW           EQUATE(1)
PW_CLIENT           EQUATE(2)

VK_SNAPSHOT         EQUATE(02Ch)       !PRINT SCREEN key

! Error constants
  ITEMIZE(0),PRE()
ERR_MIN                 EQUATE         ! All error #s >= this value
ERR_NOT_DIB             EQUATE(0)      ! Tried to load a file, NOT a DIB!
ERR_MEMORY              EQUATE         ! Not enough memory!
ERR_READ                EQUATE         ! Error reading file!
ERR_LOCK                EQUATE         ! Error on a GlobalLock()!
ERR_OPEN                EQUATE         ! Error opening a file!
ERR_CREATEPAL           EQUATE         ! Error creating palette.
ERR_GETDC               EQUATE         ! Couldn't get a DC.
ERR_CREATEDDB           EQUATE         ! Error create a DDB.
ERR_STRETCHBLT          EQUATE         ! StretchBlt() returned failure.
ERR_STRETCHDIBITS       EQUATE         ! StretchDIBits() returned failure.
ERR_SETDIBITSTODEVICE   EQUATE         ! SetDIBitsToDevice() failed.
ERR_STARTDOC            EQUATE         ! Error calling StartDoc().
ERR_NOGDIMODULE         EQUATE         ! Couldn't find GDI module in memory.
ERR_SETABORTPROC        EQUATE         ! Error calling SetAbortProc().
ERR_STARTPAGE           EQUATE         ! Error calling StartPage().
ERR_NEWFRAME            EQUATE         ! Error calling NEWFRAME escape.
ERR_ENDPAGE             EQUATE         ! Error calling EndPage().
ERR_ENDDOC              EQUATE         ! Error calling EndDoc().
ERR_SETDIBITS           EQUATE         ! Error calling SetDIBits().
ERR_FILENOTFOUND        EQUATE         ! Error opening file in GetDib()
ERR_INVALIDHANDLE       EQUATE         ! Invalid Handle
ERR_DIBFUNCTION         EQUATE         ! Error on call to DIB function
ERR_MAX                 EQUATE         ! All dibapi error #s < this value
ERR_NOTINITIALIZED      EQUATE         ! SCCTOOLS library not initialized
ERR_FORMATNOTAVAILABLE  EQUATE         ! Clipboard Format not available
  END

  SECTION('SCToolsLibrary')
  MODULE('SCTOOLS.DLL')
    SCT_ClipboardToImage(UNSIGNED param_hWindow, LONG param_feq),USHORT,PROC,DLL(dll_mode)
    SCT_Init(UNSIGNED param_hWndApplication, UNSIGNED param_hWndClient, UNSIGNED param_hInstance),DLL(dll_mode)
    SCT_PrintClipboard(UNSIGNED  param_hWindow, LONG param_printOption=1, LONG param_wScaleX=1, LONG param_wScaleY=1, LONG param_x=0, LONG param_y=0),USHORT,PROC,DLL(dll_mode)
    SCT_PrintSelectedArea(LONG param_PrintOption=1, LONG param_ScaleX=1, LONG param_ScaleY=1, LONG param_x=0, LONG param_y=0),USHORT,PROC,DLL(dll_mode)
    SCT_PrintWindow(UNSIGNED param_hWindow, LONG param_printArea=1, LONG param_printOption=1, LONG param_wScaleX=1, LONG param_wScaleY=1, LONG param_x=0, LONG param_y=0),USHORT,PROC,DLL(dll_mode)
    SCT_SaveClipboard(UNSIGNED param_hWindow, *CSTRING param_szFilename, BYTE param_Compress=0),USHORT,PROC,DLL(dll_mode)
    SCT_SaveSelectedArea(*CSTRING param_szFilename, BYTE param_Compress=0),USHORT,PROC,DLL(dll_mode)
    SCT_SaveWindow(UNSIGNED param_hWindow, *CSTRING param_szFilename, LONG param_printArea=1, BYTE param_Compress=0),USHORT,PROC,DLL(dll_mode)
    SCT_Error(USHORT param_wResult),DLL(dll_mode)
    SCT_GetAppWindow(),UNSIGNED,DLL(dll_mode)
    SCT_GetAppClientWindow(),UNSIGNED,DLL(dll_mode)
  END
  MODULE('WIN32.LIB')
    SCT_GetClipboardOwner(),UNSIGNED,PASCAL,NAME('GetClipboardOwner')
    SCT_GetDesktopWindow(),UNSIGNED,PASCAL,NAME('GetDesktopWindow')
    SCT_GetTopWindow(UNSIGNED),UNSIGNED,PASCAL,NAME('GetTopWindow')
    SCT_CallWindowProc(ULONG,UNSIGNED,UNSIGNED,UNSIGNED,LONG),lONG,PASCAL,NAME('CallWindowProcA')
    SCT_ChangeClipboardChain(UNSIGNED, UNSIGNED),BOOL,PASCAL,PROC,NAME('ChangeClipboardChain')
    SCT_RegisterHotKey(UNSIGNED,SIGNED,UNSIGNED,UNSIGNED),BOOL,PASCAL,NAME('RegisterHotKey'),PROC
    SCT_SendMessage(UNSIGNED,UNSIGNED,UNSIGNED,LONG),ULONG,PASCAL,NAME('SendMessageA'),PROC
    SCT_SetClipboardViewer(UNSIGNED),UNSIGNED,PASCAL,NAME('SetClipboardViewer')
    SCT_UnregisterHotKey(UNSIGNED,SIGNED),BOOL,PASCAL,NAME('UnregisterHotKey'),PROC
    SCT_GetAsyncKeyState(UNSIGNED),SHORT,PASCAL,NAME('GetAsyncKeyState'),PROC
  END
