#pragma once
#include "MainFrm.h"

// CMyTreeView 뷰입니다.

class CMyTreeView : public CTreeView
{
	DECLARE_DYNCREATE(CMyTreeView)

protected:
	CMyTreeView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CMyTreeView();

public:
	HTREEITEM hGate[4];
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};


