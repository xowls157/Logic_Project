
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

#include<iostream>

using namespace std;

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
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_FILE_NEW, &CLogic_Circuit_SimulatorView::OnFileNew)
	ON_COMMAND(ID_ROTATE, &CLogic_Circuit_SimulatorView::OnRotate)
	ON_COMMAND(ID_GATECOPY, &CLogic_Circuit_SimulatorView::OnGatecopy)
	ON_COMMAND(ID_GATECUT, &CLogic_Circuit_SimulatorView::OnGatecut)
	ON_COMMAND(ID_PASTE, &CLogic_Circuit_SimulatorView::OnPaste)
	ON_COMMAND(ID_Delete, &CLogic_Circuit_SimulatorView::OnDelete)
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
	selected = NULL;
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
	CPen pen;
	CFont font;
	CBitmap bit;
	CPoint point(10, 10);
	POSITION pos;
	pen.CreatePen(BS_SOLID, 5, RGB(0, 0, 255));
	
	SetTimer(0, 1000, 0);

	//클라이언트 영역에 점찍기
	CreatePoint(pDC);	

	pos = LineList.GetHeadPosition();
	while (pos) {
		LineUnit *temp = (LineUnit *)DrawList.GetNext(pos); //클래스객체에 List의 다음 링크 데이터 받기( 클래스주소가 들어있음 )

		point = temp->getPoint();
		pDC->MoveTo(point);

		if (temp->isType(Branch_type) == false) {
			
			if (temp == selected) {
				CPen *old = pDC->SelectObject(&pen);
				pDC->LineTo(temp->endPoint);
				pDC->SelectObject(old);
			}
			else {
				pDC->LineTo(temp->endPoint);
			}
			pDC->Ellipse(point.x - 5, point.y - 5, point.x + 5, point.y + 5);
			pDC->Ellipse(temp->endPoint.x - 5, temp->endPoint.y - 5, temp->endPoint.x + 5, temp->endPoint.y + 5);
		}
		else {
			pDC->SelectStockObject(BLACK_BRUSH);
			pDC->Rectangle(point.x - 5, point.y - 5, point.x + 5, point.y + 5);
			pDC->SelectStockObject(NULL_BRUSH);
		}

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
	CRect rect;
	CBitmap bit;
	BITMAP bminfo;
	CDC memDC;  //메모리 dc(장치와 연결되어 있지 않은 dc)
	CPoint point(pt);
	CPoint temp_pt, *prev_pt;
	CPoint temp_image = unit->ImageSize;
	int dir_int = (int)unit->getDirction();


	for (int i = 0; i < (int)unit->getDirction(); i++) {
		int temp_size = unit->ImageSize.y;
		unit->ImageSize.y = unit->ImageSize.x;
		unit->ImageSize.x = temp_size;
	}


	memDC.CreateCompatibleDC(pDC);

	if (unit->isType(InputSwitch_type)) 
	{

		if (unit->getOutput(0) == true)
			bit.LoadBitmapW(IDB_OffSwitch);
		else
			bit.LoadBitmapW(IDB_OnSwitch);
		bit.GetBitmap(&bminfo);
		memDC.SelectObject(&bit);

		pDC->StretchBlt( //비트맵을 1:1로 출력
			point.x, point.y, unit->ImageSize.x, unit->ImageSize.y,   //비트맵이 출력될 client 영역
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//메모리 dc가 선택한 비트맵 좌측상단 x,y 부터 출력
			SRCCOPY  //비트맵을 목적지에 기존 내용위에 복사
			);

		//입출력점부터 이미지까지의 거리.
		switch (unit->getDirction()) {
		case EAST: {
			temp_pt.SetPoint(-20, 0);
			break;
		}case NORTH: {
			temp_pt.SetPoint(0, 20);
			break;
		}case WEST: {
			temp_pt.SetPoint(20, 0);
			break;
		}case SOUTH: {
			temp_pt.SetPoint(0, -20);
			break;
		}
		}
		pDC->MoveTo(unit->output_pt[0]);
		pDC->LineTo(unit->output_pt[0].x + temp_pt.x, unit->output_pt[0].y + temp_pt.y);

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
			point.x, point.y, unit->ImageSize.x, unit->ImageSize.y,   //비트맵이 출력될 client 영역
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//메모리 dc가 선택한 비트맵 좌측상단 x,y 부터 출력
			SRCCOPY  //비트맵을 목적지에 기존 내용위에 복사
			);

		//입출력점부터 이미지까지의 거리.
		switch (unit->getDirction()) {
		case EAST: {
			temp_pt.SetPoint(-20, 0);
			break;
		}case NORTH: {
			temp_pt.SetPoint(0, 20);
			break;
		}case WEST: {
			temp_pt.SetPoint(20, 0);
			break;
		}case SOUTH: {
			temp_pt.SetPoint(0, -20);
			break;
		}
		}
		pDC->MoveTo(unit->input_pt[0]);
		pDC->LineTo(unit->input_pt[0].x + temp_pt.x, unit->input_pt[0].y + temp_pt.y);
	}
	else if (unit->isType(Segment_type)) {

		bit.LoadBitmapW(IDB_SEGMENT);
		bit.GetBitmap(&bminfo);
		memDC.SelectObject(&bit);

		pDC->StretchBlt( //비트맵을 1:1로 출력
			point.x, point.y, unit->ImageSize.x, unit->ImageSize.y,   //비트맵이 출력될 client 영역
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//메모리 dc가 선택한 비트맵 좌측상단 x,y 부터 출력
			SRCCOPY  //비트맵을 목적지에 기존 내용위에 복사
			);
		Segment *seg = (Segment*)unit;
		CClientDC dc(this);
		seg->updateOutput();
		temp_pt.SetPoint(point.x + 10, point.y + 10);

		seg->drawNumber(seg->Number, temp_pt, pDC);
		seg->acivateSegment(seg->Number, dc);

		for (int i = 0; i < unit->getMaxInput(); i++) {
			pDC->MoveTo(unit->input_pt[i]);

			if (unit->input_pt[i].x - unit->getPoint().x >= 0 && unit->input_pt[i].y - unit->getPoint().y >= 0)
				if (unit->input_pt[i].x - unit->getPoint().x > unit->ImageSize.x)
					temp_pt.SetPoint(-20, 0);
				else
					temp_pt.SetPoint(0, -20);
			else if (unit->input_pt[i].x - unit->getPoint().x < 0)
				temp_pt.SetPoint(20, 0);
			else if (unit->input_pt[i].y - unit->getPoint().y < 0)
				temp_pt.SetPoint(0, 20);

			pDC->LineTo(unit->input_pt[i].x + temp_pt.x, unit->input_pt[i].y + temp_pt.y);
		}

	}
	else if (unit->isType(AndGate_type)) {

		switch (unit->getDirction()) {
		case EAST: {
			temp_pt.SetPoint(-20, 0);
			bit.LoadBitmapW(IDB_ANDGATE);
			break;
		}case NORTH: {
			temp_pt.SetPoint(0, 20);
			bit.LoadBitmapW(IDB_ANDGATE2);
			break;
		}case WEST: {
			temp_pt.SetPoint(20, 0);
			bit.LoadBitmapW(IDB_ANDGATE3);
			break;
		}case SOUTH: {
			temp_pt.SetPoint(0, -20);
			bit.LoadBitmapW(IDB_ANDGATE4);
			break;
		}
		}
		bit.GetBitmap(&bminfo);
		memDC.SelectObject(&bit);

		pDC->StretchBlt( //비트맵을 1:1로 출력
			point.x, point.y, unit->ImageSize.x, unit->ImageSize.y,   //비트맵이 출력될 client 영역
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//메모리 dc가 선택한 비트맵 좌측상단 x,y 부터 출력
			SRCCOPY  //비트맵을 목적지에 기존 내용위에 복사
			);


		for (int i = 0; i<unit->getMaxOutput(); i++) {
			pDC->MoveTo(unit->output_pt[i]);
			pDC->LineTo(unit->output_pt[i].x + temp_pt.x, unit->output_pt[i].y + temp_pt.y);
		}

		switch (unit->getDirction()) {
		case EAST: {
			temp_pt.SetPoint(20, 0);
			break;
		}case NORTH: {
			temp_pt.SetPoint(0, -20);
			break;
		}case WEST: {
			temp_pt.SetPoint(-20, 0);
			break;
		}case SOUTH: {
			temp_pt.SetPoint(0, 20);
			break;
		}
		}

		for (int i = 0; i<unit->getMaxInput(); i++) {
			pDC->MoveTo(unit->input_pt[i]);
			pDC->LineTo(unit->input_pt[i].x + temp_pt.x, unit->input_pt[i].y + temp_pt.y);
		}
	}
	else if (unit->isType(OrGate_type)) {

		switch (unit->getDirction()) {
		case EAST: {
			temp_pt.SetPoint(-20, 0);
			bit.LoadBitmapW(IDB_ORGATE);
			break;
		}case NORTH: {
			temp_pt.SetPoint(0, 20);
			bit.LoadBitmapW(IDB_ORGATE1);
			break;
		}case WEST: {
			temp_pt.SetPoint(20, 0);
			bit.LoadBitmapW(IDB_ORGATE2);
			break;
		}case SOUTH: {
			temp_pt.SetPoint(0, -20);
			bit.LoadBitmapW(IDB_ORGATE3);
			break;
		}
		}
		bit.GetBitmap(&bminfo);
		memDC.SelectObject(&bit);

		pDC->StretchBlt( //비트맵을 1:1로 출력
			point.x, point.y, unit->ImageSize.x, unit->ImageSize.y,   //비트맵이 출력될 client 영역
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//메모리 dc가 선택한 비트맵 좌측상단 x,y 부터 출력
			SRCCOPY  //비트맵을 목적지에 기존 내용위에 복사
			);


		for (int i = 0; i<unit->getMaxOutput(); i++) {
			pDC->MoveTo(unit->output_pt[i]);
			pDC->LineTo(unit->output_pt[i].x + temp_pt.x, unit->output_pt[i].y + temp_pt.y);
		}

		switch (unit->getDirction()) {
		case EAST: {
			temp_pt.SetPoint(20, 0);
			break;
		}case NORTH: {
			temp_pt.SetPoint(0, -20);
			break;
		}case WEST: {
			temp_pt.SetPoint(-20, 0);
			break;
		}case SOUTH: {
			temp_pt.SetPoint(0, 20);
			break;
		}
		}

		for (int i = 0; i<unit->getMaxInput(); i++) {
			pDC->MoveTo(unit->input_pt[i]);
			pDC->LineTo(unit->input_pt[i].x + temp_pt.x, unit->input_pt[i].y + temp_pt.y);
		}
	}
	else if (unit->isType(NotGate_type)) {
		switch (unit->getDirction()) {
		case EAST: {
			temp_pt.SetPoint(-20, 0);

			bit.LoadBitmapW(IDB_NOTGATE);
			break;
		}case NORTH: {
			temp_pt.SetPoint(0, 20);

			bit.LoadBitmapW(IDB_NOTGATE1);
			break;
		}case WEST: {
			temp_pt.SetPoint(20, 0);

			bit.LoadBitmapW(IDB_NOTGATE2);
			break;
		}case SOUTH: {
			temp_pt.SetPoint(0, -20);

			bit.LoadBitmapW(IDB_NOTGATE3);
			break;
		}
		}
		bit.GetBitmap(&bminfo);
		memDC.SelectObject(&bit);

		CPoint point2(point.x + 40, point.y + 40);

		pDC->StretchBlt( //비트맵을 1:1로 출력
			point.x, point.y, unit->ImageSize.x, unit->ImageSize.y,   //비트맵이 출력될 client 영역
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//메모리 dc가 선택한 비트맵 좌측상단 x,y 부터 출력
			SRCCOPY  //비트맵을 목적지에 기존 내용위에 복사
			);

		for (int i = 0; i<unit->getMaxOutput(); i++) {
			pDC->MoveTo(unit->output_pt[i]);
			pDC->LineTo(unit->output_pt[i].x + temp_pt.x, unit->output_pt[i].y + temp_pt.y);
		}

		switch (unit->getDirction()) {
		case EAST: {
			temp_pt.SetPoint(20, 0);
			break;
		}case NORTH: {
			temp_pt.SetPoint(0, -20);
			break;
		}case WEST: {
			temp_pt.SetPoint(-20, 0);
			break;
		}case SOUTH: {
			temp_pt.SetPoint(0, 20);
			break;
		}
		}

		for (int i = 0; i<unit->getMaxInput(); i++) {
			pDC->MoveTo(unit->input_pt[i]);
			pDC->LineTo(unit->input_pt[i].x + temp_pt.x, unit->input_pt[i].y + temp_pt.y);
		}

	}
	else if (unit->isType(NandGate_type)) {
		switch (unit->getDirction()) {
		case EAST: {
			temp_pt.SetPoint(-20, 0);
			bit.LoadBitmapW(IDB_NANDGATE);
			break;
		}case NORTH: {
			temp_pt.SetPoint(0, 20);
			bit.LoadBitmapW(IDB_NANDGATE1);
			break;
		}case WEST: {
			temp_pt.SetPoint(20, 0);
			bit.LoadBitmapW(IDB_NANDGATE2);
			break;
		}case SOUTH: {
			temp_pt.SetPoint(0, -20);
			bit.LoadBitmapW(IDB_NANDGATE3);
			break;
		}
		}
		bit.GetBitmap(&bminfo);
		memDC.SelectObject(&bit);
		CPoint point2(point.x + 40, point.y + 40);

		pDC->StretchBlt( //비트맵을 1:1로 출력
			point.x, point.y, unit->ImageSize.x, unit->ImageSize.y,   //비트맵이 출력될 client 영역
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//메모리 dc가 선택한 비트맵 좌측상단 x,y 부터 출력
			SRCCOPY  //비트맵을 목적지에 기존 내용위에 복사
			);

		for (int i = 0; i<unit->getMaxOutput(); i++) {
			pDC->MoveTo(unit->output_pt[i]);
			pDC->LineTo(unit->output_pt[i].x + temp_pt.x, unit->output_pt[i].y + temp_pt.y);
		}

		switch (unit->getDirction()) {
		case EAST: {
			temp_pt.SetPoint(20, 0);
			break;
		}case NORTH: {
			temp_pt.SetPoint(0, -20);
			break;
		}case WEST: {
			temp_pt.SetPoint(-20, 0);
			break;
		}case SOUTH: {
			temp_pt.SetPoint(0, 20);
			break;
		}
		}

		for (int i = 0; i<unit->getMaxInput(); i++) {
			pDC->MoveTo(unit->input_pt[i]);
			pDC->LineTo(unit->input_pt[i].x + temp_pt.x, unit->input_pt[i].y + temp_pt.y);
		}

	}
	else if (unit->isType(NorGate_type)) {
		switch (unit->getDirction()) {
		case EAST: {
			bit.LoadBitmapW(IDB_NORGATE);
			temp_pt.SetPoint(-20, 0);
			break;
		}case NORTH: {
			bit.LoadBitmapW(IDB_NORGATE1);
			temp_pt.SetPoint(0, 20);
			break;
		}case WEST: {
			bit.LoadBitmapW(IDB_NORGATE2);
			temp_pt.SetPoint(20, 0);
			break;
		}case SOUTH: {
			bit.LoadBitmapW(IDB_NORGATE3);
			temp_pt.SetPoint(0, -20);
			break;
		}
		}
		bit.GetBitmap(&bminfo);
		memDC.SelectObject(&bit);

		CPoint point2(point.x + 40, point.y + 40);

		pDC->StretchBlt( //비트맵을 1:1로 출력
			point.x, point.y, unit->ImageSize.x, unit->ImageSize.y,   //비트맵이 출력될 client 영역
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//메모리 dc가 선택한 비트맵 좌측상단 x,y 부터 출력
			SRCCOPY  //비트맵을 목적지에 기존 내용위에 복사
			);



		for (int i = 0; i<unit->getMaxOutput(); i++) {
			pDC->MoveTo(unit->output_pt[i]);
			pDC->LineTo(unit->output_pt[i].x + temp_pt.x, unit->output_pt[i].y + temp_pt.y);
		}

		switch (unit->getDirction()) {
		case EAST: {
			temp_pt.SetPoint(20, 0);
			break;
		}case NORTH: {
			temp_pt.SetPoint(0, -20);
			break;
		}case WEST: {
			temp_pt.SetPoint(-20, 0);
			break;
		}case SOUTH: {
			temp_pt.SetPoint(0, 20);
			break;
		}
		}

		for (int i = 0; i<unit->getMaxInput(); i++) {
			pDC->MoveTo(unit->input_pt[i]);
			pDC->LineTo(unit->input_pt[i].x + temp_pt.x, unit->input_pt[i].y + temp_pt.y);
		}
	}
	else if (unit->isType(XorGate_type)) {

		switch (unit->getDirction()) {
		case EAST: {
			bit.LoadBitmapW(IDB_XORGATE);
			temp_pt.SetPoint(-20, 0);
			break;
		}case NORTH: {
			temp_pt.SetPoint(0, 20);

			bit.LoadBitmapW(IDB_XORGATE1);
			break;
		}case WEST: {
			temp_pt.SetPoint(20, 0);

			bit.LoadBitmapW(IDB_XORGATE2);
			break;
		}case SOUTH: {
			temp_pt.SetPoint(0, -20);

			bit.LoadBitmapW(IDB_XORGATE3);
			break;
		}
		}
		bit.GetBitmap(&bminfo);
		memDC.SelectObject(&bit);

		CPoint point2(point.x + 40, point.y + 40);

		pDC->StretchBlt( //비트맵을 1:1로 출력
			point.x, point.y, unit->ImageSize.x, unit->ImageSize.y,   //비트맵이 출력될 client 영역
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//메모리 dc가 선택한 비트맵 좌측상단 x,y 부터 출력
			SRCCOPY  //비트맵을 목적지에 기존 내용위에 복사
			);

		for (int i = 0; i<unit->getMaxOutput(); i++) {
			pDC->MoveTo(unit->output_pt[i]);
			pDC->LineTo(unit->output_pt[i].x + temp_pt.x, unit->output_pt[i].y + temp_pt.y);
		}

		switch (unit->getDirction()) {
		case EAST: {
			temp_pt.SetPoint(20, 0);
			break;
		}case NORTH: {
			temp_pt.SetPoint(0, -20);
			break;
		}case WEST: {
			temp_pt.SetPoint(-20, 0);
			break;
		}case SOUTH: {
			temp_pt.SetPoint(0, 20);
			break;
		}
		}

		for (int i = 0; i<unit->getMaxInput(); i++) {
			pDC->MoveTo(unit->input_pt[i]);
			pDC->LineTo(unit->input_pt[i].x + temp_pt.x, unit->input_pt[i].y + temp_pt.y);
		}
	}
	else if (unit->isType(DFFGate_type)) {
		bit.LoadBitmapW(IDB_DFFGATE);
		bit.GetBitmap(&bminfo);
		memDC.SelectObject(&bit);

		CPoint point2(point.x + 40, point.y + 40);

		pDC->StretchBlt( //비트맵을 1:1로 출력
			point.x, point.y, unit->ImageSize.x, unit->ImageSize.y,   //비트맵이 출력될 client 영역
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//메모리 dc가 선택한 비트맵 좌측상단 x,y 부터 출력
			SRCCOPY  //비트맵을 목적지에 기존 내용위에 복사
			);
		switch (unit->getDirction()) {
		case EAST: {
			temp_pt.SetPoint(-20, 0);
			break;
		}case NORTH: {
			temp_pt.SetPoint(0, 20);
			break;
		}case WEST: {
			temp_pt.SetPoint(20, 0);
			break;
		}case SOUTH: {
			temp_pt.SetPoint(0, -20);
			break;
		}
		}

		for (int i = 0; i < unit->getMaxOutput(); i++) {
			pDC->MoveTo(unit->output_pt[i]);
			pDC->LineTo(unit->output_pt[i].x + temp_pt.x, unit->output_pt[i].y + temp_pt.y);
		}

		switch (unit->getDirction()) {
		case EAST: {
			temp_pt.SetPoint(20, 0);
			break;
		}case NORTH: {
			temp_pt.SetPoint(0, -20);
			break;
		}case WEST: {
			temp_pt.SetPoint(-20, 0);
			break;
		}case SOUTH: {
			temp_pt.SetPoint(0, 20);
			break;
		}
		}

		pDC->MoveTo(unit->input_pt[0]);
		pDC->LineTo(unit->input_pt[0].x + temp_pt.x, unit->input_pt[0].y + temp_pt.y);

		switch (unit->getDirction()) {
		case EAST: {
			temp_pt.SetPoint(0, 20);
			break;
		}case NORTH: {
			temp_pt.SetPoint(20, 0);
			break;
		}case WEST: {
			temp_pt.SetPoint(0, -20);
			break;
		}case SOUTH: {
			temp_pt.SetPoint(-20, 0);
			break;
		}
		}

		pDC->MoveTo(unit->input_pt[1]);
		pDC->LineTo(unit->input_pt[1].x + temp_pt.x, unit->input_pt[1].y + temp_pt.y);

	}
	else if (unit->isType(JKFFGate_type)) {
		bit.LoadBitmapW(IDB_JKFFGATE);
		bit.GetBitmap(&bminfo);
		memDC.SelectObject(&bit);

		CPoint point2(point.x + 40, point.y + 40);

		pDC->StretchBlt( //비트맵을 1:1로 출력
			point.x, point.y, unit->ImageSize.x, unit->ImageSize.y,   //비트맵이 출력될 client 영역
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//메모리 dc가 선택한 비트맵 좌측상단 x,y 부터 출력
			SRCCOPY  //비트맵을 목적지에 기존 내용위에 복사
			);
		switch (unit->getDirction()) {
		case EAST: {
			temp_pt.SetPoint(-20, 0);
			break;
		}case NORTH: {
			temp_pt.SetPoint(0, 20);
			break;
		}case WEST: {
			temp_pt.SetPoint(20, 0);
			break;
		}case SOUTH: {
			temp_pt.SetPoint(0, -20);
			break;
		}
		}

		for (int i = 0; i < unit->getMaxOutput(); i++) {
			pDC->MoveTo(unit->output_pt[i]);
			pDC->LineTo(unit->output_pt[i].x + temp_pt.x, unit->output_pt[i].y + temp_pt.y);
		}

		switch (unit->getDirction()) {
		case EAST: {
			temp_pt.SetPoint(20, 0);
			break;
		}case NORTH: {
			temp_pt.SetPoint(0, -20);
			break;
		}case WEST: {
			temp_pt.SetPoint(-20, 0);
			break;
		}case SOUTH: {
			temp_pt.SetPoint(0, 20);
			break;
		}
		}

		pDC->MoveTo(unit->input_pt[0]);
		pDC->LineTo(unit->input_pt[0].x + temp_pt.x, unit->input_pt[0].y + temp_pt.y);


		switch (unit->getDirction()) {
		case EAST: {
			temp_pt.SetPoint(0, 20);
			break;
		}case NORTH: {
			temp_pt.SetPoint(20, 0);
			break;
		}case WEST: {
			temp_pt.SetPoint(0, -20);
			break;
		}case SOUTH: {
			temp_pt.SetPoint(-20, 0);
			break;
		}
		}

		pDC->MoveTo(unit->input_pt[1]);
		pDC->LineTo(unit->input_pt[1].x + temp_pt.x, unit->input_pt[1].y + temp_pt.y);
		
		switch (unit->getDirction()) {
		case EAST: {
			temp_pt.SetPoint(20, 0);
			break;
		}case NORTH: {
			temp_pt.SetPoint(0, -20);
			break;
		}case WEST: {
			temp_pt.SetPoint(-20, 0);
			break;
		}case SOUTH: {
			temp_pt.SetPoint(0, 20);
			break;
		}
		}
		pDC->MoveTo(unit->input_pt[2]);
		pDC->LineTo(unit->input_pt[2].x + temp_pt.x, unit->input_pt[2].y + temp_pt.y);

	}
	else if (unit->isType(TFFGate_type)) {
		bit.LoadBitmapW(IDB_TFFGATE);
		bit.GetBitmap(&bminfo);
		memDC.SelectObject(&bit);

		CPoint point2(point.x + 40, point.y + 40);

		pDC->StretchBlt( //비트맵을 1:1로 출력
			point.x, point.y, unit->ImageSize.x, unit->ImageSize.y,   //비트맵이 출력될 client 영역
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//메모리 dc가 선택한 비트맵 좌측상단 x,y 부터 출력
			SRCCOPY  //비트맵을 목적지에 기존 내용위에 복사
			);

		switch (unit->getDirction()) {
		case EAST: {
			temp_pt.SetPoint(-20, 0);
			break;
		}case NORTH: {
			temp_pt.SetPoint(0, 20);
			break;
		}case WEST: {
			temp_pt.SetPoint(20, 0);
			break;
		}case SOUTH: {
			temp_pt.SetPoint(0, -20);
			break;
		}
		}

		for (int i = 0; i < unit->getMaxOutput(); i++) {
			pDC->MoveTo(unit->output_pt[i]);
			pDC->LineTo(unit->output_pt[i].x + temp_pt.x, unit->output_pt[i].y + temp_pt.y);
		}

		switch (unit->getDirction()) {
		case EAST: {
			temp_pt.SetPoint(20, 0);
			break;
		}case NORTH: {
			temp_pt.SetPoint(0, -20);
			break;
		}case WEST: {
			temp_pt.SetPoint(-20, 0);
			break;
		}case SOUTH: {
			temp_pt.SetPoint(0, 20);
			break;
		}
		}

		pDC->MoveTo(unit->input_pt[0]);
		pDC->LineTo(unit->input_pt[0].x + temp_pt.x, unit->input_pt[0].y + temp_pt.y);

		switch (unit->getDirction()) {
		case EAST: {
			temp_pt.SetPoint(0, 20);
			break;
		}case NORTH: {
			temp_pt.SetPoint(20, 0);
			break;
		}case WEST: {
			temp_pt.SetPoint(0, -20);
			break;
		}case SOUTH: {
			temp_pt.SetPoint(-20, 0);
			break;
		}
		}

		pDC->MoveTo(unit->input_pt[1]);
		pDC->LineTo(unit->input_pt[1].x + temp_pt.x, unit->input_pt[1].y + temp_pt.y);

	}
	if ((unit->label.state)) {
		unit->onLabelName(pDC);
	}

	unit->ImageSize = temp_image;
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

