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
// ClipboardCFTextEntry.cpp: implementation of the CClipboardCFEntry class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "smartclip.h"
#include "ClipboardCFTextEntry.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClipboardCFTextEntry::CClipboardCFTextEntry()
{
	m_ClipboardType = CB_CF_TEXT;
}

CClipboardCFTextEntry::~CClipboardCFTextEntry()
{

}

#ifdef _DEBUG
void CClipboardCFTextEntry::AssertValid() const
{

}

void CClipboardCFTextEntry::Dump(CDumpContext &dc) const
{
	dc << "CFTextEntry" << "\tSize : " << m_dwCBDataSize << "\n";
	dc << (LPCTSTR)m_pCBData;
	dc << "\n";

}
#endif	//_DEBUG

void CClipboardCFTextEntry::RenderData(CDC &Dc, CRect &DisplayRect)
{
	INT nPreviousMode = Dc.SetBkMode(TRANSPARENT);
	Dc.DrawText((LPCTSTR)m_pCBData, (int)m_dwCBDataSize - 1, &DisplayRect, DT_LEFT | DT_TOP | DT_EXPANDTABS | DT_NOPREFIX | DT_WORDBREAK | DT_EDITCONTROL); 
	Dc.SetBkMode(nPreviousMode);
}
