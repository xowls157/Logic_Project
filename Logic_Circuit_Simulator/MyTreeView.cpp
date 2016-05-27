// MyTreeView.cpp : ���� �����Դϴ�.
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
	HTREEITEM hGate[4];
	CString Gate[] = {
		_T("������Ʈ"), _T("�ø��÷�"), _T("��/���"), _T("Ŭ��")
	};
	for (int i = 0; i<4; i++)
		hGate[i] = tree.InsertItem(Gate[i], 0, 0, TVI_ROOT, TVI_LAST);

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
	/*
	CTreeCtrl m_taskList;
	HTREEITEM hSelectedItem = m_taskList.GetSelectedItem();

	if (hGate[1])
	{
	AndGate *in1 = new AndGate(CPoint(10, 10));

	DrawList.AddHead(in1);

	Invalidate();
	// ������ Item�� Text ����
	//CString strData = m_taskList.GetItemText(hSelectedItem);
	//CTreeView *test = (CTest *)m_taskList.GetItemData(hSelectedItem);
	}
	*/

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