POSITION CLogic_Circuit_SimulatorView::CheckOnLine(CPoint pt) {
	POSITION pos;
	CPoint temp_point;

	pos = LineList.GetHeadPosition(); //List의 헤더로 이동

	while (pos) {
		POSITION current_pos = pos;
		LineUnit *temp;
		temp = (LineUnit *)LineList.GetNext(pos);

		if (temp->getPoint().x == temp->endPoint.x && temp->getPoint().x == Nearby_point(pt).x) {
			if (temp->getPoint().y < temp->endPoint.y) {
				if (temp->getPoint().y <= Nearby_point(pt).y && Nearby_point(pt).y <= temp->endPoint.y)
					return current_pos;
			}
			else if (temp->endPoint.y < temp->getPoint().y) {
				if (temp->endPoint.y <= Nearby_point(pt).y && Nearby_point(pt).y <= temp->getPoint().y) {
					return current_pos;
				}
			}
		}
		else if (temp->getPoint().y == temp->endPoint.y && temp->getPoint().y == Nearby_point(pt).y) {
			if (temp->getPoint().x < temp->endPoint.x) {
				if (temp->getPoint().x <= Nearby_point(pt).x && Nearby_point(pt).x <= temp->endPoint.x )
					return current_pos;
			}
			else if (temp->endPoint.x < temp->getPoint().x) {
				if (temp->endPoint.x <= Nearby_point(pt).x && Nearby_point(pt).x <= temp->getPoint().x) {
					return current_pos;
				}
			}
		}
	}
	return NULL;
}

