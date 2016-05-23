
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
#include "resource.h"

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
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_32771, &CLogic_Circuit_SimulatorView::CreateInput)
	ON_COMMAND(ID_32772, &CLogic_Circuit_SimulatorView::CreateOutput)
	ON_COMMAND(ID_32773, &CLogic_Circuit_SimulatorView::CreateAND)
	ON_COMMAND(ID_32774, &CLogic_Circuit_SimulatorView::CreateOr)
	ON_COMMAND(ID_32775, &CLogic_Circuit_SimulatorView::CreateNot)
	ON_COMMAND(ID_32776, &CLogic_Circuit_SimulatorView::CreateNand)
	ON_COMMAND(ID_32777, &CLogic_Circuit_SimulatorView::CreateNor)
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

	move = false;

	return CView::PreCreateWindow(cs);
}

// CLogic_Circuit_SimulatorView 그리기

void CLogic_Circuit_SimulatorView::OnDraw(CDC* pDC)
{
	CLogic_Circuit_SimulatorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	CFont font;
	CBitmap bit;
	CPoint point(10, 10);
	POSITION pos;


	//클라이언트 영역에 점찍기
	CreatePoint(pDC);	



	pos = DrawList.GetHeadPosition(); //List의 헤더로 이동
	while (pos) {
		LogicUnit *temp = (LogicUnit*)DrawList.GetNext(pos); //클래스객체에 List의 다음 링크 데이터 받기( 클래스주소가 들어있음 )
		DrawUnit(pDC, temp->getPoint(), temp);
	}
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



void CLogic_Circuit_SimulatorView::CreatePoint(CDC* pDC) {

	CRect rect;

	int x, y;

	GetClientRect(&rect);

	y = rect.Height();
	x = rect.Width();


	for (int point_x = 10; point_x < x; point_x += 20) {
		for (int point_y = 10; point_y < y; point_y += 20) {
			pDC->Ellipse(point_x - 1, point_y - 1, point_x + 1, point_y + 1);
		}
	}
}

void CLogic_Circuit_SimulatorView::DrawUnit(CDC* pDC, CPoint pt, LogicUnit *unit) {


	CClientDC dc(this);
	CRect rect;
	CBitmap bit;
	BITMAP bminfo;
	CDC memDC;  //메모리 dc(장치와 연결되어 있지 않은 dc)
	CPoint point(pt);

	memDC.CreateCompatibleDC(pDC);

	if (unit->isType(InputSwitch_type)) {

		bit.LoadBitmapW(IDB_OnSwitch);
		bit.GetBitmap(&bminfo);
		memDC.SelectObject(&bit);

		CPoint point2(point.x + 40, point.y + 40);

		pDC->StretchBlt( //비트맵을 1:1로 출력
			point.x, point.y, 20, 20,   //비트맵이 출력될 client 영역
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//메모리 dc가 선택한 비트맵 좌측상단 x,y 부터 출력
			SRCCOPY  //비트맵을 목적지에 기존 내용위에 복사
			);
	}
	if (unit->isType(OutputSwitch_type)) {

		bit.LoadBitmapW(IDB_OnOUTPUT);
		bit.GetBitmap(&bminfo);
		memDC.SelectObject(&bit);

		CPoint point2(point.x + 40, point.y + 40);

		pDC->StretchBlt( //비트맵을 1:1로 출력
			point.x, point.y, 20, 20,   //비트맵이 출력될 client 영역
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//메모리 dc가 선택한 비트맵 좌측상단 x,y 부터 출력
			SRCCOPY  //비트맵을 목적지에 기존 내용위에 복사
			);
	}
	else if (unit->isType(AndGate_type)) {

		bit.LoadBitmapW(IDB_ANDGATE);
		bit.GetBitmap(&bminfo);
		memDC.SelectObject(&bit);

		CPoint point2(point.x + 40, point.y + 40);

		pDC->StretchBlt( //비트맵을 1:1로 출력
			point.x, point.y, 60, 80,   //비트맵이 출력될 client 영역
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//메모리 dc가 선택한 비트맵 좌측상단 x,y 부터 출력
			SRCCOPY  //비트맵을 목적지에 기존 내용위에 복사
			);

		pDC->MoveTo(pt.x, pt.y + 20);
		pDC->LineTo(pt.x - 20, pt.y + 20);

		pDC->MoveTo(pt.x, pt.y + 60);
		pDC->LineTo(pt.x - 20, pt.y + 60);


		pDC->MoveTo(pt.x + 60, pt.y + 40);
		pDC->LineTo(pt.x + 80, pt.y + 40);

	}
	else if (unit->isType(OrGate_type)) {

		bit.LoadBitmapW(IDB_ORGATE);
		bit.GetBitmap(&bminfo);
		memDC.SelectObject(&bit);

		CPoint point2(point.x + 40, point.y + 40);

		pDC->StretchBlt( //비트맵을 1:1로 출력
			point.x, point.y, 60, 80,   //비트맵이 출력될 client 영역
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//메모리 dc가 선택한 비트맵 좌측상단 x,y 부터 출력
			SRCCOPY  //비트맵을 목적지에 기존 내용위에 복사
			);
	}
	else if (unit->isType(NotGate_type)) {

		bit.LoadBitmapW(IDB_NOTGATE);
		bit.GetBitmap(&bminfo);
		memDC.SelectObject(&bit);

		CPoint point2(point.x + 40, point.y + 40);

		pDC->StretchBlt( //비트맵을 1:1로 출력
			point.x, point.y, 60, 80,   //비트맵이 출력될 client 영역
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//메모리 dc가 선택한 비트맵 좌측상단 x,y 부터 출력
			SRCCOPY  //비트맵을 목적지에 기존 내용위에 복사
		);

		pDC->MoveTo(pt.x, pt.y + 20);
		pDC->LineTo(pt.x - 20, pt.y + 20);

		pDC->MoveTo(pt.x, pt.y + 60);
		pDC->LineTo(pt.x - 20, pt.y + 60);


		pDC->MoveTo(pt.x + 60, pt.y + 40);
		pDC->LineTo(pt.x + 80, pt.y + 40);
		
	}
	else if (unit->isType(NandGate_type)) {

		bit.LoadBitmapW(IDB_NANDGATE);
		bit.GetBitmap(&bminfo);
		memDC.SelectObject(&bit);

		CPoint point2(point.x + 40, point.y + 40);

		pDC->StretchBlt( //비트맵을 1:1로 출력
			point.x, point.y, 60, 80,   //비트맵이 출력될 client 영역
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//메모리 dc가 선택한 비트맵 좌측상단 x,y 부터 출력
			SRCCOPY  //비트맵을 목적지에 기존 내용위에 복사
		);

		pDC->MoveTo(pt.x, pt.y + 20);
		pDC->LineTo(pt.x - 20, pt.y + 20);

		pDC->MoveTo(pt.x, pt.y + 60);
		pDC->LineTo(pt.x - 20, pt.y + 60);


		pDC->MoveTo(pt.x + 60, pt.y + 40);
		pDC->LineTo(pt.x + 80, pt.y + 40);

	}
	else if (unit->isType(NorGate_type)) 
	{

		bit.LoadBitmapW(IDB_NORGATE);
		bit.GetBitmap(&bminfo);
		memDC.SelectObject(&bit);

		CPoint point2(point.x + 40, point.y + 40);

		pDC->StretchBlt( //비트맵을 1:1로 출력
			point.x, point.y, 60, 80,   //비트맵이 출력될 client 영역
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//메모리 dc가 선택한 비트맵 좌측상단 x,y 부터 출력
			SRCCOPY  //비트맵을 목적지에 기존 내용위에 복사
		);

		/*
		pDC->MoveTo(pt.x, pt.y + 20);
		pDC->LineTo(pt.x - 20, pt.y + 20);

		pDC->MoveTo(pt.x, pt.y + 60);
		pDC->LineTo(pt.x - 20, pt.y + 60);


		pDC->MoveTo(pt.x + 60, pt.y + 40);
		pDC->LineTo(pt.x + 80, pt.y + 40);
		*/

	}
}

bool CLogic_Circuit_SimulatorView::CheckIn(CPoint point) {

	POSITION pos;
	startx = point.x;
	starty = point.y;

	current = NULL;

	pos = DrawList.GetHeadPosition(); //List의 헤더로 이동

	while (pos) {

		current = pos;
		LogicUnit *temp;
		temp = (LogicUnit *)DrawList.GetNext(pos);


		if (temp->getPoint().x <= point.x && point.x <= temp->getPoint().x + temp->ImageSize.x ||
			temp->getPoint().x + temp->ImageSize.x <= point.x && point.x <= temp->getPoint().x) {

			if (temp->getPoint().y <= point.y && point.y <= temp->getPoint().y + temp->ImageSize.y ||
				temp->getPoint().y + temp->ImageSize.y <= point.y && point.y <= temp->getPoint().y) {

				move = true;
				return true;
			}
		}


	}



}



void CLogic_Circuit_SimulatorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnLButtonDown(nFlags, point);

	CheckIn(point);
}


