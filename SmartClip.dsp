# Microsoft Developer Studio Project File - Name="SmartClip" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SmartClip - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SmartClip.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SmartClip.mak" CFG="SmartClip - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SmartClip - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SmartClip - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SmartClip - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "SmartClip - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "SmartClip - Win32 Release"
# Name "SmartClip - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Data Class"

# PROP Default_Filter "cpp;c;cxx"
# Begin Source File

SOURCE=.\ClipboardCFBitmapEntry.cpp
# End Source File
# Begin Source File

SOURCE=.\ClipboardCFTextEntry.cpp
# End Source File
# Begin Source File

SOURCE=.\ClipboardEntry.cpp
# End Source File
# Begin Source File

SOURCE=.\ClipboardEntryArray.cpp
# End Source File
# Begin Source File

SOURCE=.\ClipboardList.cpp
# End Source File
# Begin Source File

SOURCE=.\ClipboardMgr.cpp
# End Source File
# End Group
# Begin Group "Settings Class"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MainPage.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingsSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\SharingPage.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\SmartClip.cpp
# End Source File
# Begin Source File

SOURCE=.\SmartClip.rc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SystemTray.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Data Headers"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=.\ClipboardCFBitmapEntry.h
# End Source File
# Begin Source File

SOURCE=.\ClipboardCFTextEntry.h
# End Source File
# Begin Source File

SOURCE=.\ClipboardEntry.h
# End Source File
# Begin Source File

SOURCE=.\ClipboardEntryArray.h
# End Source File
# Begin Source File

SOURCE=.\ClipboardList.h
# End Source File
# Begin Source File

SOURCE=.\ClipboardMgr.h
# End Source File
# End Group
# Begin Group "Settings Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MainPage.h
# End Source File
# Begin Source File

SOURCE=.\SettingsSheet.h
# End Source File
# Begin Source File

SOURCE=.\SharingPage.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Defines.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SmartClip.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SystemTray.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\ico129.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico131.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico158.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico161.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico165.ico
# End Source File
# Begin Source File

SOURCE=.\res\SmartClip.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "SmartClip - Win32 Release"

!ELSEIF  "$(CFG)" == "SmartClip - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TestData.txt

!IF  "$(CFG)" == "SmartClip - Win32 Release"

!ELSEIF  "$(CFG)" == "SmartClip - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Target
# End Project
