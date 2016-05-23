
// Logic_Circuit_SimulatorView.h : CLogic_Circuit_SimulatorView Ŭ������ �������̽�
//

#pragma once
#include "LogicUnit.h"


class CLogic_Circuit_SimulatorView : public CView
{
protected: // serialization������ ��������ϴ�.
	CLogic_Circuit_SimulatorView();
	DECLARE_DYNCREATE(CLogic_Circuit_SimulatorView)

// Ư���Դϴ�.
public:
	CLogic_Circuit_SimulatorDoc* GetDocument() const;

// �۾��Դϴ�.
public:
	CArray<CRect, CRect&> boxes; // �ڽ� ��ü ����Ʈ
	CPtrList DrawList;
	POSITION current;
	bool move;
	int startx;
	int starty;


	void CreatePoint(CDC* pDC);
	void DrawUnit(CDC* pDC, CPoint pt, LogicUnit *unit);
	bool CheckIn(CPoint pt);

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CLogic_Circuit_SimulatorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void CreateInput();
	afx_msg void CreateOutput();
	afx_msg void CreateAND();
	afx_msg void CreateOr();
};

#ifndef _DEBUG  // Logic_Circuit_SimulatorView.cpp�� ����� ����
inline CLogic_Circuit_SimulatorDoc* CLogic_Circuit_SimulatorView::GetDocument() const
   { return reinterpret_cast<CLogic_Circuit_SimulatorDoc*>(m_pDocument); }
#endif

