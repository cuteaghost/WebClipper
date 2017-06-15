
// webclipperView.cpp : CwebclipperView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "webclipper.h"
#endif

#include "webclipperDoc.h"
#include "webclipperView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CwebclipperView

IMPLEMENT_DYNCREATE(CwebclipperView, CHtmlEditView)

BEGIN_MESSAGE_MAP(CwebclipperView, CHtmlEditView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CHtmlEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CHtmlEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CHtmlEditView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CwebclipperView 构造/析构

CwebclipperView::CwebclipperView()
{
	// TODO: 在此处添加构造代码

}

CwebclipperView::~CwebclipperView()
{
}

BOOL CwebclipperView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CwebclipperView 绘制

void CwebclipperView::OnDraw(CDC* /*pDC*/)
{
	CwebclipperDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CwebclipperView 打印


void CwebclipperView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CwebclipperView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CwebclipperView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CwebclipperView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CwebclipperView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CwebclipperView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CwebclipperView 诊断

#ifdef _DEBUG
void CwebclipperView::AssertValid() const
{
	CView::AssertValid();
}

void CwebclipperView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CwebclipperDoc* CwebclipperView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CwebclipperDoc)));
	return (CwebclipperDoc*)m_pDocument;
}
#endif //_DEBUG


// CwebclipperView 消息处理程序
