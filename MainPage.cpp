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
// MainPage.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MainPage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMainPage, CPropertyPage)
//IMPLEMENT_DYNCREATE(CPage, CPropertyPage)


/////////////////////////////////////////////////////////////////////////////
// CMainPage property page

CMainPage::CMainPage() : CPropertyPage(CMainPage::IDD)
{
	m_dwHotkeyActivate = 0;
	m_dwHotkeyModifierActivate = 0;

	m_dwHotkeyDelete = 0;
	m_dwHotkeyModifierDelete = 0;

	m_dwHotkeyNext = 0;
	m_dwHotkeyModifierNext = 0;

	m_dwHotkeyPrevious = 0;
	m_dwHotkeyModifierPrevious = 0;

	
	//{{AFX_DATA_INIT(CMainPage)
	m_nMaxEntries = 0;
	m_bEnableAutoStart = FALSE;
	m_bDissable = FALSE;
	//}}AFX_DATA_INIT
}

CMainPage::~CMainPage()
{
}

void CMainPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainPage)
	DDX_Control(pDX, IDC_HOTKEY_ACTIVATE, m_ctlHotkeyActivate);
	DDX_Control(pDX, IDC_HOTKEY_DELETE, m_ctlHotkeyDelete);
	DDX_Control(pDX, IDC_HOTKEY_NEXT, m_ctlHotkeyNext);
	DDX_Control(pDX, IDC_HOTKEY_PREVIOUS, m_ctlHotkeyPrevious);
	DDX_Text(pDX, ID_MAX_ENTRIES, m_nMaxEntries);
	DDX_Check(pDX, ID_CF_ENABLE_AUTOSTART, m_bEnableAutoStart);
	DDX_Check(pDX, IDC_CF_DISSABLE, m_bDissable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMainPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMainPage)
	ON_WM_CREATE()
	ON_BN_CLICKED(ID_CF_ENABLE_AUTOSTART, OnEnableAutostart)
	ON_COMMAND(IDC_CF_DISSABLE, OnDissableSmartclip)
	ON_EN_CHANGE(IDC_CF_DISSABLE, OnChangeCFDissable)
	ON_EN_CHANGE(ID_MAX_ENTRIES,  OnChangeMaxEntries)
	ON_BN_CLICKED(IDC_HOTKEY_LOAD_DEFAULTS, OnHotkeyLoadDefaults)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/*
/////////////////////////////////////////////////////////////////////////////
// CPage property page

CPage::CPage() : CPropertyPage(CPage::IDD)
{
	//{{AFX_DATA_INIT(CPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPage::~CPage()
{
}

void CPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPage, CPropertyPage)
	//{{AFX_MSG_MAP(CPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

*/

BOOL CMainPage::OnSetActive() 
{

	return CPropertyPage::OnSetActive();
}

BOOL CMainPage::OnApply() 
{
	m_ctlHotkeyActivate.GetHotKey(m_dwHotkeyActivate,	m_dwHotkeyModifierActivate);
	m_ctlHotkeyDelete.GetHotKey	 (m_dwHotkeyDelete,	    m_dwHotkeyModifierDelete);
	m_ctlHotkeyNext.GetHotKey	 (m_dwHotkeyNext,		m_dwHotkeyModifierNext);
	m_ctlHotkeyPrevious.GetHotKey(m_dwHotkeyPrevious,	m_dwHotkeyModifierPrevious);

	m_dwHotkeyModifierActivate = TranslateFromHotKeyCtrl(m_dwHotkeyModifierActivate);
	m_dwHotkeyModifierDelete   = TranslateFromHotKeyCtrl(m_dwHotkeyModifierDelete);
	m_dwHotkeyModifierNext	   = TranslateFromHotKeyCtrl(m_dwHotkeyModifierNext);
	m_dwHotkeyModifierPrevious = TranslateFromHotKeyCtrl(m_dwHotkeyModifierPrevious);

	return CPropertyPage::OnApply();
}

