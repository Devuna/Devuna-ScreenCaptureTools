   PROGRAM




   INCLUDE('ABERROR.INC'),ONCE
   INCLUDE('ABUTIL.INC'),ONCE
   INCLUDE('ERRORS.CLW'),ONCE
   INCLUDE('KEYCODES.CLW'),ONCE
   INCLUDE('ABFUZZY.INC'),ONCE
eSCTHOTKEY          EQUATE(CtrlMouseRight)                 !PrintScreen Key
 ITEMIZE(EVENT:USER),PRE(EVENT)
StartAbout              EQUATE
StartClipboardDemo      EQUATE
 END
    INCLUDE('PRNPROP.CLW')
   INCLUDE('SCTOOLS.INC','SCToolsEquates')

   MAP
     MODULE('SCT_DEMO_BC.CLW')
DctInit     PROCEDURE                                      ! Initializes the dictionary definition module
DctKill     PROCEDURE                                      ! Kills the dictionary definition module
     END
!--- Application Global and Exported Procedure Definitions --------------------------------------------
     MODULE('SCT_DEMO001.CLW')
Main                   PROCEDURE   !
     END
     MODULE('SCT_DEMO002.CLW')
ClipboardDemo          PROCEDURE   !Demo Clipboard Function
     END
     MODULE('SCT_DEMO003.CLW')
About                  PROCEDURE   !
     END
         INCLUDE('SCTOOLS.INC','SCToolsLibrary')
   END

SilentRunning        BYTE(0)                               ! Set true when application is running in 'silent mode'

!region File Declaration
!endregion


FuzzyMatcher         FuzzyClass                            ! Global fuzzy matcher
GlobalErrorStatus    ErrorStatusClass,THREAD
GlobalErrors         ErrorClass                            ! Global error manager
INIMgr               INIClass                              ! Global non-volatile storage manager
GlobalRequest        BYTE(0),THREAD                        ! Set when a browse calls a form, to let it know action to perform
GlobalResponse       BYTE(0),THREAD                        ! Set to the response from the form
VCRRequest           LONG(0),THREAD                        ! Set to the request from the VCR buttons

Dictionary           CLASS,THREAD
Construct              PROCEDURE
Destruct               PROCEDURE
                     END


  CODE
  GlobalErrors.Init(GlobalErrorStatus)
  FuzzyMatcher.Init                                        ! Initilaize the browse 'fuzzy matcher'
  FuzzyMatcher.SetOption(MatchOption:NoCase, 1)            ! Configure case matching
  FuzzyMatcher.SetOption(MatchOption:WordOnly, 0)          ! Configure 'word only' matching
  INIMgr.Init('.\sct_demo.INI', NVD_INI)                   ! Configure INIManager to use INI file
  DctInit
  SYSTEM{PROP:Icon} = 'sctools.ico'
  Main
  INIMgr.Update
  INIMgr.Kill                                              ! Destroy INI manager
  FuzzyMatcher.Kill                                        ! Destroy fuzzy matcher


Dictionary.Construct PROCEDURE

  CODE
  IF THREAD()<>1
     DctInit()
  END


Dictionary.Destruct PROCEDURE

  CODE
  DctKill()

