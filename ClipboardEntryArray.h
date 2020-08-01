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
// ClipboardEntryArray.h: interface for the CClipboardEntryArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIPBOARDENTRYARRAY_H__B8F992DE_EA11_4C8E_8A7F_2111EFE0EB19__INCLUDED_)
#define AFX_CLIPBOARDENTRYARRAY_H__B8F992DE_EA11_4C8E_8A7F_2111EFE0EB19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ClipboardEntry.h"

class CClipboardEntryArray : public CArray<CClipboardEntry*, CClipboardEntry*>
{
public:
	CClipboardEntryArray();
	virtual ~CClipboardEntryArray();

	BOOL PutClipboardEntries();
	BOOL GetClipboardEntries();

protected:
	BOOL DeleteSelf();

	// Debug Functions
public:
	CClipboardEntry* GetClipboardEntryOfType(UINT nCFType);
#ifdef _DEBUG
	virtual void Dump( CDumpContext& dc ) const;
	virtual void AssertValid() const;
#endif	//_DEBUG
};

#endif // !defined(AFX_CLIPBOARDENTRYARRAY_H__B8F992DE_EA11_4C8E_8A7F_2111EFE0EB19__INCLUDED_)
