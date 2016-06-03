#pragma once
#include "MainFrm.h"

// CMyTreeView ���Դϴ�.

class CMyTreeView : public CTreeView
{
	DECLARE_DYNCREATE(CMyTreeView)

protected:
	CMyTreeView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
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