POSITION CLogic_Circuit_SimulatorView::CheckOnBranch(CPoint pt) {
	POSITION pos;
	CPoint temp_point;

	pos = LineList.GetHeadPosition(); //List의 헤더로 이동

	while (pos) {
		POSITION current_pos = pos;
		LineUnit *temp;
		temp = (branch *)LineList.GetNext(pos);

		if (temp->getPoint().x == temp->getPoint().y) {
			if (temp->getPoint().x == Nearby_point(pt).x) {
				return current_pos;
			}
		}
	}
	return NULL;
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
	this->stack = new unitStack[this->DrawList.GetSize()+ this->LineList.GetSize()];
	this->stack_count = 0;
	
	for (int i = 0; i < (this->DrawList.GetSize()+this->LineList.GetSize()); i++) {
		stack[i].unit = NULL;
		stack[i].prev = NULL;
	}

	unit->Op();

	stack[stack_count].unit = unit;
	stack[stack_count].prev = new bool[unit->getMaxOutput()];

	for (int i = 0; i < unit->getCurrentOutput(); i++) {
		stack[stack_count].prev[i] = unit->getOutput(i);
		}
	stack_count++;
	for (int i = 0; i < unit->getCurrentOutput(); i++) {
		Update(unit->getOutputList(i));
	}
	this->stack_count = 0;
}

void CLogic_Circuit_SimulatorView::Update(LogicUnit *unit) {
	int temp = -1;
	unit->Op();		//연산
	temp = isInStack(unit);//현재 도착한곳이 스택에 있는지 확인

	//연산결과를 다음 연결되어있는것들의 입력값으로 전달해줌.
	if (unit->getCurrentOutput() != 0) {
		for (int i = 0; i < unit->getMaxOutput(); i++) {
			for (int j = 0; j < (unit->getOutputList(i))->getMaxInput(); j++) {
				//i번째 연결된것을 확인하고 값을 전달.
				if ((unit->getOutputList(i))->getInputList(j) == unit) {	
					(unit->getOutputList(i))->setInput(j, unit->getOutput(i));
				}
			}
		}
	}
	//출력 램프에 도착하면 업데이트를 종료
	if (unit->isType(OutputSwitch_type) == false) {
		//스택이 비어있으면
		if (stack[stack_count].unit == NULL) {
			//스택에 없던거면
			if (temp == -1) {
				stack[stack_count].unit = unit;
				stack[stack_count].prev = new bool[unit->getMaxOutput()];
				
				//이전값을 저장
				for (int i = 0; i < unit->getCurrentOutput(); i++) {
					stack[stack_count].prev[i] = unit->getOutput(i);
				}
				stack_count++;
				
				//모든 출력으로 연결된것들을 다시 업데이트
				for (int i = 0; i < unit->getCurrentOutput(); i++) {
					Update(unit->getOutputList(i));
				}
			}
			//스택에 있던거라면
			else {
				for (int i = 0; i < unit->getCurrentOutput(); i++) {
					//스택에 있던건대 i번째 출력의 결과가 다르면 다시 업데이트
					if (stack[temp].prev[i] != unit->getOutput(i)) {
						stack[temp].prev[i] = unit->getOutput(i);
						Update(unit->getOutputList(i));
					}
				}
			}
		}
	}
}

int CLogic_Circuit_SimulatorView::isInStack(LogicUnit *unit) {
	for (int i = 0; (i < this->stack_count) && (this->stack[i].unit != NULL); i++) {
		if (stack[i].unit == unit) {
			return i;
		}
		else return -1;
	}
}

//현재 클릭지점(point)가 어떤 게이트의 몇번째 입력지점인지 리턴해주고 isInput에 입력이면 true, 출력지점이면 false 
int CLogic_Circuit_SimulatorView::search_unit(CPoint point, bool &isInput) {
	POSITION pos;
	CPoint pt;
	int result;;
	current = NULL;

	pos = LineList.GetHeadPosition(); //List의 헤더로 이동

	while (pos) {
		current = pos;
		LineUnit *temp;
		temp = (LineUnit *)LineList.GetNext(pos);

		//인풋이나 아웃풋쪽에 있는지 확인
		pt = Nearby_point(point);					//마우스 포인터의 가까운 점을 구함.
		result = temp->get_putIndex(pt, isInput);	//가까운점이 input점에 있는지 확인.
		if (result != -1) {
			return result;	//구한 연결점의 인덱스를 리턴해줌
		}
	}

	pos = DrawList.GetHeadPosition(); //List의 헤더로 이동

	while (pos) {
		current = pos;
		LogicUnit *temp;
		temp = (LogicUnit *)DrawList.GetNext(pos);

		//인풋이나 아웃풋쪽에 있는지 확인
		pt = Nearby_point(point);					//마우스 포인터의 가까운 점을 구함.
		result = temp->get_putIndex(pt, isInput);	//가까운점이 input점에 있는지 확인.
		if (result != -1) {
			return result;	//구한 연결점의 인덱스를 리턴해줌
		}
	}

	current = NULL;
	return -1;
}

