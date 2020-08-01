// COPYRIGHT (C) George Chiramattel, [http://www.chiramattel.com/george]
//
// This code is free software; you can redistribute it and / or
// modify it provided that the following conditions are met:
//
// 1. Redistributions must reproduce the above copyright notice, this list of 
// conditions and the following disclaimer in the documentation and / or other 
// materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED ''AS IS'' AND ANY EXPRESSED OR IMPLIED WARRANTIES,
// INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY 
// AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
// GEORGE CHIRAMATTEL BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
// OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY 
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// For bug reports or feature requets please contact.
// George Chiramattel [feedback@chiramattel.com]
//
// Defines.h : include file for standard Defanitions
//  

#if !defined(AFX_DEFINES_H__1AB41C3F_51BE_4BD8_85BD_9EF4DB6CCC7C__INCLUDED_)
#define AFX_DEFINES_H__1AB41C3F_51BE_4BD8_85BD_9EF4DB6CCC7C__INCLUDED_

enum CBOARD_TYPE
{
	CB_CF_EMPTY		= 0,
	CB_CF_TEXT		= CF_TEXT,
	CB_CF_BITMAP	= CF_BITMAP
};

#define WM_ICON_NOTIFY		WM_USER+10

#define CF_WINDOW_WIDTH		256
#define CF_WINDOW_HEIGHT	180
#define CF_WINDOW_GUTTER	5
#define CF_HOTKEY_MODIFIERS	MOD_ALT|MOD_CONTROL

#define ID_HOTKEY_ACTIVATE	0x100
#define ID_HOTKEY_DELETE	0x101
#define ID_HOTKEY_NEXT		0x102
#define ID_HOTKEY_PREVIOUS	0x103

#define ID_TIMER			0x100
#define VISIBLE_TIMER		3


static UINT CBPriorityList[]	= { 
	CF_TEXT, 
	CF_BITMAP 
};

#endif // !defined(AFX_DEFINES_H__1AB41C3F_51BE_4BD8_85BD_9EF4DB6CCC7C__INCLUDED_)