void CLogic_Circuit_SimulatorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnLButtonUp(nFlags, point);


	move = false;
}


void CLogic_Circuit_SimulatorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnMouseMove(nFlags, point);

	if (nFlags & MK_LBUTTON == 1 && current != NULL) {

		if (move)
		{
			LogicUnit *temp;
			POINT pt;
			temp = (LogicUnit *)DrawList.GetAt(current);

			pt = temp->getPoint();

			// 이동
			pt.x += point.x - startx;
			pt.y += point.y - starty;

			startx = point.x;
			starty = point.y;

			temp->setPoint(pt);

			Invalidate();
		}

		/*
		if (move == false) {

		CClientDC dc(this);
		dc.SelectStockObject(NULL_BRUSH);
		dc.SetROP2(R2_NOT);

		dc.Rectangle(boxes[current].left, boxes[current].top, boxes[current].right, boxes[current].bottom);

		// 크기 변경
		boxes[current].right = point.x;
		boxes[current].bottom = point.y;

		dc.Rectangle(boxes[current].left, boxes[current].top, boxes[current].right, boxes[current].bottom);

		}
		*/
	}
}


void CLogic_Circuit_SimulatorView::CreateInput()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	InputSwitch *in1 = new InputSwitch(CPoint(10, 10));

	in1->setOutput(0, true);

	DrawList.AddHead(in1);

	Invalidate();
}


void CLogic_Circuit_SimulatorView::CreateOutput()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	OutputSwitch *in1 = new OutputSwitch(CPoint(10, 10));

	DrawList.AddHead(in1);

	Invalidate();
}


void CLogic_Circuit_SimulatorView::CreateAND()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	AndGate *in1 = new AndGate(CPoint(10, 10));

	DrawList.AddHead(in1);

	Invalidate();
}


void CLogic_Circuit_SimulatorView::CreateOr()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	OrGate *in1 = new OrGate(CPoint(10, 10));

	DrawList.AddHead(in1);

	Invalidate();
}

void CLogic_Circuit_SimulatorView::CreateNot()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	NotGate *in1 = new NotGate(CPoint(10, 10));

	DrawList.AddHead(in1);

	Invalidate();
}


void CLogic_Circuit_SimulatorView::CreateNand()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	NANDGate *in1 = new NANDGate(CPoint(10, 10));

	DrawList.AddHead(in1);

	Invalidate();
}


void CLogic_Circuit_SimulatorView::CreateNor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	NorGate *in1 = new NorGate(CPoint(10, 10));

	DrawList.AddHead(in1);

	Invalidate();
}