void CLogic_Circuit_SimulatorView::OnLButtonDown(UINT nFlags, CPoint point){
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);
	LogicUnit* temp;
	LineUnit *selected_line;
	branch * br = NULL;
	int result;
	bool isInput = false;

	//빈공간에 클릭이 됨
	if (CheckIn(point) == false && (selected_Input == NULL || selected_Output == NULL) && (selected ==NULL)) {
		//혹시 유닛의 인풋이나 아웃풋쪽에 클릭이 됬는지 확인
		result = search_unit(point, isInput);

		//찾은값이 있을경우
		if (result != -1) {
			temp = (LogicUnit*)DrawList.GetAt(current);
			CPoint pt;
			pt = Nearby_point(point);



			if (temp->isType(LineUnit_type) &&((pt == temp->output_pt[0]&& temp->getOutputList(0)!=NULL) || (pt == temp->input_pt[0] && temp->getInputList(0) != NULL)) ) {
				//분기만들곳의 아웃풋 지점이면
				br = new branch(pt, 2);
				if (pt == temp->output_pt[0]) {
					LineUnit *temp_line = (LineUnit *)temp->getOutputList(0);
					LogicUnit::disconnect_Unit(temp, 0, temp->getOutputList(0), 0);
					LogicUnit::connect_Unit(temp, 0, br, 0);
					LogicUnit::connect_Unit(br, 0, temp_line, 0);

					dc.Ellipse(pt.x - 5, pt.y - 5, pt.x + 5, pt.y + 5);
					selected_Input = br;
					selected_Input_Index = br->getCurrentInput();
				}
				else if(pt == temp->input_pt[0]){
					LineUnit *temp_line = (LineUnit *)temp->getInputList(0);
					LogicUnit::disconnect_Unit(temp->getInputList(0), 0, temp, 0);
					LogicUnit::connect_Unit(temp_line, 0, br, 0);
					LogicUnit::connect_Unit(br, 0, temp, 0);

					dc.Ellipse(pt.x - 5, pt.y - 5, pt.x + 5, pt.y + 5);
					selected_Input = br;
					selected_Input_Index = br->getCurrentInput();
				}

				this->LineList.AddHead(br);
			}
			else{
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
		}
		//빈영역에 선택된경우
		else {
			//연결이 안된 라인끼리 연결할경우
			POSITION pos = CheckOnLine(point);
			if (pos != NULL) {
				selected_line = (LineUnit*)LineList.GetAt(pos);
				selected = selected_line;
			}
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
					dc.LineTo(Nearby_point(CPoint(prevx, prevy)));

					if ((selected_Input->output_pt)[selected_Input_Index] == Nearby_point(CPoint(prevx, prevy))) {
						line = new LineUnit((selected_Input->output_pt)[selected_Input_Index], Nearby_point(line_start_pt));
					}
					else {
						line = new LineUnit((selected_Input->output_pt)[selected_Input_Index], Nearby_point(CPoint(prevx, prevy)));
					}

					LogicUnit::connect_Unit(selected_Input, selected_Input_Index, line, 0);
				}
				//신호를 받는것만 연결됬을때
				else if (selected_Output != NULL) {
					dc.MoveTo(line_start_pt);
					dc.LineTo(Nearby_point(CPoint(prevx, prevy)));

					if ((selected_Output->input_pt)[selected_Output_Index] == Nearby_point(line_start_pt)) {
						line = new LineUnit(Nearby_point(point), Nearby_point(line_start_pt));
					}
					else {
						line = new LineUnit(line_start_pt, Nearby_point(point));
					}

					LogicUnit::connect_Unit(line, 0, selected_Output, selected_Output_Index);
				}
				else if (selected_Input == NULL && selected_Output == NULL) {
					dc.MoveTo(line_start_pt);
					dc.LineTo(Nearby_point(CPoint(prevx, prevy)));

					line = new LineUnit(line_start_pt, Nearby_point(CPoint(prevx, prevy)));
				}

				LineList.AddHead(line);

				selected_Input = NULL;
				selected_Output = NULL;

				linning = false;
		}
		else {

			if (selected != NULL) {
				if (((LineUnit*)selected)->endPoint.x == selected->getPoint().x) {
					//세로 선에 시작점에 연결할때
					if (((LineUnit*)selected)->getPoint().y == Nearby_point(point).y) {
						selected_Output = selected_line;

						selected = NULL;
					}
					//세로 선에 끝점에 연결할때
					else if (((LineUnit*)selected)->endPoint.y == Nearby_point(point).y) {
						selected_Input = selected_line;

						selected = NULL;
					}
				}
				else if (((LineUnit*)selected)->endPoint.y == selected->getPoint().y) {
					if (((LineUnit*)selected)->getPoint().x == Nearby_point(point).x) {
						selected_Output = selected_line;

						selected = NULL;
					}
					else if (((LineUnit*)selected)->endPoint.x == Nearby_point(point).x) {
						selected_Input = selected_line;

						selected = NULL;
					}
				}
			}

			if (selected == NULL) {
				linning = true;
				line_start_pt = Nearby_point(point);
			}
			else if (selected != NULL) {
				Invalidate();
			}
		}
	}
	else if (selected != NULL) {
		selected = NULL;
		Invalidate();
	}
	//빈공간이 아닐경우?
	else if(selected_Input != NULL || selected_Output != NULL)
	{
		selected_Input = selected_Output = NULL;
	}
	CView::OnLButtonDown(nFlags, point);
}

void CLogic_Circuit_SimulatorView::OnLButtonUp(UINT nFlags, CPoint point){
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

void CLogic_Circuit_SimulatorView::OnMouseMove(UINT nFlags, CPoint point){
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
			temp->label.pt.SetPoint(pt.x, pt.y - 20);

			Invalidate();
		}
	}
	//선 그려주기 부분
	else if (linning == true) {
		CPoint temp(startx,starty);
		int lengthx, lengthy;

		dc.SelectStockObject(WHITE_PEN);

		temp = Nearby_point(temp);
		dc.MoveTo(temp);
		dc.LineTo(prevx, prevy);
		dc.Ellipse(prevx - 5, prevy - 5, prevx + 5, prevy + 5);

		dc.SelectStockObject(BLACK_PEN);

		if (point.x > temp.x)
			lengthx = point.x - temp.x;
		else
			lengthx = temp.x - point.x;

		if (point.y > temp.y)
			lengthy = point.y - temp.y;
		else
			lengthy = temp.y - point.y;

		dc.MoveTo(temp);
		if (lengthx > lengthy)
			temp = Nearby_point(CPoint(point.x, temp.y));
		else
			temp = Nearby_point(CPoint(temp.x, point.y));
		
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

					newUpdate(temp);
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
	/*
	Clock_pulse *clr;
	InputSwitch *inp;
	POSITION pos;
	pos = LineList.GetHeadPosition();
	
	while (pos)
	{
		clr->setSwitch();
		newUpdate(clr);
	}
	*/
	CView::OnTimer(nIDEvent);
}

//우클릭시 라벨붙이기 띄움
void CLogic_Circuit_SimulatorView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CMenu menu;
	CMenu menu2;
	menu.LoadMenu(IDR_MENU1);
	menu2.LoadMenu(IDR_MENU2);

	if (CheckIn(this->mPoint) == true){
		CMenu *pMenu = menu.GetSubMenu(0);
		pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
	}
	else {
		CMenu *pMenu = menu2.GetSubMenu(0);
		pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
	}

}

//라벨붙이기
void CLogic_Circuit_SimulatorView::OnLabel()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CClientDC *dc = new CClientDC(this);
	
	LogicUnit *temp;
	temp = (LogicUnit *)DrawList.GetNext(current);

	temp->onLabelName(dc);
	temp->label.state = true;
	current = NULL;
}

