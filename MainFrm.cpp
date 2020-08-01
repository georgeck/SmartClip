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
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "SmartClip.h"

#include "ClipboardMgr.h"

#include "SystemTray.h"
#include "MainFrm.h"
#include "SettingsSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_CHANGECBCHAIN()
	ON_WM_DESTROY()
	ON_WM_DRAWCLIPBOARD()
	ON_WM_PAINT()
	ON_COMMAND(ID_EMPTY_CLIPBOARD, OnEmptyClipboard)
	ON_COMMAND(ID_SETTINGS, OnSettings)
	ON_WM_TIMER()
	ON_MESSAGE(WM_ICON_NOTIFY, OnTrayNotification)
	ON_MESSAGE(WM_HOTKEY, OnGlobalHotkey)
	ON_COMMAND(ID_DISSABLE_SMARTCLIP, OnDissableSmartclip)
	ON_UPDATE_COMMAND_UI(ID_DISSABLE_SMARTCLIP, OnUpdateDissableSmartclip)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_hWndNextViewer  = NULL;

	m_uHotkeyActivate = 0;
	m_uHotkeyDelete	  = 0;
	m_uHotkeyNext	  = 0;
	m_uHotkeyPrevious = 0;

	m_nTimerCount	  = 0;
	m_bEnabled		  = TRUE;
}

CMainFrame::~CMainFrame()
{

}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	Init();
	
	DisplayWindow(FALSE);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	if(cs.hMenu)
		DestroyMenu(cs.hMenu);
	cs.hMenu	 = NULL;

	cs.style	 = WS_POPUP | WS_VISIBLE | WS_CLIPSIBLINGS | WS_OVERLAPPED;
	cs.dwExStyle = WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_TOOLWINDOW | WS_EX_TOPMOST;


	cs.x		 = GetSystemMetrics(SM_CXMAXIMIZED) - (CF_WINDOW_WIDTH +  30);
	cs.y		 = GetSystemMetrics(SM_CYMAXIMIZED) - (CF_WINDOW_HEIGHT + 30);
	cs.cx		 = CF_WINDOW_WIDTH;
	cs.cy		 = CF_WINDOW_HEIGHT;

	cs.lpszClass = AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW,
      ::LoadCursor(NULL, IDC_ARROW),
      (HBRUSH) ::GetStockObject(HOLLOW_BRUSH),
      NULL);
	return TRUE;
}	

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	// if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
	//	  return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


LRESULT CMainFrame::OnTrayNotification(WPARAM wParam, LPARAM lParam)
{
	return m_TrayIcon.OnTrayNotification(wParam, lParam);
}

LRESULT CMainFrame::OnGlobalHotkey(WPARAM wParam, LPARAM lParam)
{
	lParam;					// Unused
	switch(wParam)
	{
	case ID_HOTKEY_ACTIVATE:
   		OnHotkeyActivate();
		break;

	case ID_HOTKEY_DELETE:
		OnHotkeyDelete();
		break;

	case ID_HOTKEY_NEXT:
		OnHotkeyNext();
		break;

	case ID_HOTKEY_PREVIOUS:
		OnHotkeyPrevious();
		break;

	default:
		ASSERT(FALSE);
	}

	return TRUE;;
}

void CMainFrame::OnChangeCbChain(HWND hWndRemove, HWND hWndAfter) 
{
	CFrameWnd::OnChangeCbChain(hWndRemove, hWndAfter);
	
    if ((HWND) hWndRemove == m_hWndNextViewer) 
        m_hWndNextViewer = (HWND)hWndAfter; 
	
    // Otherwise, pass the message to the next link. 
	else if (m_hWndNextViewer != NULL) 
        ::SendMessage(m_hWndNextViewer, WM_CHANGECBCHAIN, (WPARAM)hWndRemove, (LPARAM)hWndAfter); 	
}

void CMainFrame::OnDestroy() 
{
	CFrameWnd::OnDestroy();
	ChangeClipboardChain(m_hWndNextViewer); 
}

void CMainFrame::OnDrawClipboard() 
{
	CFrameWnd::OnDrawClipboard();

	if(m_bEnabled)
	{
		HWND hOwner = ::GetClipboardOwner();
		if(hOwner != m_hWnd)
		{
			// Capture the data!!
			m_ClipboardMgr.GetClipboardEntries();	
		}
		// Pass the message to the Next Viewer
		::SendMessage(m_hWndNextViewer, WM_DRAWCLIPBOARD, NULL, NULL); 	
	}
	Invalidate();
}

void CMainFrame::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rectWindow;
	GetClientRect(&rectWindow);

	// Draw the shadow
	CRect rectShadow = rectWindow;
	rectShadow.DeflateRect(8, 8, 0, 0);
	dc.FillRect(&rectShadow, &m_BrushShadow);

	// Draw the Screen
	CRect rectScreen = rectWindow;
	rectScreen.DeflateRect(1, 1, 8, 8);
	dc.Draw3dRect(rectScreen.left, 
		rectScreen.top,
		rectScreen.right + 1,
		rectScreen.bottom + 1,
		0, 0);
	rectScreen.OffsetRect(1, 1);
	dc.FillRect(&rectScreen, &m_BrushToolTip);

	m_ClipboardMgr.DrawClipboad(dc, rectScreen);
}

