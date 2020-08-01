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
// ClipboardMgr.cpp: implementation of the CClipboardMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "smartclip.h"

#include "ClipboardMgr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClipboardMgr::CClipboardMgr()
{

}

CClipboardMgr::~CClipboardMgr()
{

}


#ifdef _DEBUG
void CClipboardMgr::AssertValid() const
{

}

void CClipboardMgr::Dump(CDumpContext &dc) const
{
	m_ClipboardList.Dump(dc);
}

#endif	//_DEBUG

BOOL CClipboardMgr::GetClipboardEntries()
{
	HWND hMainWindow = AfxGetMainWnd()->m_hWnd;
	ASSERT(::IsWindow(hMainWindow));

	// Open the Clipboard
	OpenClipboard(hMainWindow);

	// Enumerate through the formats
	UINT uClipboradFormat = NULL;
	CClipboardEntryArray* pClipboardEntryArray = NULL;
	
	while(uClipboradFormat = EnumClipboardFormats(uClipboradFormat))
	{
		// Check if we need to capture this format
		if(IsRequiredFormat(uClipboradFormat))
		{
			// Create curresponding instance of CClipboardEntry
			CClipboardEntry* pNewEntry = GetClipboardEntryOfType(uClipboradFormat);

			ASSERT(pNewEntry != NULL);

			// Add it to the list
			if(pClipboardEntryArray == NULL)
				pClipboardEntryArray = new CClipboardEntryArray;

			pClipboardEntryArray->Add(pNewEntry);
		}
	}

	// Add the new CClipboardEntryArray to the list
	if(pClipboardEntryArray)
	{
		// Ask CClipboardEntryArray to populate the data
		pClipboardEntryArray->GetClipboardEntries();

		m_ClipboardList.AddNewEntry(pClipboardEntryArray);
	}

	// Close Clipboard
	CloseClipboard();
		
	return TRUE;
}

BOOL CClipboardMgr::IsRequiredFormat(UINT uFormatType)
{
	switch(uFormatType)
	{
	case CB_CF_TEXT:
		return TRUE;
		/*
	case CB_CF_BITMAP:
		return TRUE;
		*/
	}
	return FALSE;
}

CClipboardEntry* CClipboardMgr::GetClipboardEntryOfType(UINT uFormatType)
{
	switch(uFormatType)
	{
	case CB_CF_TEXT:
		return new CClipboardCFTextEntry();
	/*
	case CB_CF_BITMAP:
		return new CClipboardCFBitmapEntry();
	*/
	}
	return NULL;
}


BOOL CClipboardMgr::SetClipboardEntries()
{
	HWND hMainWindow = AfxGetMainWnd()->m_hWnd;
	ASSERT(::IsWindow(hMainWindow));

	// Get the current List
	CClipboardEntryArray* pClipboardEntryArray = m_ClipboardList.GetCurrentEntry();

	// Add the new CClipboardEntryArray to the list
	if(pClipboardEntryArray)
	{
		// Ask CClipboardEntryArray to put data back to clipboard
		pClipboardEntryArray->PutClipboardEntries();
	}
	return TRUE;
}

void CClipboardMgr::DrawClipboad(CDC &Dc, CRect &DisplayRect)
{
	// Find the best CB_Format to draw
	INT nFormat = GetPriorityClipboardFormat(CBPriorityList, sizeof(CBPriorityList)/sizeof(UINT)); 

	if(nFormat <= 0 )
	{
		INT nPreviousMode = Dc.SetBkMode(TRANSPARENT);
		Dc.DrawText(CString("Data not captured in ClipBoard"), &DisplayRect, DT_CENTER | DT_TOP | DT_EXPANDTABS | DT_NOPREFIX | DT_WORDBREAK | DT_VCENTER | DT_SINGLELINE | DT_EDITCONTROL); 
		Dc.SetBkMode(nPreviousMode);	
	}
	else
	{
		// Get this ClipboardEntry
		CClipboardEntry* pCBEntry = NULL;
		CClipboardEntryArray* pCBArray =  m_ClipboardList.GetCurrentEntry();
		if(pCBArray)
		{
			pCBEntry = pCBArray->GetClipboardEntryOfType(nFormat);
			
			if(pCBEntry)
			{
				ASSERT_VALID(pCBEntry);
				pCBEntry->RenderData(Dc, DisplayRect);
			}
		}
	}
}

BOOL CClipboardMgr::PutNextEntryToCB()
{
	// Get the next EntryArray
	CClipboardEntryArray* pCBarray = m_ClipboardList.GetNextEntry();

	if(!pCBarray)
	{
		MessageBeep(-1);
		return FALSE;
	}
	return pCBarray->PutClipboardEntries();

}

BOOL CClipboardMgr::PutPrevEntryToCB()
{
	// Get the prev EntryArray
	CClipboardEntryArray* pCBarray = m_ClipboardList.GetPreviousEntry();

	if(!pCBarray)
	{
		MessageBeep(-1);
		return FALSE;
	}
	return pCBarray->PutClipboardEntries();
}

void CClipboardMgr::SetMaxEntries(INT nMaxEntries)
{
	m_ClipboardList.SetMaxEntries(nMaxEntries);
}

INT CClipboardMgr::GetMaxEntries()
{
	return m_ClipboardList.GetMaxEntries();
}

void CClipboardMgr::EmptyCBClipBoard()
{
	HWND hMainWindow = AfxGetMainWnd()->m_hWnd;
	ASSERT(::IsWindow(hMainWindow));

	// Open the Clipboard clean it and close it.
	OpenClipboard(hMainWindow);
	EmptyClipboard();
	CloseClipboard();
	
	m_ClipboardList.DeleteSelf();
}