void CMainPage::OnOK() 
{
	CRegKey Registry;
	if(Registry.Open(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run") == ERROR_SUCCESS)
	{
		if(m_bEnableAutoStart)
		{
			char szPath[MAX_PATH];
			ZeroMemory(szPath, MAX_PATH);
			
			GetModuleFileName(AfxGetResourceHandle(), szPath, MAX_PATH);
			if(lstrlen(szPath))
			{
				Registry.SetValue(szPath, "SmartClip");
			}		
		}
		else
		{
			// delete the key if found
			Registry.DeleteValue("SmartClip");
		}
	}	
	
	CPropertyPage::OnOK();
}

int CMainPage::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CPropertyPage::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	
	return 0;
}

WORD CMainPage::Translate2HotKeyCtrl(WORD dwData)
{
	WORD dwReturn = 0;

	if(dwData & MOD_ALT)
		dwReturn |= HOTKEYF_ALT;

	if(dwData & MOD_CONTROL)
		dwReturn |= HOTKEYF_CONTROL;

	if(dwData & MOD_SHIFT)
		dwReturn |= HOTKEYF_SHIFT;

	if(dwData & MOD_WIN)
		dwReturn |= HOTKEYF_EXT;

	return dwReturn;
}

WORD CMainPage::TranslateFromHotKeyCtrl(WORD dwData)
{
	WORD dwReturn = 0;

	if(dwData & HOTKEYF_ALT)
		dwReturn |= MOD_ALT;

	if(dwData & HOTKEYF_CONTROL)
		dwReturn |= MOD_CONTROL;

	if(dwData & HOTKEYF_SHIFT)
		dwReturn |= MOD_SHIFT;

	return dwReturn;

}

BOOL CMainPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CRegKey Registry;
	if(Registry.Open(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run") == ERROR_SUCCESS)
	{
		DWORD dwCount = MAX_PATH;
		char szPathQuery[MAX_PATH];
		Registry.QueryValue(szPathQuery, "SmartClip", &dwCount);

		char szPath[MAX_PATH];
		GetModuleFileName(AfxGetResourceHandle(), szPath, MAX_PATH);
		
		if(lstrcmp(szPathQuery, szPath) == 0)
		{
			m_bEnableAutoStart = TRUE;
		}
		else
		{
			m_bEnableAutoStart = FALSE;
		}
	}

	// Set the Hotkey 
	m_ctlHotkeyActivate.SetHotKey(m_dwHotkeyActivate,	Translate2HotKeyCtrl(m_dwHotkeyModifierActivate));
	m_ctlHotkeyDelete.SetHotKey	 (m_dwHotkeyDelete,	    Translate2HotKeyCtrl(m_dwHotkeyModifierDelete));
	m_ctlHotkeyNext.SetHotKey	 (m_dwHotkeyNext,		Translate2HotKeyCtrl(m_dwHotkeyModifierNext));
	m_ctlHotkeyPrevious.SetHotKey(m_dwHotkeyPrevious,	Translate2HotKeyCtrl(m_dwHotkeyModifierPrevious));
	
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMainPage::OnEnableAutostart() 
{
	SetModified();
}

void CMainPage::OnDissableSmartclip() 
{
	SetModified();
}

void CMainPage::OnChangeMaxEntries() 
{
	SetModified();
}

void CMainPage::OnChangeCFDissable() 
{
	SetModified();
}

void CMainPage::OnHotkeyLoadDefaults() 
{
	m_ctlHotkeyActivate.SetHotKey(67,	Translate2HotKeyCtrl(3));
	m_ctlHotkeyDelete.SetHotKey	 (38,	Translate2HotKeyCtrl(3));
	m_ctlHotkeyNext.SetHotKey	 (39,	Translate2HotKeyCtrl(3));
	m_ctlHotkeyPrevious.SetHotKey(37,	Translate2HotKeyCtrl(3));

	SetModified();
}
