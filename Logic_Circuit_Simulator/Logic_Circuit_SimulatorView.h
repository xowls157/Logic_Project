
// Logic_Circuit_SimulatorView.h : CLogic_Circuit_SimulatorView 클래스의 인터페이스
//

#pragma once
#include "LogicUnit.h"


class CLogic_Circuit_SimulatorView : public CView
{
protected: // serialization에서만 만들어집니다.
	CLogic_Circuit_SimulatorView();
	DECLARE_DYNCREATE(CLogic_Circuit_SimulatorView)

// 특성입니다.
public:
	CLogic_Circuit_SimulatorDoc* GetDocument() const;

// 작업입니다.
public:
	CArray<CRect, CRect&> boxes; // 박스 객체 리스트
	CPtrList DrawList;
	POSITION current;
	bool move;
	int startx;
	int starty;


	void CreatePoint(CDC* pDC);
	void DrawUnit(CDC* pDC, CPoint pt, LogicUnit *unit);
	bool CheckIn(CPoint pt);

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CLogic_Circuit_SimulatorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
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

#ifndef _DEBUG  // Logic_Circuit_SimulatorView.cpp의 디버그 버전
inline CLogic_Circuit_SimulatorDoc* CLogic_Circuit_SimulatorView::GetDocument() const
   { return reinterpret_cast<CLogic_Circuit_SimulatorDoc*>(m_pDocument); }
#endif

