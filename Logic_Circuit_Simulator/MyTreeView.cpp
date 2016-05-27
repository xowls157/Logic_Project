// MyTreeView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Logic_Circuit_Simulator.h"
#include "Logic_Circuit_SimulatorView.h"
#include "LogicUnit.h"
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
	HTREEITEM hGate[4];
	CString Gate[] = {
		_T("논리게이트"), _T("플립플롭"), _T("입/출력"), _T("클럭")
	};
	for (int i = 0; i<4; i++)
		hGate[i] = tree.InsertItem(Gate[i], 0, 0, TVI_ROOT, TVI_LAST);

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
	/*
	CTreeCtrl m_taskList;
	HTREEITEM hSelectedItem = m_taskList.GetSelectedItem();

	if (hGate[1])
	{
	AndGate *in1 = new AndGate(CPoint(10, 10));

	DrawList.AddHead(in1);

	Invalidate();
	// 선택한 Item의 Text 정보
	//CString strData = m_taskList.GetItemText(hSelectedItem);
	//CTreeView *test = (CTest *)m_taskList.GetItemData(hSelectedItem);
	}
	*/

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
