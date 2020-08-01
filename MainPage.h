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
// MainPage.h : header file
//

#ifndef __MAINPAGE_H__
#define __MAINPAGE_H__

/////////////////////////////////////////////////////////////////////////////
// CMainPage dialog

class CMainPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMainPage)

// Construction
public:
	CMainPage();
	~CMainPage();

// Dialog Data
	//{{AFX_DATA(CMainPage)
	enum { IDD = IDD_MAIN_PAGE };
	CHotKeyCtrl	m_ctlHotkeyActivate;
	CHotKeyCtrl	m_ctlHotkeyDelete;
	CHotKeyCtrl	m_ctlHotkeyNext;
	CHotKeyCtrl	m_ctlHotkeyPrevious;
	UINT	m_nMaxEntries;
	BOOL	m_bEnableAutoStart;
	BOOL	m_bDissable;
	//}}AFX_DATA

	// Activate
	WORD m_dwHotkeyActivate;
	WORD m_dwHotkeyModifierActivate;

	// Delete
	WORD m_dwHotkeyDelete;
	WORD m_dwHotkeyModifierDelete;

	// Next
	WORD m_dwHotkeyNext;
	WORD m_dwHotkeyModifierNext;

	// Previous
	WORD m_dwHotkeyPrevious;
	WORD m_dwHotkeyModifierPrevious;



// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMainPage)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnApply();
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMainPage)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnEnableAutostart();
	afx_msg void OnDissableSmartclip();
	afx_msg void OnChangeMaxEntries();
	afx_msg void OnChangeCFDissable();
	afx_msg void OnHotkeyLoadDefaults();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	WORD TranslateFromHotKeyCtrl(WORD dwData);
	WORD Translate2HotKeyCtrl(WORD dwData);
};
/*
/////////////////////////////////////////////////////////////////////////////
// CPage dialog

class CPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CPage)

// Construction
public:
	CPage();
	~CPage();

// Dialog Data
	//{{AFX_DATA(CPage)
	enum { IDD = IDD_PROPPAGE3 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
*/

#endif // __MAINPAGE_H__
