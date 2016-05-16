
// Logic_Circuit_SimulatorView.cpp : CLogic_Circuit_SimulatorView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Logic_Circuit_Simulator.h"
#endif

#include "Logic_Circuit_SimulatorDoc.h"
#include "Logic_Circuit_SimulatorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLogic_Circuit_SimulatorView

IMPLEMENT_DYNCREATE(CLogic_Circuit_SimulatorView, CView)

BEGIN_MESSAGE_MAP(CLogic_Circuit_SimulatorView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CLogic_Circuit_SimulatorView 생성/소멸

CLogic_Circuit_SimulatorView::CLogic_Circuit_SimulatorView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CLogic_Circuit_SimulatorView::~CLogic_Circuit_SimulatorView()
{
}

BOOL CLogic_Circuit_SimulatorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CLogic_Circuit_SimulatorView 그리기

void CLogic_Circuit_SimulatorView::OnDraw(CDC* /*pDC*/)
{
	CLogic_Circuit_SimulatorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CLogic_Circuit_SimulatorView 인쇄

BOOL CLogic_Circuit_SimulatorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CLogic_Circuit_SimulatorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CLogic_Circuit_SimulatorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CLogic_Circuit_SimulatorView 진단

#ifdef _DEBUG
void CLogic_Circuit_SimulatorView::AssertValid() const
{
	CView::AssertValid();
}

void CLogic_Circuit_SimulatorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLogic_Circuit_SimulatorDoc* CLogic_Circuit_SimulatorView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLogic_Circuit_SimulatorDoc)));
	return (CLogic_Circuit_SimulatorDoc*)m_pDocument;
}
#endif //_DEBUG


// CLogic_Circuit_SimulatorView 메시지 처리기
