// MyTreeView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Logic_Circuit_Simulator.h"
#include "Logic_Circuit_SimulatorView.h"
#include "LogicUnit.h"
#include "MainFrm.h"
#include "MyTreeView.h"


// CMyTreeView

IMPLEMENT_DYNCREATE(CMyTreeView, CTreeView)

CMyTreeView::CMyTreeView()
{

}

CMyTreeView::~CMyTreeView()
{
}

BEGIN_MESSAGE_MAP(CMyTreeView, CTreeView)
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// CMyTreeView �����Դϴ�.

#ifdef _DEBUG
void CMyTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyTreeView �޽��� ó�����Դϴ�.


void CMyTreeView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	// �̹��� ����Ʈ ������ �ʱ�ȭ
	CImageList il;
	il.Create(IDB_BITMAP5, 16, 1, RGB(255, 255, 255));

	// �̹��� ����Ʈ ����
	CTreeCtrl& tree = GetTreeCtrl();
	tree.SetImageList(&il, TVSIL_NORMAL);
	il.Detach();

	// 1-���� �ʱ�ȭ
	CString Gate[] = {
		_T("������Ʈ"), _T("�ø��÷�"), _T("��/���"), _T("Ŭ��")
	};
	for (int i = 0; i<4; i++)
		this->hGate[i] = tree.InsertItem(Gate[i], 0, 0, TVI_ROOT, TVI_LAST);

	// 2-���� �ʱ�ȭ
	tree.InsertItem(_T("ANDGATE"), 1, 1, hGate[0], TVI_LAST);
	tree.InsertItem(_T("ORGATE"), 1, 1, hGate[0], TVI_LAST);
	tree.InsertItem(_T("NOTGATE"), 1, 1, hGate[0], TVI_LAST);
	tree.InsertItem(_T("NANDGATE"), 1, 1, hGate[0], TVI_LAST);
	tree.InsertItem(_T("NORGATE"), 1, 1, hGate[0], TVI_LAST);
	tree.InsertItem(_T("XORGATE"), 1, 1, hGate[0], TVI_LAST);

	tree.InsertItem(_T("D-FF"), 1, 1, hGate[1], TVI_LAST);
	tree.InsertItem(_T("JK-FF"), 1, 1, hGate[1], TVI_LAST);
	tree.InsertItem(_T("T-FF"), 1, 1, hGate[1], TVI_LAST);

	tree.InsertItem(_T("�Է�"), 1, 1, hGate[2], TVI_LAST);
	tree.InsertItem(_T("���"), 1, 1, hGate[2], TVI_LAST);

	}


BOOL CMyTreeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	cs.style |= TVS_HASBUTTONS;
	cs.style |= TVS_HASLINES;
	cs.style |= TVS_LINESATROOT;
	cs.style |= TVS_TRACKSELECT;


	return CTreeView::PreCreateWindow(cs);
}


void CMyTreeView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CTreeCtrl& treeCtrl = GetTreeCtrl();
	CPoint  p;
	CLogic_Circuit_SimulatorView *view;

	GetCursorPos(&p);
	::ScreenToClient(treeCtrl.m_hWnd, &p);
	HTREEITEM hItem = treeCtrl.HitTest(p);

	view = (CLogic_Circuit_SimulatorView *)((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndSplitter.GetPane(0, 1);

	CString item_name = treeCtrl.GetItemText(hItem);


	if (item_name == _T("ANDGATE")) {
		AndGate *unit = new AndGate(CPoint(40, 40));
		view->DrawList.AddHead(unit);
		view->Invalidate();
	}
	else if (item_name == _T("ORGATE")) {
		OrGate *unit = new OrGate(CPoint(40, 40));
		view->DrawList.AddHead(unit);
		view->Invalidate();
	}
	else if (item_name == _T("NOTGATE")) {
		NotGate *unit = new NotGate(CPoint(40, 40));
		view->DrawList.AddHead(unit);
		view->Invalidate();
	}
	else if (item_name == _T("NANDGATE")) {
		NANDGate *unit = new NANDGate(CPoint(40, 40));
		view->DrawList.AddHead(unit);
		view->Invalidate();
	}
	else if (item_name == _T("NORGATE")) {
		NorGate *unit = new NorGate(CPoint(40, 40));
		view->DrawList.AddHead(unit);
		view->Invalidate();
	}
	else if (item_name == _T("XORGATE")) {
		XorGate *unit = new XorGate(CPoint(40, 40));
		view->DrawList.AddHead(unit);
		view->Invalidate();
	}
	else if (item_name == _T("D-FF")) {
		DFFGate *unit = new DFFGate(CPoint(40, 40));
		view->DrawList.AddHead(unit);
		view->Invalidate();

	}
	else if (item_name == _T("JK-FF")) {
		JKFFGate *unit = new JKFFGate(CPoint(40, 40));
		view->DrawList.AddHead(unit);
		view->Invalidate();

	}
	else if (item_name == _T("T-FF")) {
		TFFGate *unit = new TFFGate(CPoint(40, 40));
		view->DrawList.AddHead(unit);
		view->Invalidate();

	}
	else if (item_name == _T("�Է�")) {
		InputSwitch *unit = new InputSwitch(CPoint(40, 40));
		view->DrawList.AddHead(unit);
		view->Invalidate();
	}
	else if (item_name == _T("���")) {
		OutputSwitch  *unit = new OutputSwitch(CPoint(40, 40));
		view->DrawList.AddHead(unit);
		view->Invalidate();
	}

	CTreeView::OnLButtonDblClk(nFlags, point);
}
