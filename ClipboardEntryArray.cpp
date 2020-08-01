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
// ClipboardEntryArray.cpp: implementation of the CClipboardEntryArray class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "smartclip.h"
#include "ClipboardEntryArray.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClipboardEntryArray::CClipboardEntryArray()
{

}

CClipboardEntryArray::~CClipboardEntryArray()
{
	DeleteSelf();

	ASSERT(GetSize() == 0);
}

#ifdef _DEBUG
void CClipboardEntryArray::AssertValid() const
{

}

void CClipboardEntryArray::Dump(CDumpContext &dc) const
{
//	CArray<CClipboardEntry*, CClipboardEntry*>::Dump(dc);
	dc << "CClipboardEntryArray with size = " << GetSize() << "\n";
	// Loop through the Array and delete all entries
	INT nSize = GetSize();
	for(INT nCount = 0; nCount < nSize; nCount++)
	{
		CClipboardEntry* pClipboardEntry = GetAt(nCount);
		ASSERT(pClipboardEntry != NULL);
		if(pClipboardEntry)
		{
			pClipboardEntry->Dump(dc);
		}
	}
}
#endif	//_DEBUG

BOOL CClipboardEntryArray::GetClipboardEntries()
{
	// Loop through the list and get data in
	INT nSize = GetSize();
	for(INT nCount = 0; nCount < nSize; nCount++)
	{
		CClipboardEntry* pClipboardEntry = GetAt(nCount);
		ASSERT(pClipboardEntry != NULL);
		ASSERT_VALID(pClipboardEntry);

		if(pClipboardEntry)
		{
			pClipboardEntry->GetFromClipboard();
		}
	}

	return FALSE;
}

BOOL CClipboardEntryArray::PutClipboardEntries()
{
	// Open the Clipboard and keep it open 
	HWND hMainWnd = AfxGetMainWnd()->m_hWnd;
	ASSERT(::IsWindow(hMainWnd));

	if(!OpenClipboard(hMainWnd))
		return FALSE;

	// Empty its old contents
	EmptyClipboard(); 

	// Loop through and put data in
	INT nSize = GetSize();
	for(INT nCount = 0; nCount < nSize; nCount++)
	{
		CClipboardEntry* pClipboardEntry = GetAt(nCount);
		ASSERT(pClipboardEntry != NULL);
		ASSERT_VALID(pClipboardEntry);

		if(pClipboardEntry)
		{
			pClipboardEntry->PutToClipboard();
		}
	}

	// Close Clipboard
	CloseClipboard();

	return FALSE;
}

BOOL CClipboardEntryArray::DeleteSelf()
{
	// Loop through the Array and delete all entries
	INT nSize = GetSize();
	for(INT nCount = 0; nCount < nSize; nCount++)
	{
		CClipboardEntry* pClipboardEntry = GetAt(nCount);
		ASSERT(pClipboardEntry != NULL);
		if(pClipboardEntry)
		{
			delete pClipboardEntry;
		}
	}
	
	RemoveAll();
	return TRUE;
}

CClipboardEntry* CClipboardEntryArray::GetClipboardEntryOfType(UINT nCFType)
{
	// Loop through the Array and get the entry
	INT nSize = GetSize();
	for(INT nCount = 0; nCount < nSize; nCount++)
	{
		CClipboardEntry* pClipboardEntry = GetAt(nCount);
		ASSERT(pClipboardEntry != NULL);
		ASSERT_VALID(pClipboardEntry);

		if(pClipboardEntry)
		{
			if(nCFType == (UINT)pClipboardEntry->GetFormat() )
			{
				return pClipboardEntry;
			}
		}
	}
	return NULL;
}