BOOL CMainFrame::Init()
{
	// Create the Tray Icon.
	m_TrayIcon.Create(this, 
		WM_ICON_NOTIFY, 
		"Click here to configure SmartClip", 
		AfxGetApp()->LoadIcon(IDR_TRAY_ICON), 
		IDR_TRAY_MENU);
	
	// Enter the Clipboard Viewer Chain
	m_hWndNextViewer = SetClipboardViewer();

	// Create the Brushes
	m_BrushToolTip.CreateSolidBrush(GetSysColor(COLOR_INFOBK));
	m_BrushShadow.CreateSolidBrush( GetSysColor(COLOR_GRAYTEXT));

	// Load Default Settings
	LoadSettings();

	// Register Default Hotkeys
	BOOL bSuccess = TRUE;
	bSuccess &= RegisterHotKey(m_hWnd, ID_HOTKEY_ACTIVATE, m_uHotkeyModifierActivate, m_uHotkeyActivate);
	bSuccess &= RegisterHotKey(m_hWnd, ID_HOTKEY_DELETE	,  m_uHotkeyModifierDelete  , m_uHotkeyDelete);
	bSuccess &= RegisterHotKey(m_hWnd, ID_HOTKEY_NEXT    , m_uHotkeyModifierNext	, m_uHotkeyNext);
	bSuccess &= RegisterHotKey(m_hWnd, ID_HOTKEY_PREVIOUS, m_uHotkeyModifierPrevious, m_uHotkeyPrevious);

	if(bSuccess == FALSE)
	{
		::MessageBox(::GetDesktopWindow(), "Failes to set one or more HotKeys\nPlease change the HotKey settings", "SmartClip", MB_OK);
	}
	return TRUE;
}

void CMainFrame::LoadSettings()
{
	CWinApp* pApp = AfxGetApp();
	if(pApp)
	{
		m_ClipboardMgr.SetMaxEntries(pApp->GetProfileInt("Settings", "MaxEntries", 7) );

		m_uHotkeyActivate		  = pApp->GetProfileInt("Settings", "Activate",			67);
		m_uHotkeyModifierActivate = pApp->GetProfileInt("Settings", "ActivateModifier", 3);

		m_uHotkeyDelete			  = pApp->GetProfileInt("Settings", "Delete",			38);
		m_uHotkeyModifierDelete	  = pApp->GetProfileInt("Settings", "DeleteModifier",	3);

		m_uHotkeyNext			  = pApp->GetProfileInt("Settings", "Next",				39);
		m_uHotkeyModifierNext	  = pApp->GetProfileInt("Settings", "NextModifier",		3);

		m_uHotkeyPrevious		  = pApp->GetProfileInt("Settings", "Previous",			37);
		m_uHotkeyModifierPrevious = pApp->GetProfileInt("Settings", "PreviousModifier", 3);
	}
}

void CMainFrame::SaveSettings()
{
	CWinApp* pApp = AfxGetApp();
	if(pApp)
	{
		pApp->WriteProfileInt("Settings", "MaxEntries", m_ClipboardMgr.GetMaxEntries() );

		pApp->WriteProfileInt("Settings", "Activate",			m_uHotkeyActivate);
		pApp->WriteProfileInt("Settings", "ActivateModifier",	m_uHotkeyModifierActivate);

		pApp->WriteProfileInt("Settings", "Delete",				m_uHotkeyDelete);
		pApp->WriteProfileInt("Settings", "DeleteModifier",		m_uHotkeyModifierDelete);

		pApp->WriteProfileInt("Settings", "Next",				m_uHotkeyNext);
		pApp->WriteProfileInt("Settings", "NextModifier",		m_uHotkeyModifierNext);

		pApp->WriteProfileInt("Settings", "Previous",			m_uHotkeyPrevious);
		pApp->WriteProfileInt("Settings", "PreviousModifier",	m_uHotkeyModifierPrevious);
	}

}

void CMainFrame::OnEmptyClipboard() 
{
	// TODO: Add your command handler code here
	m_ClipboardMgr.EmptyCBClipBoard();
}

