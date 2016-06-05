// MyTreeView.cpp : 구현 파일입니다.
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


// CMyTreeView 진단입니다.

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


// CMyTreeView 메시지 처리기입니다.


void CMyTreeView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	// 이미지 리스트 생성과 초기화
	CImageList il;
	il.Create(IDB_BITMAP5, 16, 1, RGB(255, 255, 255));

	// 이미지 리스트 설정
	CTreeCtrl& tree = GetTreeCtrl();
	tree.SetImageList(&il, TVSIL_NORMAL);
	il.Detach();

	// 1-레벨 초기화
	CString Gate[] = {
		_T("논리게이트"), _T("플립플롭"), _T("입/출력"), _T("클럭")
	};
	for (int i = 0; i<4; i++)
		this->hGate[i] = tree.InsertItem(Gate[i], 0, 0, TVI_ROOT, TVI_LAST);

	// 2-레벨 초기화
	tree.InsertItem(_T("ANDGATE"), 1, 1, hGate[0], TVI_LAST);
	tree.InsertItem(_T("ORGATE"), 1, 1, hGate[0], TVI_LAST);
	tree.InsertItem(_T("NOTGATE"), 1, 1, hGate[0], TVI_LAST);
	tree.InsertItem(_T("NANDGATE"), 1, 1, hGate[0], TVI_LAST);
	tree.InsertItem(_T("NORGATE"), 1, 1, hGate[0], TVI_LAST);
	tree.InsertItem(_T("XORGATE"), 1, 1, hGate[0], TVI_LAST);

	tree.InsertItem(_T("D-FF"), 1, 1, hGate[1], TVI_LAST);
	tree.InsertItem(_T("JK-FF"), 1, 1, hGate[1], TVI_LAST);
	tree.InsertItem(_T("T-FF"), 1, 1, hGate[1], TVI_LAST);

	tree.InsertItem(_T("입력"), 1, 1, hGate[2], TVI_LAST);
	tree.InsertItem(_T("출력"), 1, 1, hGate[2], TVI_LAST);

	}


BOOL CMyTreeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	cs.style |= TVS_HASBUTTONS;
	cs.style |= TVS_HASLINES;
	cs.style |= TVS_LINESATROOT;
	cs.style |= TVS_TRACKSELECT;


	return CTreeView::PreCreateWindow(cs);
}


void CMyTreeView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

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
	else if (item_name == _T("입력")) {
		InputSwitch *unit = new InputSwitch(CPoint(40, 40));
		view->DrawList.AddHead(unit);
		view->Invalidate();
	}
	else if (item_name == _T("출력")) {
		OutputSwitch  *unit = new OutputSwitch(CPoint(40, 40));
		view->DrawList.AddHead(unit);
		view->Invalidate();
	}

	CTreeView::OnLButtonDblClk(nFlags, point);
}
