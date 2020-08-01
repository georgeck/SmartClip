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
// ClipboardMgr.h: interface for the CClipboardMgr class.
//
//////////////////////////////////////////////////////////////////////
 
#if !defined(AFX_CLIPBOARDMGR_H__F83F2893_7D89_4136_B75D_457DFB8A3077__INCLUDED_)
#define AFX_CLIPBOARDMGR_H__F83F2893_7D89_4136_B75D_457DFB8A3077__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ClipboardEntry.h"
#include "ClipboardCFTextEntry.h"
#include "ClipboardCFBitmapEntry.h"
#include "ClipboardEntryArray.h"
#include "ClipboardList.h"


class CClipboardMgr : public CObject  
{
public:
	void EmptyCBClipBoard();
	INT GetMaxEntries();
	void SetMaxEntries(INT nMaxEntries);
	BOOL PutPrevEntryToCB();
	BOOL PutNextEntryToCB();
	void DrawClipboad(CDC& Dc, CRect& DisplayRect);
	BOOL SetClipboardEntries();
	BOOL GetClipboardEntries();
	CClipboardMgr();
	virtual ~CClipboardMgr();

	// Debug Functions
#ifdef _DEBUG
	virtual void Dump( CDumpContext& dc ) const;
	virtual void AssertValid() const;
#endif	//_DEBUG

private:
	CClipboardEntry* GetClipboardEntryOfType(UINT uFormatType);
	BOOL IsRequiredFormat(UINT uFormatType);

	CClipboardList m_ClipboardList;

};


#endif // !defined(AFX_CLIPBOARDMGR_H__F83F2893_7D89_4136_B75D_457DFB8A3077__INCLUDED_)
