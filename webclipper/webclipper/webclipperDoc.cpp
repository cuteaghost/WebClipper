
// webclipperDoc.cpp : CwebclipperDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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


// ChtmlDoc 构造/析构

CwebclipperDoc::CwebclipperDoc()
{
	// TODO: 在此添加一次性构造代码
}

CwebclipperDoc::~CwebclipperDoc()
{
}

BOOL CwebclipperDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	if (NewDocumentStartup == 0)
	{
		//AfxMessageBox(_T("不打开...."));
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
		AfxMessageBox(_T("打开...."));
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
		OnSaveDocument(strPath); // 这个函数能自动地消除文档修改标记
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
		OnSaveDocument(strPath); // 这个函数能自动地消除文档修改标记
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
	//AfxMessageBox(_T("保存成功！"));
	return TRUE;
}

// ChtmlDoc 序列化

void CwebclipperDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CwebclipperDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
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

// 搜索处理程序的支持
void CwebclipperDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
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

// ChtmlDoc 诊断

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


// CwebclipperDoc 命令
