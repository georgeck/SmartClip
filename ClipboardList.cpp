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
// ClipboardList.cpp: implementation of the CClipboardList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "smartclip.h"
#include "ClipboardList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClipboardList::CClipboardList()
{
	m_CurrentEntry = NULL;
	m_nMaxEntries  = 7;			// Default Entries
}

CClipboardList::~CClipboardList()
{
	DeleteSelf();
}

#ifdef _DEBUG
void CClipboardList::AssertValid() const
{

}

void CClipboardList::Dump(CDumpContext &dc) const
{
	// Loop through the list and DISPLAY all entries
	POSITION pos = GetHeadPosition();

//	CList <CClipboardEntryArray*, CClipboardEntryArray*>::Dump(dc);
	for(INT nItter = 0; nItter < GetCount(); nItter++)
	{
		CClipboardEntryArray* pClipboardEntryArray = GetNext(pos);
		if(pClipboardEntryArray)
		{
			pClipboardEntryArray->Dump(dc);
		}
	}

}
#endif	//_DEBUG

CClipboardEntryArray* CClipboardList::GetCurrentEntry()
{
	if(m_CurrentEntry == NULL)
		return NULL;

	CClipboardEntryArray* pCurrentEntry = GetAt(m_CurrentEntry);

	ASSERT_VALID(pCurrentEntry);
	return pCurrentEntry;
}

BOOL CClipboardList::DeleteSelf()
{
	// Loop through the list and delete all entries
	POSITION pos = GetHeadPosition();

	for(INT nItter = 0; nItter < GetCount(); nItter++)
	{
		CClipboardEntryArray* pClipboardEntryArray = GetNext(pos);
		if(pClipboardEntryArray)
			delete pClipboardEntryArray;
	}

	RemoveAll();
	m_CurrentEntry = NULL;
	return TRUE;
}

BOOL CClipboardList::AddNewEntry(CClipboardEntryArray *pNewCBEntryArray)
{
	ASSERT(pNewCBEntryArray != NULL);
	ASSERT_VALID(pNewCBEntryArray);

	// Check if we have reached MAX entry count
	if(GetCount() >= m_nMaxEntries)
	{
		// Delete from the head (Oldest entry)
		CClipboardEntryArray* pTempEntry = RemoveHead();
		ASSERT(pTempEntry);

		if(pTempEntry)
			delete pTempEntry;

		ASSERT(GetCount() == (m_nMaxEntries - 1));
	}

	// Always add to the bottom of the list
	m_CurrentEntry = AddTail(pNewCBEntryArray);

	return TRUE;
}


CClipboardEntryArray* CClipboardList::GetNextEntry()
{
	//ASSERT(m_CurrentEntry != NULL);

	if(m_CurrentEntry == GetTailPosition())
	{
		// We are on the Tail of the list.
		return NULL;
	}

	CClipboardEntryArray* pReturnEntry = NULL;
	GetNext(m_CurrentEntry);

	pReturnEntry = GetAt(m_CurrentEntry);

	ASSERT(pReturnEntry != NULL);
	ASSERT_VALID(pReturnEntry);

	return pReturnEntry;
}

CClipboardEntryArray* CClipboardList::GetPreviousEntry()
{
	if(m_CurrentEntry == GetHeadPosition())
	{
		// We are on the head of the list.
		return NULL;
	}

	CClipboardEntryArray* pReturnEntry = NULL;
	GetPrev(m_CurrentEntry);

	pReturnEntry = GetAt(m_CurrentEntry);

	ASSERT(pReturnEntry != NULL);
	ASSERT_VALID(pReturnEntry);

	return pReturnEntry;
}

BOOL CClipboardList::DeleteCurrentEntry()
{
	
	return TRUE;
}

void CClipboardList::SetMaxEntries(INT nMaxEntries)
{
	if(GetCount() > nMaxEntries)
	{
		// We have to trim ourself
		// TODO
	}
	m_nMaxEntries = nMaxEntries;
}

INT CClipboardList::GetMaxEntries()
{
	return m_nMaxEntries;
}
