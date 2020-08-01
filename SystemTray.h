// This is a modified version of the file originally written by
// Chris Maunder (cmaunder@mail.com)
// http://cvs.sourceforge.net/viewcvs.py/filezilla/FileZilla/source/misc/SystemTray.cpp?rev=1.6
//

/////////////////////////////////////////////////////////////////////////////
// SystemTray.h : header file
//

#ifndef _INCLUDED_SYSTEMTRAY_H_
#define _INCLUDED_SYSTEMTRAY_H_

/////////////////////////////////////////////////////////////////////////////
// CSystemTray window

class CSystemTray
{
// Construction/destruction
public:
    CSystemTray();
    virtual ~CSystemTray();

// Operations
public:
    BOOL Enabled() { return m_bEnabled; }

    // Create the tray icon
    BOOL Create(CWnd* pParent, UINT uCallbackMessage, LPCTSTR szTip, HICON icon, UINT uID);

    // Change or retrieve the Tooltip text
    BOOL    SetTooltipText(LPCTSTR pszTooltipText);
    BOOL    SetTooltipText(UINT nID);
    CString GetTooltipText() const;

    // Change or retrieve the icon displayed
    BOOL  SetIcon(UINT nIDResource);
    void  ShowIcon();
    void  RemoveIcon();

    // Default handler for tray notification message
    virtual LRESULT OnTrayNotification(WPARAM uID, LPARAM lEvent);

// Overrides

// Implementation
protected:
    void Initialise();

    BOOL            m_bEnabled;   // does O/S support tray icon?
    NOTIFYICONDATA  m_tnd;
    int				m_nCurrentIcon;
    UINT			m_DefaultMenuItemID;
    BOOL			m_DefaultMenuItemByPos;

protected:
};
#endif

/////////////////////////////////////////////////////////////////////////////
