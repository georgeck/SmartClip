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
// ClipboardCFBitmapEntry.h: interface for the CClipboardCFBitmapEntry class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIPBOARDCFBITMAPENTRY_H__FAE745B9_11CB_4E46_BD47_5183CA3483A2__INCLUDED_)
#define AFX_CLIPBOARDCFBITMAPENTRY_H__FAE745B9_11CB_4E46_BD47_5183CA3483A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ClipboardEntry.h"

class CClipboardCFBitmapEntry : public CClipboardEntry  
{
public:
	BOOL DeleteSelf();
	BOOL GetFromClipboard();
	CClipboardCFBitmapEntry();
	virtual ~CClipboardCFBitmapEntry();

	// Debug Functions
#ifdef _DEBUG
	virtual void Dump( CDumpContext& dc ) const;
	virtual void AssertValid() const;
#endif	//_DEBUG

	void RenderData(CDC &Dc, CRect &DisplayRect);

protected:

};

#endif // !defined(AFX_CLIPBOARDCFBITMAPENTRY_H__FAE745B9_11CB_4E46_BD47_5183CA3483A2__INCLUDED_)
