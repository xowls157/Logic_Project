
// Logic_Circuit_SimulatorView.h : CLogic_Circuit_SimulatorView Ŭ������ �������̽�
//

#pragma once


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
};

#ifndef _DEBUG  // Logic_Circuit_SimulatorView.cpp�� ����� ����
inline CLogic_Circuit_SimulatorDoc* CLogic_Circuit_SimulatorView::GetDocument() const
   { return reinterpret_cast<CLogic_Circuit_SimulatorDoc*>(m_pDocument); }
#endif

