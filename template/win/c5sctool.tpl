#! ================================================================================================
#!                             DEVUNA - Screen Capture Tools Templates
#! ================================================================================================
#! Author:  Randy Rogers (KCR) <rrogers@devuna.com>
#! Notice:  Copyright (C) 2017, Devuna
#!          Distributed under the MIT License (https://opensource.org/licenses/MIT)
#! ================================================================================================
#!    This file is part of Devuna-ScreenCaptureTools (https://github.com/Devuna/Devuna-ScreenCaptureTools)
#!
#!    Devuna-ScreenCaptureTools is free software: you can redistribute it and/or modify
#!    it under the terms of the MIT License as published by
#!    the Open Source Initiative.
#!
#!    Devuna-ScreenCaptureTools is distributed in the hope that it will be useful,
#!    but WITHOUT ANY WARRANTY; without even the implied warranty of
#!    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#!    MIT License for more details.
#!
#!    You should have received a copy of the MIT License
#!    along with Devuna-ScreenCaptureTools.  If not, see <https://opensource.org/licenses/MIT>.
#! ================================================================================================
#!
#!===============================================================================================
#!
#! Copyright 2000-2017 Devuna
#!
#! ALL RIGHTS RESERVED
#!
#!===============================================================================================
#TEMPLATE (C5SCTool, 'Screen Capture Tools Legacy Templates')
#HELP('SCTOOLS.HLP')
#!
#INCLUDE ('C5SCXTNS.TPW')
#INCLUDE ('C5SCCODE.TPW')
#INCLUDE ('C5SCCTRL.TPW')

#SYSTEM
 #TAB('Devuna Screen Capture Tools Templates')
  #INSERT  (%SysHead)
  #BOXED   ('About Devuna Screen Capture Tools Templates'),AT(5)
    #DISPLAY (''),AT(15)
    #DISPLAY ('This template 1s free software:                                       '),AT(15)
    #DISPLAY ('You can redistribute it and/or modify it under the terms of the GNU   '),AT(15)
    #DISPLAY ('General Public License as published by the Free Software Foundation,  '),AT(15)
    #DISPLAY (''),AT(15)
    #DISPLAY ('This template is distributed in the hope that they will be useful     '),AT(15)
    #DISPLAY ('but WITHOUT ANY WARRANTY; without even the implied warranty           '),AT(15)
    #DISPLAY ('of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.'),AT(15)
    #DISPLAY (''),AT(15)
    #DISPLAY ('See the MIT License for more details.'),AT(15)
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
  #DISPLAY ('C5SCTOOL.TPL'),AT(40,4)
  #DISPLAY ('Screen Capture Tools Clarion Templates'),AT(40,14)
  #DISPLAY ('for Clarion Legacy Template Applications'),AT(40,24)
  #DISPLAY ('')
#!
#!===============================================================================================
#GROUP(%EmbedStart)
#?!-----------------------------------------------------------------------------------------------------------
#?! C5SCTOOL.TPL   (C)2000-2017 Devuna
#?! Template: (%TplName - %TplDescription)
#IF (%EmbedID)
#?! Embed:    (%EmbedID) (%EmbedDescription) (%EmbedParameters)
#ENDIF
#?!-----------------------------------------------------------------------------------------------------------
#!
#!===============================================================================================
#GROUP(%EmbedEnd)
#?!-----------------------------------------------------------------------------------------------------------
