
// webclipperView.cpp : CwebclipperView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CHtmlEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CHtmlEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CHtmlEditView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CwebclipperView ����/����

CwebclipperView::CwebclipperView()
{
	// TODO: �ڴ˴���ӹ������

}

CwebclipperView::~CwebclipperView()
{
}

BOOL CwebclipperView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CwebclipperView ����

void CwebclipperView::OnDraw(CDC* /*pDC*/)
{
	CwebclipperDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CwebclipperView ��ӡ


void CwebclipperView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CwebclipperView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CwebclipperView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CwebclipperView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CwebclipperView ���

#ifdef _DEBUG
void CwebclipperView::AssertValid() const
{
	CView::AssertValid();
}

void CwebclipperView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CwebclipperDoc* CwebclipperView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CwebclipperDoc)));
	return (CwebclipperDoc*)m_pDocument;
}
#endif //_DEBUG


// CwebclipperView ��Ϣ�������
