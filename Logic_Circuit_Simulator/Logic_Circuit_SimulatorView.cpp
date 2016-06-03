
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
#include "MainFrm.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 
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
	ON_COMMAND(ID_32782, &CLogic_Circuit_SimulatorView::CreateXor)
	ON_COMMAND(ID_32783, &CLogic_Circuit_SimulatorView::CreateDFF)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_TIMER()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_32784, &CLogic_Circuit_SimulatorView::OnLabel)
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

	linning = move = false;
	selected_Input = NULL;
	selected_Output = NULL;
	selected_Input_Index = -1;
	selected_Output_Index = -1;
	prevx = prevy = -1;

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

	pos = LineList.GetHeadPosition();
	while (pos) {
		LineUnit *temp = (LineUnit *)DrawList.GetNext(pos); //클래스객체에 List의 다음 링크 데이터 받기( 클래스주소가 들어있음 )

		point = temp->getPoint();
		pDC->MoveTo(point);
		pDC->LineTo(temp->endPoint);

		pDC->Ellipse(point.x - 5, point.y - 5, point.x + 5, point.y + 5);
		pDC->Ellipse(temp->endPoint.x - 5, temp->endPoint.y - 5, temp->endPoint.x + 5, temp->endPoint.y + 5);

	}

	pos = DrawList.GetTailPosition(); //List의 헤더로 이동
	while (pos) {
		LogicUnit *temp = (LogicUnit*)DrawList.GetPrev(pos); //클래스객체에 List의 다음 링크 데이터 받기( 클래스주소가 들어있음 )
		if (temp->isType(OutputSwitch_type) == true) {
			((OutputSwitch*)temp)->updateOutput();
		}
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


//클라이언트 영역에 점찍기.
void CLogic_Circuit_SimulatorView::CreatePoint(CDC* pDC) {
	CRect rect;
	int x, y;

	GetClientRect(&rect);
	y = rect.Height();
	x = rect.Width();

	for (int point_x = 20; point_x < x; point_x += 20) {
		for (int point_y = 20; point_y < y; point_y += 20) {
			pDC->Ellipse(point_x - 1, point_y - 1, point_x + 1, point_y + 1);
		}
	}
}

//리스트에 담긴 객체를 전달받아 타입에따라 그려주기
void CLogic_Circuit_SimulatorView::DrawUnit(CDC* pDC, CPoint pt, LogicUnit *unit) {
	CClientDC dc(this);
	CRect rect;
	CBitmap bit;
	BITMAP bminfo;
	CDC memDC;  //메모리 dc(장치와 연결되어 있지 않은 dc)
	CPoint point(pt);

	memDC.CreateCompatibleDC(pDC);

	if (unit->isType(InputSwitch_type)) {

		if (unit->getOutput(0) == true)
			bit.LoadBitmapW(IDB_OffSwitch);
		else
			bit.LoadBitmapW(IDB_OnSwitch);
		bit.GetBitmap(&bminfo);
		memDC.SelectObject(&bit);

		pDC->StretchBlt( //비트맵을 1:1로 출력
			point.x, point.y, 40, 40,   //비트맵이 출력될 client 영역
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//메모리 dc가 선택한 비트맵 좌측상단 x,y 부터 출력
			SRCCOPY  //비트맵을 목적지에 기존 내용위에 복사
			);

		pDC->MoveTo(pt.x + 40, pt.y + 20);
		pDC->LineTo(pt.x + 60, pt.y + 20);
	}
	if (unit->isType(OutputSwitch_type))
	{
		if (unit->getCurrentInput() == 1)
			unit->setInput(0, (unit->getInputList(0))->getOutput(0));


		if (unit->getInput(0) == true)
			bit.LoadBitmapW(IDB_OnOUTPUT);
		else
			bit.LoadBitmapW(IDB_OffOUTPUT);
		bit.GetBitmap(&bminfo);
		memDC.SelectObject(&bit);

		pDC->StretchBlt( //비트맵을 1:1로 출력
			point.x, point.y, 40, 40,   //비트맵이 출력될 client 영역
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//메모리 dc가 선택한 비트맵 좌측상단 x,y 부터 출력
			SRCCOPY  //비트맵을 목적지에 기존 내용위에 복사
			);

		pDC->MoveTo(pt.x, pt.y + 20);
		pDC->LineTo(pt.x - 20, pt.y + 20);
	}
	else if (unit->isType(AndGate_type)) {
		((AndGate*)unit)->Op();

		bit.LoadBitmapW(IDB_ANDGATE);
		bit.GetBitmap(&bminfo);
		memDC.SelectObject(&bit);

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
		((OrGate*)unit)->Op();

		bit.LoadBitmapW(IDB_ORGATE);
		bit.GetBitmap(&bminfo);
		memDC.SelectObject(&bit);

		pDC->StretchBlt( //비트맵을 1:1로 출력
			point.x, point.y, 60, 80,   //비트맵이 출력될 client 영역
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//메모리 dc가 선택한 비트맵 좌측상단 x,y 부터 출력
			SRCCOPY  //비트맵을 목적지에 기존 내용위에 복사
			);

		pDC->MoveTo(pt.x+8, pt.y + 20);
		pDC->LineTo(pt.x - 20, pt.y + 20);
		pDC->MoveTo(pt.x +8, pt.y + 60);
		pDC->LineTo(pt.x - 20, pt.y + 60);
		pDC->MoveTo(pt.x + 60, pt.y + 40);
		pDC->LineTo(pt.x + 80, pt.y + 40);
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

		
		pDC->MoveTo(pt.x, pt.y + 20);
		pDC->LineTo(pt.x - 20, pt.y + 20);
		pDC->MoveTo(pt.x + 8, pt.y + 60);
		pDC->LineTo(pt.x - 20, pt.y + 60);
		pDC->MoveTo(pt.x + 60, pt.y + 40);
		pDC->LineTo(pt.x + 80, pt.y + 40);
	}
	else if (unit->isType(XorGate_type))
	{

		bit.LoadBitmapW(IDB_XORGATE);
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


}

bool CLogic_Circuit_SimulatorView::CheckIn(CPoint point) {
	POSITION pos;
	CPoint temp_point;

	current = NULL;

	startx = point.x;
	starty = point.y;

	pos = DrawList.GetHeadPosition(); //List의 헤더로 이동
	temp_point = point;

	while (pos) {
		current = pos;
		point = temp_point;
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

	current = NULL;
	return false;
}

//근처의 점을 찾아 좌표를 리턴
CPoint CLogic_Circuit_SimulatorView::Nearby_point(CPoint pt) {
	
	CPoint leftUP_point;
	int temp_x = 0;
	int temp_y = 0;
	int i=0;

	//근처에서 제일 가까운 왼쪽-위 점을 찾아냄
	while (1) {
		i = pt.x - temp_x;
		if (i < 20)
			break;
		temp_x = temp_x + 20;
	}

	i = 0;
	while (1) {
		i = pt.y - temp_y;
		if (i < 20)
			break;
		temp_y = temp_y + 20;
	}
	//====================================

	leftUP_point.x = temp_x;
	leftUP_point.y = temp_y;

	//왼쪽위 점을 기준으로 마우스가 어느점에서 가까운지 비교
	if ((pt.x - leftUP_point.x) <= 10) {
		if ((pt.y - leftUP_point.y) <= 10)
			return leftUP_point;
		else {
			leftUP_point.y += 20;
			return leftUP_point;
}
	}
	else {
		leftUP_point.x += 20;

		if ((pt.y - leftUP_point.y) <= 10) {
			return leftUP_point;
		}
		else {
			leftUP_point.y += 20;
			return leftUP_point;
		}
	}
	//=====================================================
}

//입력받은 유닛으로부터 후로 연결된 것들을 업데이트 시켜줌
void CLogic_Circuit_SimulatorView::newUpdate(LogicUnit *unit) {
	this->stack = new unitStack[this->DrawList.GetSize()];
	this->stack_count = 0;
	/*
	for (int i = 0; i < this->DrawList.GetSize(); i++) {
		stack[i].unit = NULL;
		stack[i].prev = -1;
	}

	unit->Op();

	for (int i = 0; i < unit->getCurrentOutput(); i++) {

		if (stack[0].unit == NULL) {
			stack[0].unit = unit->getOutputList[i];
			stack[0].prev = unit->getOutput(i);
		}
		else if (stack[0].prev != unit->getOutput(i)) {


		}


	}
	*/
}

void CLogic_Circuit_SimulatorView::Update(LogicUnit *unit) {
	unit->Op();


}

//현재 클릭지점(point)가 어떤 게이트의 몇번째 입력지점인지 리턴해주고 isInput에 입력이면 true, 출력지점이면 false 
int CLogic_Circuit_SimulatorView::search_unit(CPoint point, bool &isInput) {
	POSITION pos;
	CPoint pt;
	int result;;
	current = NULL;

	pos = DrawList.GetHeadPosition(); //List의 헤더로 이동

	while (pos) {
		current = pos;
		LogicUnit *temp;
		temp = (LogicUnit *)DrawList.GetNext(pos);

		//인풋이나 아웃풋쪽에 있는지 확인
		pt = Nearby_point(point);					//마우스 포인터의 가까운 점을 구함.
		result = temp->get_putIndex(pt,isInput);	//가까운점이 input점에 있는지 확인.
		if (result != -1) {
			return result;	//구한 연결점의 인덱스를 리턴해줌
		}
	}

	current = NULL;
	return -1;
}

void CLogic_Circuit_SimulatorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);
	LogicUnit* temp;
	int result;
	bool isInput = false;

	//빈공간에 클릭이 됨
	if (CheckIn(point) == false && (selected_Input == NULL || selected_Output == NULL)) {
		//혹시 유닛의 인풋이나 아웃풋쪽에 클릭이 됬는지 확인
		result = search_unit(point, isInput);

		//찾은값이 있을경우
		if (result != -1) {
			temp = (LogicUnit*)DrawList.GetAt(current);
			CPoint pt;
			pt = Nearby_point(point);

			//신호를 쏘는곳
			if (isInput != true && selected_Input == NULL) {
				dc.Ellipse(pt.x - 5, pt.y - 5, pt.x + 5, pt.y + 5);
				selected_Input = temp;
				selected_Input_Index = result;
			}
			//신호를 받는곳
			else if (isInput == true && selected_Output == NULL) {
				dc.Ellipse(pt.x - 5, pt.y - 5, pt.x + 5, pt.y + 5);
				selected_Output = temp;
				selected_Output_Index = result;
			}
		}
		//빈영역에 선택된경우
		else {
			//분기를 만들어 선을 그려주기 추가 부분
			
		}


		//현재 클릭된 좌표점부터 선 그리기 신호 추가.
		if (linning) {
			LineUnit* line;

			//선 양쪽점 모두 게이트로 선택이 되었을경우 연결을 시켜줌
			if (selected_Input != NULL && selected_Output != NULL) {
				dc.MoveTo((selected_Input->output_pt)[selected_Input_Index].x, (selected_Input->output_pt)[selected_Input_Index].y);
				dc.LineTo((selected_Output->input_pt)[selected_Output_Index].x, (selected_Output->input_pt)[selected_Output_Index].y);

				line = new LineUnit((selected_Input->output_pt)[selected_Input_Index], (selected_Output->input_pt)[selected_Output_Index]);

				LogicUnit::connect_line(line, selected_Input, selected_Input_Index, selected_Output, selected_Output_Index);
			}
			//신호를 쏘는것만 연결됬을때
			else if (selected_Input != NULL) {
				dc.MoveTo((selected_Input->output_pt)[selected_Input_Index].x, (selected_Input->output_pt)[selected_Input_Index].y);
				dc.LineTo(Nearby_point(point));

				line = new LineUnit((selected_Input->output_pt)[selected_Input_Index], Nearby_point(point));

				LogicUnit::connect_Unit(selected_Input, selected_Input_Index, line, 0);
			}
			//신호를 받는것만 연결됬을때
			else if (selected_Output != NULL) {
				dc.MoveTo(line_start_pt);
				dc.LineTo(Nearby_point(point));

				line = new LineUnit(line_start_pt, Nearby_point(point));

				LogicUnit::connect_Unit(line, 0, selected_Output, selected_Output_Index);
			}
			else if (selected_Input == NULL && selected_Output == NULL) {
				dc.MoveTo(line_start_pt);
				dc.LineTo(Nearby_point(point));

				line = new LineUnit(line_start_pt, Nearby_point(point));
			}
				LineList.AddHead(line);

				selected_Input = NULL;
				selected_Output = NULL;

			linning = false;
}
		else {
			linning = true;
			line_start_pt = Nearby_point(point);
		}
	}
	//빈공간이 아닐경우?
	else if(selected_Input != NULL || selected_Output != NULL)
	{
		selected_Input = selected_Output = NULL;
	}
	CView::OnLButtonDown(nFlags, point);
}

void CLogic_Circuit_SimulatorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);
	LogicUnit *temp;
	if (current != NULL) {
		if (move) {
			CPoint pt;
			temp = (LogicUnit *)DrawList.GetAt(current);

			//기준점		
			pt = Nearby_point(temp->getPoint());

			temp->setPoint(pt);
			temp->setPut_point(pt);

		}
	}
	else {
		//인풋 아웃풋 좌표 확인
	}
	move = false;

	Invalidate();
	
	CView::OnLButtonUp(nFlags, point);
}

void CLogic_Circuit_SimulatorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnMouseMove(nFlags, point);
	CClientDC dc(this);
	mPoint.SetPoint(point.x, point.y);

	if (nFlags & MK_LBUTTON == 1 && current != NULL && linning != true) {
		//유닛 이동부분
		if (move)
		{
			LogicUnit *temp;

			CPoint pt;
			temp = (LogicUnit *)DrawList.GetAt(current);

			pt = temp->getPoint();

			// 이동
			pt.x += point.x - startx;
			pt.y += point.y - starty;

			startx = point.x;
			starty = point.y;

			temp->setPoint(pt);
			temp->setPut_point(pt);
			temp->label.pt.SetPoint(pt.x, pt.y - 40);

			Invalidate();
		}
	}
	//선 그려주기 부분
	else if (linning == true) {
		CPoint temp(startx,starty);
		dc.SelectStockObject(WHITE_PEN);

		temp = Nearby_point(temp);
		dc.MoveTo(temp);
		dc.LineTo(prevx, prevy);
		dc.Ellipse(prevx - 5, prevy - 5, prevx + 5, prevy + 5);

		dc.SelectStockObject(BLACK_PEN);

		dc.MoveTo(temp);
		temp = Nearby_point(CPoint(point.x,point.y));
		dc.LineTo(temp);
		dc.Ellipse(temp.x - 5, temp.y - 5, temp.x + 5, temp.y + 5);

		prevx = temp.x;
		prevy = temp.y;
	}
}

void CLogic_Circuit_SimulatorView::CreateInput()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	InputSwitch *in1 = new InputSwitch(CPoint(40, 40));

	in1->setOutput(0, true);

	DrawList.AddHead(in1);

	Invalidate();
}


void CLogic_Circuit_SimulatorView::CreateOutput()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	OutputSwitch *in1 = new OutputSwitch(CPoint(40, 40));

	DrawList.AddHead(in1);

	Invalidate();
}


void CLogic_Circuit_SimulatorView::CreateAND()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	AndGate *in1 = new AndGate(CPoint(40, 40));

	DrawList.AddHead(in1);

	Invalidate();
}


void CLogic_Circuit_SimulatorView::CreateOr()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	OrGate *in1 = new OrGate(CPoint(40, 40));

	DrawList.AddHead(in1);

	Invalidate();
}


void CLogic_Circuit_SimulatorView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	POSITION pos;
	CPoint temp_point;
	LogicUnit *temp;
	pos = DrawList.GetHeadPosition(); //List의 헤더로 이동

	temp_point = point;

	while (pos) {
		current = pos;		
		temp = (LogicUnit *)DrawList.GetNext(pos);

		if (temp->isType(InputSwitch_type) || temp->isType(OutputSwitch_type)) {
			if (temp->getPoint().x <= point.x && point.x <= temp->getPoint().x + temp->ImageSize.x ||
				temp->getPoint().x + temp->ImageSize.x <= point.x && point.x <= temp->getPoint().x) {

				if (temp->getPoint().y <= point.y && point.y <= temp->getPoint().y + temp->ImageSize.y ||
					temp->getPoint().y + temp->ImageSize.y <= point.y && point.y <= temp->getPoint().y) {
					((InputSwitch*)temp)->setSwitch();
				}
			}
		}
	}
	CView::OnLButtonDblClk(nFlags, point);
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


void CLogic_Circuit_SimulatorView::CreateXor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	XorGate *in1 = new XorGate(CPoint(10, 10));

	DrawList.AddHead(in1);

	Invalidate();
}


void CLogic_Circuit_SimulatorView::CreateDFF()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CLogic_Circuit_SimulatorView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnTimer(nIDEvent);
}


void CLogic_Circuit_SimulatorView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CMenu menu;
	menu.LoadMenu(IDR_MENU1);

	if (CheckIn(this->mPoint) == true){
		CMenu *pMenu = menu.GetSubMenu(0);
		pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
	}

}


void CLogic_Circuit_SimulatorView::OnLabel()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CClientDC dc(this);
	LogicUnit *temp;
	temp = (LogicUnit *)DrawList.GetNext(current);

	temp->onLabelName(dc);
}
