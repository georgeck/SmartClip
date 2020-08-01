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
// ClipboardCFBitmapEntry.cpp: implementation of the CClipboardCFBitmapEntry class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "smartclip.h"
#include "ClipboardCFBitmapEntry.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClipboardCFBitmapEntry::CClipboardCFBitmapEntry()
{
	m_ClipboardType = CB_CF_BITMAP;
}

CClipboardCFBitmapEntry::~CClipboardCFBitmapEntry()
{

}


#ifdef _DEBUG
void CClipboardCFBitmapEntry::AssertValid() const
{

}

void CClipboardCFBitmapEntry::Dump(CDumpContext &dc) const
{
	dc << "CFBitmapEntry" << "\tSize : " << m_dwCBDataSize << "\n";
}
#endif	//_DEBUG

void CClipboardCFBitmapEntry::RenderData(CDC& Dc, CRect &DisplayRect)
{
	// Create a MemoryDc
	CDC MemoryDc;
	if(MemoryDc.CreateCompatibleDC(&Dc))
	{
		HBITMAP hBitmap = (HBITMAP)m_pCBData;
		HBITMAP hOldBitmap = (HBITMAP)::SelectObject(MemoryDc.m_hDC, hBitmap);

		Dc.BitBlt(DisplayRect.left, DisplayRect.top, 
			DisplayRect.Width(), DisplayRect.Height(),
			&MemoryDc, 0, 0, SRCCOPY);

		::SelectObject(MemoryDc.m_hDC, hOldBitmap);
	}
}

BOOL CClipboardCFBitmapEntry::GetFromClipboard()
{
	// Clipboard is already opened by CClipboardEntryArray 
	ASSERT(m_ClipboardType != CB_CF_EMPTY);
	ASSERT(m_pCBData == NULL);

	// Get the data
	HBITMAP hBitmap = (HBITMAP)GetClipboardData(m_ClipboardType);
	ASSERT(hBitmap != NULL);

	if(hBitmap)
	{
		BITMAP BitMap;
		GetObject(hBitmap, sizeof(BITMAP), &BitMap);

		m_pCBData = (BYTE*)CreateBitmapIndirect(&BitMap);

		/*
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
		*/


	}
	return TRUE;
}

BOOL CClipboardCFBitmapEntry::DeleteSelf()
{
	if(m_pCBData)
	{
		DeleteObject((HGDIOBJ)m_pCBData);
		m_pCBData = NULL;
	}
	return TRUE;
}