void CMainFrame::OnSettings() 
{
	CSettingsSheet SettingsDlg;

	SettingsDlg.m_MainPage.m_bDissable					= !m_bEnabled;
	SettingsDlg.m_MainPage.m_nMaxEntries			    = m_ClipboardMgr.GetMaxEntries();

	SettingsDlg.m_MainPage.m_dwHotkeyActivate			= m_uHotkeyActivate;
	SettingsDlg.m_MainPage.m_dwHotkeyModifierActivate   = m_uHotkeyModifierActivate;

	SettingsDlg.m_MainPage.m_dwHotkeyDelete			    = m_uHotkeyDelete;
	SettingsDlg.m_MainPage.m_dwHotkeyModifierDelete	    = m_uHotkeyModifierDelete;

	SettingsDlg.m_MainPage.m_dwHotkeyNext				= m_uHotkeyNext;
	SettingsDlg.m_MainPage.m_dwHotkeyModifierNext		= m_uHotkeyModifierNext;

	SettingsDlg.m_MainPage.m_dwHotkeyPrevious			= m_uHotkeyPrevious;
	SettingsDlg.m_MainPage.m_dwHotkeyModifierPrevious	= m_uHotkeyModifierPrevious;

	if(SettingsDlg.DoModal() == IDOK)
	{
		m_bEnabled					= !(SettingsDlg.m_MainPage.m_bDissable);
		m_ClipboardMgr.SetMaxEntries(SettingsDlg.m_MainPage.m_nMaxEntries);

		m_uHotkeyActivate			= SettingsDlg.m_MainPage.m_dwHotkeyActivate;
		m_uHotkeyModifierActivate	= SettingsDlg.m_MainPage.m_dwHotkeyModifierActivate;

		m_uHotkeyDelete				= SettingsDlg.m_MainPage.m_dwHotkeyDelete;
		m_uHotkeyModifierDelete		= SettingsDlg.m_MainPage.m_dwHotkeyModifierDelete;

		m_uHotkeyNext				= SettingsDlg.m_MainPage.m_dwHotkeyNext;
		m_uHotkeyModifierNext		= SettingsDlg.m_MainPage.m_dwHotkeyModifierNext;

		m_uHotkeyPrevious			= SettingsDlg.m_MainPage.m_dwHotkeyPrevious;
		m_uHotkeyModifierPrevious	= SettingsDlg.m_MainPage.m_dwHotkeyModifierPrevious;

		SaveSettings();
	}

	UpdateDissableIcon();
}


BOOL CMainFrame::OnHotkeyActivate()
{
	DisplayWindow(TRUE);
	return TRUE;
}

BOOL CMainFrame::OnHotkeyDelete()
{
//	MessageBox("OnHotkeyDelete");
	return TRUE;

}

BOOL CMainFrame::OnHotkeyNext()
{
	BOOL bBool = m_ClipboardMgr.PutNextEntryToCB();
	Invalidate();
	DisplayWindow(TRUE);

	return bBool;
}

BOOL CMainFrame::OnHotkeyPrevious()
{
	BOOL bBool = m_ClipboardMgr.PutPrevEntryToCB();
	Invalidate();
	DisplayWindow(TRUE);

	return bBool;
}

BOOL CMainFrame::DisplayWindow(BOOL bShow)
{
	if(bShow)
	{
		if(!IsCBWindowVisible())
		{
			// Move the window to visible region
			CRect VisibleRect;
			VisibleRect.left   = GetSystemMetrics(SM_CXMAXIMIZED) - (CF_WINDOW_WIDTH +  30);
			VisibleRect.top	   = GetSystemMetrics(SM_CYMAXIMIZED) - (CF_WINDOW_HEIGHT + 30);
			VisibleRect.right  = VisibleRect.left + CF_WINDOW_WIDTH;
			VisibleRect.bottom = VisibleRect.top  + CF_WINDOW_HEIGHT;
			
			MoveWindow(&VisibleRect);

			// Start the timer
			SetTimer(ID_TIMER, 1000, NULL);
		}

		// reset the timer count
		m_nTimerCount = 0;

	}
	else		// Hide the Window
	{
			// Move the window to visible region
			CRect HiddenRect;
			HiddenRect.left   = GetSystemMetrics(SM_CXMAXIMIZED) * 4;
			HiddenRect.top	  = GetSystemMetrics(SM_CYMAXIMIZED) * 4;
			HiddenRect.right  = HiddenRect.left + CF_WINDOW_WIDTH;
			HiddenRect.bottom = HiddenRect.top  + CF_WINDOW_HEIGHT;
			
			MoveWindow(&HiddenRect);

			// Kill the timer
			KillTimer(ID_TIMER);
	
	}
	return TRUE;
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	m_nTimerCount++;

	if(m_nTimerCount >= VISIBLE_TIMER)
	{
		// Kill the timer
		KillTimer(ID_TIMER);

		// Hide the Window
		DisplayWindow(FALSE);
	}
	CFrameWnd::OnTimer(nIDEvent);
}

BOOL CMainFrame::IsCBWindowVisible()
{
	CRect RectDeskTopWindow;
	GetDesktopWindow()->GetWindowRect(&RectDeskTopWindow);

	CRect RectCBWindow;
	GetWindowRect(&RectCBWindow);

	RectDeskTopWindow.IntersectRect(&RectDeskTopWindow, &RectCBWindow);
	return !(RectDeskTopWindow.IsRectEmpty());
}

void CMainFrame::OnDissableSmartclip() 
{
	m_bEnabled = !m_bEnabled;		
	UpdateDissableIcon();
}

void CMainFrame::OnUpdateDissableSmartclip(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(!m_bEnabled);	
}

void CMainFrame::UpdateDissableIcon()
{
	if(m_bEnabled)
	{
		m_TrayIcon.SetIcon(IDR_TRAY_ICON);
	}
	else
	{
		m_TrayIcon.SetIcon(IDR_DISSABLED_TRAY_ICON);
	}
}
