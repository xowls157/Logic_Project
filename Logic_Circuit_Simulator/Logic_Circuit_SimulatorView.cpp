
// Logic_Circuit_SimulatorView.cpp : CLogic_Circuit_SimulatorView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
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

// CLogic_Circuit_SimulatorView ����/�Ҹ�

CLogic_Circuit_SimulatorView::CLogic_Circuit_SimulatorView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.


}

CLogic_Circuit_SimulatorView::~CLogic_Circuit_SimulatorView()
{
}

BOOL CLogic_Circuit_SimulatorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	linning = move = false;
	selected_Input = NULL;
	selected_Output = NULL;
	selected_Input_Index = -1;
	selected_Output_Index = -1;
	prevx = prevy = -1;

	return CView::PreCreateWindow(cs);
}

// CLogic_Circuit_SimulatorView �׸���

void CLogic_Circuit_SimulatorView::OnDraw(CDC* pDC)
{
	CLogic_Circuit_SimulatorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.

	CFont font;
	CBitmap bit;
	CPoint point(10, 10);
	POSITION pos;


	//Ŭ���̾�Ʈ ������ �����
	CreatePoint(pDC);	

	pos = LineList.GetHeadPosition();
	while (pos) {
		LineUnit *temp = (LineUnit *)DrawList.GetNext(pos); //Ŭ������ü�� List�� ���� ��ũ ������ �ޱ�( Ŭ�����ּҰ� ������� )

		point = temp->getPoint();
		pDC->MoveTo(point);
		pDC->LineTo(temp->endPoint);

		pDC->Ellipse(point.x - 5, point.y - 5, point.x + 5, point.y + 5);
		pDC->Ellipse(temp->endPoint.x - 5, temp->endPoint.y - 5, temp->endPoint.x + 5, temp->endPoint.y + 5);

	}

	pos = DrawList.GetTailPosition(); //List�� ����� �̵�
	while (pos) {
		LogicUnit *temp = (LogicUnit*)DrawList.GetPrev(pos); //Ŭ������ü�� List�� ���� ��ũ ������ �ޱ�( Ŭ�����ּҰ� ������� )
		if (temp->isType(OutputSwitch_type) == true) {
			((OutputSwitch*)temp)->updateOutput();
		}
		DrawUnit(pDC, temp->getPoint(), temp);
	}
}


// CLogic_Circuit_SimulatorView �μ�

BOOL CLogic_Circuit_SimulatorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CLogic_Circuit_SimulatorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CLogic_Circuit_SimulatorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CLogic_Circuit_SimulatorView ����

#ifdef _DEBUG
void CLogic_Circuit_SimulatorView::AssertValid() const
{
	CView::AssertValid();
}

void CLogic_Circuit_SimulatorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLogic_Circuit_SimulatorDoc* CLogic_Circuit_SimulatorView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLogic_Circuit_SimulatorDoc)));
	return (CLogic_Circuit_SimulatorDoc*)m_pDocument;
}
#endif //_DEBUG


// CLogic_Circuit_SimulatorView �޽��� ó����


//Ŭ���̾�Ʈ ������ �����.
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

