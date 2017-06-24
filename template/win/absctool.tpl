#! ================================================================================================
#!                             DEVUNA - Screen Capture Tools Templates
#! ================================================================================================
#! Author:  Randy Rogers (KCR) <rrogers@devuna.com>
#! Notice:  Copyright (C) 2017, Devuna
#!          Distributed under LGPLv3 (http://www.gnu.org/licenses/lgpl.html)
#! ================================================================================================
#!    This file is part of Devuna-ScreenCaptureTools (https://github.com/Devuna/Devuna-ScreenCaptureTools)
#!
#!    Devuna-ScreenCaptureTools is free software: you can redistribute it and/or modify
#!    it under the terms of the GNU General Public License as published by
#!    the Free Software Foundation, either version 3 of the License, or
#!    (at your option) any later version.
#!
#!    Devuna-ScreenCaptureTools is distributed in the hope that it will be useful,
#!    but WITHOUT ANY WARRANTY; without even the implied warranty of
#!    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#!    GNU General Public License for more details.
#!
#!    You should have received a copy of the GNU General Public License
#!    along with Devuna-ScreenCaptureTools.  If not, see <http://www.gnu.org/licenses/>.
#! ================================================================================================
#!
#!===============================================================================================
#!
#! Copyright 2000-2017 Devuna
#!
#! ALL RIGHTS RESERVED
#!
#!===============================================================================================
#TEMPLATE (ABCSCTool, 'Screen Capture Tools ABC Templates'),FAMILY('ABC')
#HELP('SCTOOLS.HLP')
#!
#INCLUDE ('ABSCXTNS.TPW')
#INCLUDE ('ABSCCODE.TPW')
#INCLUDE ('ABSCCTRL.TPW')

#SYSTEM
 #TAB('Screen Capture Tools Templates')
  #INSERT  (%SysHead)
  #BOXED   ('About Screen Capture Tools Templates'),AT(5)
    #DISPLAY (''),AT(15)
    #DISPLAY ('Warning: These templates are protected by copyright   '),AT(15)
    #DISPLAY ('law and international treaties.   Unauthorized use,   '),AT(15)
    #DISPLAY ('reproduction or distribution of these templates, or   '),AT(15)
    #DISPLAY ('any part of  them, without the expressed written      '),AT(15)
    #DISPLAY ('consent of Devuna Inc., may      '),AT(15)
    #DISPLAY ('result in severe civil and criminal penalties, and    '),AT(15)
    #DISPLAY ('will be prosecuted to the maximum extent possible     '),AT(15)
    #DISPLAY ('under law.'),AT(15)
    #DISPLAY (''),AT(15)
    #DISPLAY ('For more information, contact the author at:'),AT(15)
    #DISPLAY ('rrogers@devuna.com'),AT(15)
    #DISPLAY ('(C)2000-2017 Devuna'),AT(15)
  #ENDBOXED
 #ENDTAB

#!===============================================================================================
#GROUP (%MakeHeadHiddenPrompts)
  #PROMPT('',@S50),%TplName
  #PROMPT('',@S100),%TplDescription
#!===============================================================================================
#GROUP   (%MakeHead,%xTplName,%xTplDescription)
  #SET (%TplName,%xTplName)
  #SET (%TplDescription,%xTplDescription)
#!
#!===============================================================================================
#GROUP   (%Head)
  #IMAGE   ('SCTOOLS.ICO'), AT(,,175,26)
  #DISPLAY (%TplName),AT(40,3)
  #DISPLAY ('(C)2000-2017 Devuna'),AT(40,12)
  #DISPLAY ('')
#!
#!===============================================================================================
#GROUP   (%SysHead)
  #IMAGE   ('SCTOOLS.ICO'), AT(,4,175,26)
  #DISPLAY ('ABSCTOOL.TPL'),AT(40,4)
  #DISPLAY ('Screen Capture Tools ABC Templates'),AT(40,14)
  #DISPLAY ('for Clarion ABC Template Applications'),AT(40,24)
  #DISPLAY ('')
#!
#!===============================================================================================
#GROUP(%EmbedStart)
#?!-----------------------------------------------------------------------------------------------------------
#?! ABSCTOOL.TPL   (C)2000-2017 Devuna
#?! Template: (%TplName - %TplDescription)
#IF (%EmbedID)
#?! Embed:    (%EmbedID) (%EmbedDescription) (%EmbedParameters)
#ENDIF
#?!-----------------------------------------------------------------------------------------------------------
#!
#!===============================================================================================
#GROUP(%EmbedEnd)
#?!-----------------------------------------------------------------------------------------------------------
