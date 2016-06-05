
// Logic_Circuit_SimulatorView.h : CLogic_Circuit_SimulatorView Ŭ������ �������̽�
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
protected: // serialization������ ��������ϴ�.
	CLogic_Circuit_SimulatorView();
	DECLARE_DYNCREATE(CLogic_Circuit_SimulatorView)

// Ư���Դϴ�.
public:
	CLogic_Circuit_SimulatorDoc* GetDocument() const;

// �۾��Դϴ�.
public:
	CPtrList DrawList;	//������ ����Ʈ���� ������ ����Ʈ
	CPtrList LineList;	//������ ���ε��� ������ ����Ʈ
	
	unitStack *stack;	//��µ��� update�� �� ������ ����
	int stack_count;	//�� ������ ī��Ʈ
	
	POSITION current;	//���� ���õ� ����Ʈ�� position
	bool move;			//���� ���õ� ����Ʈ�� �̵� ���� ����
	bool linning;		//������ �׸� �� �ִ� ����
	CPoint line_start_pt;	//������ �׸��� ������

	CPoint mPoint;
	int startx;			//������ �ٽñ׸��� ������	(���콺���꿡�� ���)
	int starty;			
	int prevx;			//������ ������ �׷ȴ� ���� (���콺���꿡�� ���)
	int prevy;

	//����Ʈ �� ����� �ӽ÷� �������ִ� ����
	LogicUnit *selected;
	LogicUnit *selected_Input;
	LogicUnit *selected_Output;
	int selected_Input_Index;
	int selected_Output_Index;


	//�۾� �޼ҵ��
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

#ifndef _DEBUG  // Logic_Circuit_SimulatorView.cpp�� ����� ����
inline CLogic_Circuit_SimulatorDoc* CLogic_Circuit_SimulatorView::GetDocument() const
   { return reinterpret_cast<CLogic_Circuit_SimulatorDoc*>(m_pDocument); }
#endif

