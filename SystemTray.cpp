// This is a modified version of the file originally written by
// Chris Maunder (cmaunder@mail.com)
// http://cvs.sourceforge.net/viewcvs.py/filezilla/FileZilla/source/misc/SystemTray.cpp?rev=1.6
//
/////////////////////////////////////////////////////////////////////////////
// SystemTray.cpp : implementation file
/////////////////////////////////////////////////////////////////////////////
    
#include "stdafx.h"
#include "SystemTray.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSystemTray construction/creation/destruction

CSystemTray::CSystemTray()
{
    Initialise();
}

void CSystemTray::Initialise()
{
    memset(&m_tnd, 0, sizeof(m_tnd));

    m_bEnabled				= FALSE;
    m_DefaultMenuItemID		= 0;
    m_DefaultMenuItemByPos	= TRUE;
}

BOOL CSystemTray::Create(CWnd* pParent, UINT uCallbackMessage, LPCTSTR szToolTip, 
                         HICON icon, UINT uID)
{
    // this is only for Windows 95 (or higher)
    VERIFY(m_bEnabled = ( GetVersion() & 0xff ) >= 4);
    if (!m_bEnabled) return FALSE;

    // Make sure we avoid conflict with other messages
    ASSERT(uCallbackMessage >= WM_USER);

    // Tray only supports tooltip text up to 64 characters
    ASSERT(_tcslen(szToolTip) <= 64);

    // load up the NOTIFYICONDATA structure
    m_tnd.cbSize = sizeof(NOTIFYICONDATA);
    m_tnd.hWnd   = pParent->GetSafeHwnd();
    m_tnd.uID    = uID;
    m_tnd.hIcon  = icon;
    m_tnd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    m_tnd.uCallbackMessage = uCallbackMessage;
    _tcscpy(m_tnd.szTip, szToolTip);

    // Set the tray icon
    VERIFY(m_bEnabled = Shell_NotifyIcon(NIM_ADD, &m_tnd));
    return m_bEnabled;
}

CSystemTray::~CSystemTray()
{
    RemoveIcon();
}

/////////////////////////////////////////////////////////////////////////////
// CSystemTray icon manipulation

void CSystemTray::RemoveIcon()
{
    if (!m_bEnabled) return;

    m_tnd.uFlags = 0;
    Shell_NotifyIcon(NIM_DELETE, &m_tnd);
    m_bEnabled = FALSE;
}

void CSystemTray::ShowIcon()
{
    m_tnd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    Shell_NotifyIcon(NIM_ADD, &m_tnd);
}

BOOL CSystemTray::SetIcon(UINT nIDResource)
{
    HICON hIcon = AfxGetApp()->LoadIcon(nIDResource);
    if (!m_bEnabled) return FALSE;

    m_tnd.uFlags = NIF_ICON;
    m_tnd.hIcon = hIcon;

    return Shell_NotifyIcon(NIM_MODIFY, &m_tnd);
}

/////////////////////////////////////////////////////////////////////////////
// CSystemTray tooltip text manipulation

BOOL CSystemTray::SetTooltipText(LPCTSTR pszTip)
{
    if (!m_bEnabled) return FALSE;

    m_tnd.uFlags = NIF_TIP;
    _tcscpy(m_tnd.szTip, pszTip);

    return Shell_NotifyIcon(NIM_MODIFY, &m_tnd);
}

BOOL CSystemTray::SetTooltipText(UINT nID)
{
    CString strText;
    VERIFY(strText.LoadString(nID));

    return SetTooltipText(strText);
}

CString CSystemTray::GetTooltipText() const
{
    CString strText;
    if (m_bEnabled)
        strText = m_tnd.szTip;

    return strText;
}

/////////////////////////////////////////////////////////////////////////////
// CSystemTray message handlers

LRESULT CSystemTray::OnTrayNotification(UINT wParam, LONG lParam) 
{
    //Return quickly if its not for this tray icon
    if (wParam != m_tnd.uID)
        return 0L;

    CMenu menu, *pSubMenu;
    CWnd* pTarget = AfxGetMainWnd();

    // Clicking with right button brings up a context menu
    if (LOWORD(lParam) == WM_RBUTTONUP || LOWORD(lParam) == WM_LBUTTONUP )
    {    
        if (!menu.LoadMenu(m_tnd.uID)) 
			return 0;

		pSubMenu = menu.GetSubMenu(0);
        if (!pSubMenu) 
			return 0;

        // Make chosen menu item the default (bold font)
        // ::SetMenuDefaultItem(pSubMenu->m_hMenu, m_DefaultMenuItemID, m_DefaultMenuItemByPos);

        // Display and track the popup menu
        CPoint pos;
        GetCursorPos(&pos);

        pTarget->SetForegroundWindow();  
        ::TrackPopupMenu(pSubMenu->m_hMenu, 0, pos.x, pos.y, 0, 
                         pTarget->GetSafeHwnd(), NULL);

        // BUGFIX: See "PRB: Menus for Notification Icons Don't Work Correctly"
        pTarget->PostMessage(WM_NULL, 0, 0);

        menu.DestroyMenu();
    } 

    return 1;
}
