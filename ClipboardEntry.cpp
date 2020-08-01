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
// ClipboardEntry.cpp: implementation of the CClipboardEntry class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "smartclip.h"
#include "ClipboardEntry.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClipboardEntry::CClipboardEntry()
{
	m_ClipboardType	= CB_CF_EMPTY;
	m_pCBData		= NULL;
	m_dwCBDataSize	= 0;
}

CClipboardEntry::~CClipboardEntry()
{
	DeleteSelf();
}

#ifdef _DEBUG
void CClipboardEntry::AssertValid() const
{

}

void CClipboardEntry::Dump(CDumpContext &dc) const
{
	
}
#endif	//_DEBUG

BOOL CClipboardEntry::DeleteSelf()
{
	if(m_pCBData)
		delete[] m_pCBData;

	return FALSE;
}

BOOL CClipboardEntry::GetFromClipboard()
{
	// Clipboard is already opened by CClipboardEntryArray 
	ASSERT(m_ClipboardType != CB_CF_EMPTY);
	ASSERT(m_pCBData == NULL);

	// Get the data
	HANDLE hData = GetClipboardData(m_ClipboardType);
	ASSERT(hData != NULL);

	if(hData)
	{
		m_dwCBDataSize = GlobalSize(hData);
		BYTE* pData = (BYTE*)::GlobalLock(hData);
		if(pData != NULL)
		{
			// Allocate data and copy the entry
			m_pCBData = new BYTE[m_dwCBDataSize];

			ASSERT(m_pCBData != NULL);

			if(m_pCBData)
				memcpy(m_pCBData, pData, m_dwCBDataSize);				
		}

		GlobalUnlock(hData);
	}
	return TRUE;
}

BOOL CClipboardEntry::PutToClipboard()
{
	// Clipboard is already opened by CClipboardEntryArray 
	ASSERT(m_ClipboardType != CB_CF_EMPTY);
	ASSERT(m_pCBData != NULL);

	if(m_pCBData)
	{
		// Allocate a global memory object for the Data
		HGLOBAL hgData = GlobalAlloc(GMEM_MOVEABLE, m_dwCBDataSize); 
		if (hgData == NULL) 
		{ 
			return FALSE; 
		} 
		
		// Lock the handle and copy the text to the buffer. 
		BYTE* pData = (BYTE*)GlobalLock(hgData); 
		memcpy(pData, m_pCBData, m_dwCBDataSize);
		GlobalUnlock(hgData); 
		
		// Place the handle on the clipboard. 
		SetClipboardData(m_ClipboardType, hgData); 
	}	
	return TRUE;
}

CBOARD_TYPE CClipboardEntry::GetFormat()
{
	return m_ClipboardType;
}

