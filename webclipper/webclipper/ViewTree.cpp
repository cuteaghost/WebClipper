
#include "stdafx.h"
#include "ViewTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "webclipperDoc.h"
#include "MainFrm.h"

/////////////////////////////////////////////////////////////////////////////
// CViewTree

CViewTree::CViewTree()
{
}

CViewTree::~CViewTree()
{
}

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CViewTree::OnNMDblclk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTree ��Ϣ�������

BOOL CViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}


void CViewTree::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��ȡ��ǰѡ�����
	CTreeCtrl* pTreeCtrl = this;
	CPoint ptCurSel(0, 0);
	TVHITTESTINFO HitTestInfo;
	// ͨ������ڿͻ����е�λ��
	GetCursorPos(&ptCurSel);
	pTreeCtrl->ScreenToClient(&ptCurSel);
	// ��ȡ��ǰѡ�������һ��
	HitTestInfo.pt = ptCurSel;
	HTREEITEM hSelect = pTreeCtrl->HitTest(&HitTestInfo);

	if (hSelect != NULL)
	{
		CString strItem = pTreeCtrl->GetItemText(hSelect);
		//AfxMessageBox(strItem);
		if (strItem != "data")
		{
			CString  strPathName;
			GetModuleFileName(NULL, strPathName.GetBuffer(256), 256);
			strPathName.ReleaseBuffer(256);
			int nPos = strPathName.ReverseFind('\\');
			strPathName = strPathName.Left(nPos + 1);
			strPathName += "data\\";
			strPathName += strItem;
			//AfxMessageBox(strPathName);
			CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
			CwebclipperDoc* pHtmlDoc = (CwebclipperDoc*)pMainFrame->GetActiveDocument();
			pHtmlDoc->OnOpenDocument((LPCTSTR)strPathName);
		}
	}
	// ���ø���Ϊѡ��״̬
	pTreeCtrl->SelectItem(hSelect);

	*pResult = 0;
}