void CLogic_Circuit_SimulatorView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	switch (nChar) {
	case VK_DELETE: {
		if (selected != NULL) {
			bool isInput;
			POSITION pos = LineList.Find(selected);
			LineUnit *line = (LineUnit *)LineList.GetAt(pos);
			LogicUnit* next = (LogicUnit*)(line->getOutputList(0));

			int num = search_unit(line->getPoint(), isInput);

			//선택된 라인의 어느한점이 다른 라인이랑 연결되있는지 확인
			if (num == -1) {
				if (line->getInputList(0)->isType(LineUnit_type)) {
					num = 0;

				}
				else if (line->getOutputList(0)->isType(LineUnit_type)) {
					num = 0;

				}
			}

			if (num != -1) {
				if (isInput) {
					int num2 = search_unit(line->endPoint, isInput);
					LogicUnit::disconnect_line(line, line->getInputList(0), num2, line->getOutputList(0), num);
				}
				else {
					int num2 = search_unit(line->endPoint, isInput);
					LogicUnit::disconnect_line(line, line->getInputList(0), num, line->getOutputList(0), num2);
				}
			}
			else {

			}
			
			LineList.RemoveAt(pos);
			selected = NULL;

			Invalidate();
		}
	}
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CLogic_Circuit_SimulatorView::OnRotate() 
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.


	LogicUnit* temp = (LogicUnit *)DrawList.GetNext(current);

	switch (temp->getDirction()) {
	case EAST: {
		temp->setDirction(NORTH);
		break;
	}
	case NORTH: {
		temp->setDirction(WEST);
		break;
	}case WEST: {
		temp->setDirction(SOUTH);
		break;
	}case SOUTH: {
		temp->setDirction(EAST);
		break;
	}
	}

	temp->rotate_on = true;
	temp->setPut_point(temp->getPoint());
	current = NULL;
	Invalidate();
}

//파일 새로만들기
void CLogic_Circuit_SimulatorView::OnFileNew()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	while (!DrawList.IsEmpty()){
		LogicUnit *temp = (LogicUnit *)this->DrawList.RemoveHead();
		delete temp;

		Invalidate();
	}

	while (!LineList.IsEmpty()) {
		LogicUnit *temp2 = (LogicUnit *)this->LineList.RemoveHead();
		delete temp2;

		Invalidate();
	}
}


void CLogic_Circuit_SimulatorView::OnGatecopy()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	LogicUnit *temp;
	Temp_stack = (LogicUnit *)DrawList.GetNext(current);
/*
	this->Temp_stack.AddHead(temp);
	Temp_stack.RemoveAll();*/
	current = NULL;
}


void CLogic_Circuit_SimulatorView::OnGatecut()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	LogicUnit *temp;
	POSITION pos;
	pos = current;
	Temp_stack = (LogicUnit *)DrawList.GetNext(current);
	
	

	Temp_stack->deleteUnit();
	DrawList.RemoveAt(pos);
	
	/*	this->Temp_stack.AddHead(temp);
	Temp_stack.RemoveAll();*/
	current = NULL;
	Invalidate();
}


void CLogic_Circuit_SimulatorView::OnDelete()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	LogicUnit *temp;
	POSITION pos;
	pos = current;
	Temp_stack = (LogicUnit *)DrawList.GetNext(current);

	Temp_stack->deleteUnit();
	DrawList.RemoveAt(pos);
	delete Temp_stack;
	Temp_stack = NULL;
	current = NULL;
	Invalidate();
}


void CLogic_Circuit_SimulatorView::OnPaste()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	LogicUnit* temp;
	LogicUnit* newLogic;
	POSITION pos=NULL;
	
	if(Temp_stack != NULL) {
			if (Temp_stack->isType(AndGate_type)) {
				AndGate *unit = new AndGate(Nearby_point(mPoint));
				unit->setDirction(Temp_stack->getDirction());
				this->DrawList.AddHead(unit);
				this->Invalidate();
			}
			else if (Temp_stack->isType(OrGate_type)) {
				OrGate *unit = new OrGate(Nearby_point(mPoint));

				unit->setDirction(Temp_stack->getDirction());
				this->DrawList.AddHead(unit);
				this->Invalidate();
			}
			else if (Temp_stack->isType(NotGate_type)) {
				NotGate *unit = new NotGate(Nearby_point(mPoint));
				unit->setDirction(Temp_stack->getDirction());
				this->DrawList.AddHead(unit);
				this->Invalidate();
			}
			else if (Temp_stack->isType(NandGate_type)) {
				NANDGate *unit = new NANDGate(Nearby_point(mPoint));
				unit->setDirction(Temp_stack->getDirction());
				this->DrawList.AddHead(unit);
				this->Invalidate();
			}
			else if (Temp_stack->isType(NorGate_type)) {
				NorGate *unit = new NorGate(Nearby_point(mPoint));
				unit->setDirction(Temp_stack->getDirction());
				this->DrawList.AddHead(unit);
				this->Invalidate();
			}
			else if (Temp_stack->isType(XorGate_type)) {
				XorGate *unit = new XorGate(Nearby_point(mPoint));
				unit->setDirction(Temp_stack->getDirction());
				this->DrawList.AddHead(unit);
				this->Invalidate();
			}
			else if (Temp_stack->isType(DFFGate_type)) {
				DFFGate *unit = new DFFGate(Nearby_point(mPoint));
				unit->setDirction(Temp_stack->getDirction());
				this->DrawList.AddHead(unit);
				this->Invalidate();

			}
			else if (Temp_stack->isType(JKFFGate_type)) {
				JKFFGate *unit = new JKFFGate(Nearby_point(mPoint));
				unit->setDirction(Temp_stack->getDirction());
				this->DrawList.AddHead(unit);
				this->Invalidate();

			}
			else if (Temp_stack->isType(TFFGate_type)) {
				TFFGate *unit = new TFFGate(Nearby_point(mPoint));
				unit->setDirction(Temp_stack->getDirction());
				this->DrawList.AddHead(unit);
				this->Invalidate();

			}
			else if (Temp_stack->isType(InputSwitch_type)) {
				InputSwitch *unit = new InputSwitch(Nearby_point(mPoint));
				unit->setDirction(Temp_stack->getDirction());
				this->DrawList.AddHead(unit);
				this->Invalidate();
			}
			else if (Temp_stack->isType(OutputSwitch_type)) {
				OutputSwitch  *unit = new OutputSwitch(Nearby_point(mPoint));
				unit->setDirction(Temp_stack->getDirction());
				this->DrawList.AddHead(unit);
				this->Invalidate();
			}
			else if (Temp_stack->isType(Segment_type)) {
				Segment *unit = new Segment(Nearby_point(mPoint));
				unit->setDirction(Temp_stack->getDirction());
				this->DrawList.AddHead(unit);
				this->Invalidate();
			}
	}
	Temp_stack = NULL;
}
