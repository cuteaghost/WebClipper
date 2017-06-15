
// webclipperDoc.cpp : CwebclipperDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "webclipper.h"
#endif

#include "webclipperDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "my.h"

// ChtmlDoc

IMPLEMENT_DYNCREATE(CwebclipperDoc, CHtmlEditDoc)

BEGIN_MESSAGE_MAP(CwebclipperDoc, CHtmlEditDoc)
END_MESSAGE_MAP()


// ChtmlDoc ����/����

CwebclipperDoc::CwebclipperDoc()
{
	// TODO: �ڴ����һ���Թ������
}

CwebclipperDoc::~CwebclipperDoc()
{
}

BOOL CwebclipperDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)
	if (NewDocumentStartup == 0)
	{
		//AfxMessageBox(_T("����...."));
		//OnOpenDocument(_T("E:\\VisualStudio\\html0.4\\html\\Debug\\start.html"));	

		CString  strPathName;
		GetModuleFileName(NULL, strPathName.GetBuffer(256), 256);
		strPathName.ReleaseBuffer(256);
		int nPos = strPathName.ReverseFind('\\');
		strPathName = strPathName.Left(nPos + 1);
		strPathName += "start.html";
		//AfxMessageBox(strPathName);
		OnOpenDocument((LPCTSTR)strPathName);

		NewDocumentStartup = 1;
	}
	else
	{
		AfxMessageBox(_T("��...."));
	}

	return TRUE;
}

void CwebclipperDoc::OnCloseDocument()
{
	if (IsModified())
	{
		CFile outfile;
		outfile.Open(_T("test"), CFile::modeCreate | CFile::modeReadWrite);

		CString strPath = outfile.GetFilePath();

		outfile.Close();
		OnSaveDocument(strPath); // ����������Զ��������ĵ��޸ı��
	}
	return CDocument::OnCloseDocument();
}

BOOL CwebclipperDoc::CanCloseFrame(CFrameWnd* pFrame)
{
	if (IsModified())
	{
		CFile outfile;
		outfile.Open(_T("test"), CFile::modeCreate | CFile::modeReadWrite);

		CString strPath = outfile.GetFilePath();

		outfile.Close();
		OnSaveDocument(strPath); // ����������Զ��������ĵ��޸ı��
	}
	return CDocument::CanCloseFrame(pFrame);
	//return TRUE;
}

BOOL CwebclipperDoc::SaveModified()
{
	return TRUE;
}


BOOL CwebclipperDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnSaveDocument(lpszPathName))
		return FALSE;
	//AfxMessageBox(_T("����ɹ���"));
	return TRUE;
}

// ChtmlDoc ���л�

void CwebclipperDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CwebclipperDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CwebclipperDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CwebclipperDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// ChtmlDoc ���

#ifdef _DEBUG
void CwebclipperDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CwebclipperDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CwebclipperDoc ����
