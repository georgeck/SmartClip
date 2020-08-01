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
// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__4F0BC3A0_FCA2_418F_B04C_FC4FD850FDB8__INCLUDED_)
#define AFX_MAINFRM_H__4F0BC3A0_FCA2_418F_B04C_FC4FD850FDB8__INCLUDED_

#include "SystemTray.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnChangeCbChain(HWND hWndRemove, HWND hWndAfter);
	afx_msg void OnDestroy();
	afx_msg void OnDrawClipboard();
	afx_msg void OnPaint();
	afx_msg void OnEmptyClipboard();
	afx_msg void OnSettings();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDissableSmartclip();
	afx_msg void OnUpdateDissableSmartclip(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void UpdateDissableIcon();
	BOOL m_bEnabled;
	BOOL IsCBWindowVisible();
	BOOL DisplayWindow(BOOL bShow);
	BOOL OnHotkeyPrevious();
	BOOL OnHotkeyNext();
	BOOL OnHotkeyDelete();
	BOOL OnHotkeyActivate();
	void SaveSettings();
	void LoadSettings();
	BOOL Init();

	LRESULT OnTrayNotification(WPARAM wParam, LPARAM lParam);
	LRESULT OnGlobalHotkey(WPARAM wParam, LPARAM lParam);


	INT m_nTimerCount;
	CSystemTray m_TrayIcon;
	HWND		m_hWndNextViewer;

	CBrush		m_BrushToolTip;
	CBrush		m_BrushShadow;

	// Settings
	UINT		m_uHotkeyActivate;
	UINT		m_uHotkeyModifierActivate;

	UINT		m_uHotkeyDelete;
	UINT		m_uHotkeyModifierDelete;

	UINT		m_uHotkeyNext;
	UINT		m_uHotkeyModifierNext;

	UINT		m_uHotkeyPrevious;
	UINT		m_uHotkeyModifierPrevious;


	// Manager
	CClipboardMgr m_ClipboardMgr;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__4F0BC3A0_FCA2_418F_B04C_FC4FD850FDB8__INCLUDED_)
