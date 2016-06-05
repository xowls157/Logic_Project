
// Logic_Circuit_SimulatorView.h : CLogic_Circuit_SimulatorView 클래스의 인터페이스
//

#pragma once
#include "LogicUnit.h"
#include "Logic_Circuit_SimulatorDoc.h"

struct unitStack {
	LogicUnit *unit;
	bool* prev;
};

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
	CPtrList DrawList;	//생성된 게이트들을 저장할 리스트
	CPtrList LineList;	//생성된 라인들을 저장할 리스트
	
	unitStack *stack;	//출력들을 update할 때 저장할 스택
	int stack_count;	//위 스택의 카운트
	
	POSITION current;	//현재 선택된 게이트의 position
	bool move;			//현재 선택된 게이트의 이동 가능 상태
	bool linning;		//라인을 그릴 수 있는 상태
	CPoint line_start_pt;	//라인을 그리는 시작점

	CPoint mPoint;
	int startx;			//라인을 다시그리는 시작점	(마우스무브에서 사용)
	int starty;			
	int prevx;			//이전에 라인을 그렸던 끝점 (마우스무브에서 사용)
	int prevy;

	//게이트 간 연결시 임시로 저장해주는 변수
	LogicUnit *selected;
	LogicUnit *selected_Input;
	LogicUnit *selected_Output;
	int selected_Input_Index;
	int selected_Output_Index;


	//작업 메소드들
	void CreatePoint(CDC* pDC);
	void DrawUnit(CDC* pDC, CPoint pt, LogicUnit *unit);
	POSITION CheckOnLine(CPoint pt);
	bool CheckIn(CPoint pt);
	POSITION CheckOnBranch(CPoint pt);

	CPoint Nearby_point(CPoint pt);
	void newUpdate(LogicUnit *unit);
	void Update(LogicUnit *unit);
	int isInStack(LogicUnit *unit);
	int search_unit(CPoint pt,bool &isInput);

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
	afx_msg void CreateNot();
	afx_msg void CreateNand();
	afx_msg void CreateNor();
	afx_msg void CreateXor();
	afx_msg void CreateDFF();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnLabel();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnFileNew();
	afx_msg void OnRotate();
};

#ifndef _DEBUG  // Logic_Circuit_SimulatorView.cpp의 디버그 버전
inline CLogic_Circuit_SimulatorDoc* CLogic_Circuit_SimulatorView::GetDocument() const
   { return reinterpret_cast<CLogic_Circuit_SimulatorDoc*>(m_pDocument); }
#endif

