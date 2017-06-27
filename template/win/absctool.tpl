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
 #TAB('Devuna Screen Capture Tools Templates')
  #INSERT  (%SysHead)
  #BOXED   ('About Devuna Screen Capture Tools Templates'),AT(5)
    #DISPLAY (''),AT(15)
    #DISPLAY ('This template 1s free software:                                       '),AT(15)
    #DISPLAY ('You can redistribute it and/or modify it under the terms of the GNU   '),AT(15)
    #DISPLAY ('General Public License as published by the Free Software Foundation,  '),AT(15)
    #DISPLAY ('either version 3 of the License,or (at your option) any later version.'),AT(15)
    #DISPLAY (''),AT(15)
    #DISPLAY ('This template is distributed in the hope that they will be useful     '),AT(15)
    #DISPLAY ('but WITHOUT ANY WARRANTY; without even the implied warranty           '),AT(15)
    #DISPLAY ('of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.'),AT(15)
    #DISPLAY (''),AT(15)
    #DISPLAY ('See the GNU General Public License for more details.'),AT(15)
    #DISPLAY ('http://www.gnu.org/licenses/'),AT(15)
    #DISPLAY ('Copyright 2017 Devuna'),AT(15)
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
