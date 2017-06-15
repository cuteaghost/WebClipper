
// webclipperView.h : CwebclipperView ��Ľӿ�
//

#pragma once


class CwebclipperView : public CHtmlEditView
{
protected: // �������л�����
	CwebclipperView();
	DECLARE_DYNCREATE(CwebclipperView)

	// ����
public:
	CwebclipperDoc* GetDocument() const;

	// ����
public:

	// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// ʵ��
public:
	virtual ~CwebclipperView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // htmlView.cpp �еĵ��԰汾
inline ChtmlDoc* ChtmlView::GetDocument() const
{
	return reinterpret_cast<ChtmlDoc*>(m_pDocument);
}
#endif

