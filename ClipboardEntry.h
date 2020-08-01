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
// ClipboardEntry.h: interface for the CClipboardEntry class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIPBOARDENTRY_H__74EC4094_9A31_4E4E_9DA2_42EADEE7CFC5__INCLUDED_)
#define AFX_CLIPBOARDENTRY_H__74EC4094_9A31_4E4E_9DA2_42EADEE7CFC5__INCLUDED_

#include "Defines.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CClipboardEntry : public CObject  
{
public:
	CClipboardEntry();
	virtual ~CClipboardEntry();

	// Debug Functions
#ifdef _DEBUG
	virtual void Dump( CDumpContext& dc ) const;
	virtual void AssertValid() const;
#endif	//_DEBUG

protected:
	DWORD m_dwCBDataSize;
	BYTE* m_pCBData;
	CBOARD_TYPE m_ClipboardType;

	virtual BOOL DeleteSelf();

public:
	virtual void RenderData(CDC &Dc, CRect &DisplayRect) = 0;
	CBOARD_TYPE GetFormat();
	virtual BOOL GetFromClipboard();
	virtual BOOL PutToClipboard();
};

#endif // !defined(AFX_CLIPBOARDENTRY_H__74EC4094_9A31_4E4E_9DA2_42EADEE7CFC5__INCLUDED_)
