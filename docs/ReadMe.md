# Getting Started #

----------

The DEVUNA repositories contain source code written in and for [Clarion for Windows®](http://www.SoftVelocity.com)

Our repositories utilize the same folder structure as Clarion for Windows®.  Here is a list or the repository folders and their typical location in Clarion for Windows® version 10:

documents - CSIDL\_COMMON_DOCUMENTS/Softvelocity/Clarion10/Accessory/Devuna/documents/[project name] (e.g. CoolTips)

examples - CSIDL\_COMMON_DOCUMENTS/SoftVelocity/Clarion10/Accessory/Devuna/examples/[project name]

images - SoftVelocity/Clarion10/Accessory/images

libsrc/win - SoftVelocity/Clarion10/Accessory/libsrc/win

template/win - SoftVelocity/Clarion10/Accessory/template/win

# Documentation Contents #

--------

Documentation for the  can be found in the Help folder of the repository.  The Help folder contains everything needed to build an HTML_Help file for the Screen Capture Tools library.

The Screen Capture Tools library (**sctools.dll**) requires a couple of supporting libraries.

**dibapi.dll**&nbsp;&nbsp;This library is based on the original dibapi library that is part of the WinCap project written in 1999 by Microsoft® Product Support Services, Developer Support. The **dibapi** folder contains the source our modified version of the library as well as a Visual Studio 2013 solution to create the library.

Unfortunately the WinCap.zip file is no longer available from Microsoft®.  Our repository has a folder, named **WinCap**, that contains the original files from the WinCap.zip archive.  You can also find WinCap.zip at [**The Programmer's Corner**](https://www.pcorner.com/list/C/WINCAP31.ZIP/INFO/).

**jpgapi.dll**&nbsp;&nbsp;This library is a wrapper for the Intel® JPEG Library **ijl15.dll**. The Intel® JPEG Library provides a set of highly optimized C functions that implement JPEG compression and decompression on Intel architecture processors. Our repository has a folder, named **jpgapi**, that contains the source files for the wrapper library as well as a Visual Studio 2013 solution to create the library.

**ijl15.dll**&nbsp;&nbsp;Unfortunately the ijl15.zip file is no longer available from Intel®.  Intel® no longer supports this old library and strongly recommends users to check the Intel IPP that will bring more benefits for functionalities and performance. Our repository has a folder, named <b>ijl15</b>, that contains the original installer for the Intel JPEG library (**ijl15.exe**).