//����Ʈ�� ��� ��ü�� ���޹޾� Ÿ�Կ����� �׷��ֱ�
void CLogic_Circuit_SimulatorView::DrawUnit(CDC* pDC, CPoint pt, LogicUnit *unit) {
	CClientDC dc(this);
	CRect rect;
	CBitmap bit;
	BITMAP bminfo;
	CDC memDC;  //�޸� dc(��ġ�� ����Ǿ� ���� ���� dc)
	CPoint point(pt);

	memDC.CreateCompatibleDC(pDC);

	if (unit->isType(InputSwitch_type)) {

		if (unit->getOutput(0) == true)
			bit.LoadBitmapW(IDB_OffSwitch);
		else
			bit.LoadBitmapW(IDB_OnSwitch);
		bit.GetBitmap(&bminfo);
		memDC.SelectObject(&bit);

		pDC->StretchBlt( //��Ʈ���� 1:1�� ���
			point.x, point.y, 40, 40,   //��Ʈ���� ��µ� client ����
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//�޸� dc�� ������ ��Ʈ�� ������� x,y ���� ���
			SRCCOPY  //��Ʈ���� �������� ���� �������� ����
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

		pDC->StretchBlt( //��Ʈ���� 1:1�� ���
			point.x, point.y, 40, 40,   //��Ʈ���� ��µ� client ����
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//�޸� dc�� ������ ��Ʈ�� ������� x,y ���� ���
			SRCCOPY  //��Ʈ���� �������� ���� �������� ����
			);

		pDC->MoveTo(pt.x, pt.y + 20);
		pDC->LineTo(pt.x - 20, pt.y + 20);
	}
	else if (unit->isType(AndGate_type)) {
		((AndGate*)unit)->Op();

		bit.LoadBitmapW(IDB_ANDGATE);
		bit.GetBitmap(&bminfo);
		memDC.SelectObject(&bit);

		pDC->StretchBlt( //��Ʈ���� 1:1�� ���
			point.x, point.y, 60, 80,   //��Ʈ���� ��µ� client ����
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//�޸� dc�� ������ ��Ʈ�� ������� x,y ���� ���
			SRCCOPY  //��Ʈ���� �������� ���� �������� ����
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

		pDC->StretchBlt( //��Ʈ���� 1:1�� ���
			point.x, point.y, 60, 80,   //��Ʈ���� ��µ� client ����
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//�޸� dc�� ������ ��Ʈ�� ������� x,y ���� ���
			SRCCOPY  //��Ʈ���� �������� ���� �������� ����
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

		pDC->StretchBlt( //��Ʈ���� 1:1�� ���
			point.x, point.y, 60, 80,   //��Ʈ���� ��µ� client ����
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//�޸� dc�� ������ ��Ʈ�� ������� x,y ���� ���
			SRCCOPY  //��Ʈ���� �������� ���� �������� ����
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

		pDC->StretchBlt( //��Ʈ���� 1:1�� ���
			point.x, point.y, 60, 80,   //��Ʈ���� ��µ� client ����
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//�޸� dc�� ������ ��Ʈ�� ������� x,y ���� ���
			SRCCOPY  //��Ʈ���� �������� ���� �������� ����
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

		pDC->StretchBlt( //��Ʈ���� 1:1�� ���
			point.x, point.y, 60, 80,   //��Ʈ���� ��µ� client ����
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//�޸� dc�� ������ ��Ʈ�� ������� x,y ���� ���
			SRCCOPY  //��Ʈ���� �������� ���� �������� ����
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

		pDC->StretchBlt( //��Ʈ���� 1:1�� ���
			point.x, point.y, 60, 80,   //��Ʈ���� ��µ� client ����
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//�޸� dc�� ������ ��Ʈ�� ������� x,y ���� ���
			SRCCOPY  //��Ʈ���� �������� ���� �������� ����
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

	pos = DrawList.GetHeadPosition(); //List�� ����� �̵�
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

//��ó�� ���� ã�� ��ǥ�� ����
CPoint CLogic_Circuit_SimulatorView::Nearby_point(CPoint pt) {
	
	CPoint leftUP_point;
	int temp_x = 0;
	int temp_y = 0;
	int i=0;

	//��ó���� ���� ����� ����-�� ���� ã�Ƴ�
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

	//������ ���� �������� ���콺�� ��������� ������� ��
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

//�Է¹��� �������κ��� �ķ� ����� �͵��� ������Ʈ ������
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

//���� Ŭ������(point)�� � ����Ʈ�� ���° �Է��������� �������ְ� isInput�� �Է��̸� true, ��������̸� false 
int CLogic_Circuit_SimulatorView::search_unit(CPoint point, bool &isInput) {
	POSITION pos;
	CPoint pt;
	int result;;
	current = NULL;

	pos = DrawList.GetHeadPosition(); //List�� ����� �̵�

	while (pos) {
		current = pos;
		LogicUnit *temp;
		temp = (LogicUnit *)DrawList.GetNext(pos);

		//��ǲ�̳� �ƿ�ǲ�ʿ� �ִ��� Ȯ��
		pt = Nearby_point(point);					//���콺 �������� ����� ���� ����.
		result = temp->get_putIndex(pt,isInput);	//��������� input���� �ִ��� Ȯ��.
		if (result != -1) {
			return result;	//���� �������� �ε����� ��������
		}
	}

	current = NULL;
	return -1;
}

void CLogic_Circuit_SimulatorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CClientDC dc(this);
	LogicUnit* temp;
	int result;
	bool isInput = false;

	//������� Ŭ���� ��
	if (CheckIn(point) == false && (selected_Input == NULL || selected_Output == NULL)) {
		//Ȥ�� ������ ��ǲ�̳� �ƿ�ǲ�ʿ� Ŭ���� ����� Ȯ��
		result = search_unit(point, isInput);

		//ã������ �������
		if (result != -1) {
			temp = (LogicUnit*)DrawList.GetAt(current);
			CPoint pt;
			pt = Nearby_point(point);

			//��ȣ�� ��°�
			if (isInput != true && selected_Input == NULL) {
				dc.Ellipse(pt.x - 5, pt.y - 5, pt.x + 5, pt.y + 5);
				selected_Input = temp;
				selected_Input_Index = result;
			}
			//��ȣ�� �޴°�
			else if (isInput == true && selected_Output == NULL) {
				dc.Ellipse(pt.x - 5, pt.y - 5, pt.x + 5, pt.y + 5);
				selected_Output = temp;
				selected_Output_Index = result;
			}
		}
		//�󿵿��� ���õȰ��
		else {
			//�б⸦ ����� ���� �׷��ֱ� �߰� �κ�
			
		}


		//���� Ŭ���� ��ǥ������ �� �׸��� ��ȣ �߰�.
		if (linning) {
			LineUnit* line;

			//�� ������ ��� ����Ʈ�� ������ �Ǿ������ ������ ������
			if (selected_Input != NULL && selected_Output != NULL) {
				dc.MoveTo((selected_Input->output_pt)[selected_Input_Index].x, (selected_Input->output_pt)[selected_Input_Index].y);
				dc.LineTo((selected_Output->input_pt)[selected_Output_Index].x, (selected_Output->input_pt)[selected_Output_Index].y);

				line = new LineUnit((selected_Input->output_pt)[selected_Input_Index], (selected_Output->input_pt)[selected_Output_Index]);

				LogicUnit::connect_line(line, selected_Input, selected_Input_Index, selected_Output, selected_Output_Index);
			}
			//��ȣ�� ��°͸� ���������
			else if (selected_Input != NULL) {
				dc.MoveTo((selected_Input->output_pt)[selected_Input_Index].x, (selected_Input->output_pt)[selected_Input_Index].y);
				dc.LineTo(Nearby_point(point));

				line = new LineUnit((selected_Input->output_pt)[selected_Input_Index], Nearby_point(point));

				LogicUnit::connect_Unit(selected_Input, selected_Input_Index, line, 0);
			}
			//��ȣ�� �޴°͸� ���������
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
	//������� �ƴҰ��?
	else if(selected_Input != NULL || selected_Output != NULL)
	{
		selected_Input = selected_Output = NULL;
	}
	CView::OnLButtonDown(nFlags, point);
}

void CLogic_Circuit_SimulatorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CClientDC dc(this);
	LogicUnit *temp;
	if (current != NULL) {
		if (move) {
			CPoint pt;
			temp = (LogicUnit *)DrawList.GetAt(current);

			//������		
			pt = Nearby_point(temp->getPoint());

			temp->setPoint(pt);
			temp->setPut_point(pt);

		}
	}
	else {
		//��ǲ �ƿ�ǲ ��ǥ Ȯ��
	}
	move = false;

	Invalidate();
	
	CView::OnLButtonUp(nFlags, point);
}

void CLogic_Circuit_SimulatorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnMouseMove(nFlags, point);
	CClientDC dc(this);
	mPoint.SetPoint(point.x, point.y);

	if (nFlags & MK_LBUTTON == 1 && current != NULL && linning != true) {
		//���� �̵��κ�
		if (move)
		{
			LogicUnit *temp;

			CPoint pt;
			temp = (LogicUnit *)DrawList.GetAt(current);

			pt = temp->getPoint();

			// �̵�
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
	//�� �׷��ֱ� �κ�
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	InputSwitch *in1 = new InputSwitch(CPoint(40, 40));

	in1->setOutput(0, true);

	DrawList.AddHead(in1);

	Invalidate();
}


void CLogic_Circuit_SimulatorView::CreateOutput()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	OutputSwitch *in1 = new OutputSwitch(CPoint(40, 40));

	DrawList.AddHead(in1);

	Invalidate();
}


void CLogic_Circuit_SimulatorView::CreateAND()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	AndGate *in1 = new AndGate(CPoint(40, 40));

	DrawList.AddHead(in1);

	Invalidate();
}


void CLogic_Circuit_SimulatorView::CreateOr()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	OrGate *in1 = new OrGate(CPoint(40, 40));

	DrawList.AddHead(in1);

	Invalidate();
}


void CLogic_Circuit_SimulatorView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	POSITION pos;
	CPoint temp_point;
	LogicUnit *temp;
	pos = DrawList.GetHeadPosition(); //List�� ����� �̵�

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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	NotGate *in1 = new NotGate(CPoint(10, 10));

	DrawList.AddHead(in1);

	Invalidate();
}


void CLogic_Circuit_SimulatorView::CreateNand()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	NANDGate *in1 = new NANDGate(CPoint(10, 10));

	DrawList.AddHead(in1);

	Invalidate();
}


void CLogic_Circuit_SimulatorView::CreateNor()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	NorGate *in1 = new NorGate(CPoint(10, 10));

	DrawList.AddHead(in1);

	Invalidate();
}


void CLogic_Circuit_SimulatorView::CreateXor()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	XorGate *in1 = new XorGate(CPoint(10, 10));

	DrawList.AddHead(in1);

	Invalidate();
}


void CLogic_Circuit_SimulatorView::CreateDFF()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CLogic_Circuit_SimulatorView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnTimer(nIDEvent);
}


void CLogic_Circuit_SimulatorView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

	CMenu menu;
	menu.LoadMenu(IDR_MENU1);

	if (CheckIn(this->mPoint) == true){
		CMenu *pMenu = menu.GetSubMenu(0);
		pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
	}

}


void CLogic_Circuit_SimulatorView::OnLabel()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CClientDC dc(this);
	LogicUnit *temp;
	temp = (LogicUnit *)DrawList.GetNext(current);

	temp->onLabelName(dc);
}
