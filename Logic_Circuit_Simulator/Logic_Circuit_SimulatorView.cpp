
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
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
	ON_WM_LBUTTONDBLCLK()
	ON_WM_TIMER()
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

	move = false;
	selected_Input = NULL;
	selected_Output = NULL;
	selected_Input_Index = -1;
	selected_Output_Index = -1;
	temp1 = temp2 = NULL;

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
	}

	pos = DrawList.GetHeadPosition(); //List�� ����� �̵�
	while (pos) {
		LogicUnit *temp = (LogicUnit*)DrawList.GetNext(pos); //Ŭ������ü�� List�� ���� ��ũ ������ �ޱ�( Ŭ�����ּҰ� ������� )
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

		pDC->MoveTo(pt.x+40, pt.y+20 );
		pDC->LineTo(pt.x + 60, pt.y+20);
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

		pDC->MoveTo(pt.x, pt.y+20);
		pDC->LineTo(pt.x - 20, pt.y+20);
	}
	else if (unit->isType(AndGate_type)) {
		((AndGate*)unit)->andOp();

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

		bit.LoadBitmapW(IDB_ORGATE);
		bit.GetBitmap(&bminfo);
		memDC.SelectObject(&bit);

		pDC->StretchBlt( //��Ʈ���� 1:1�� ���
			point.x, point.y, 60, 80,   //��Ʈ���� ��µ� client ����
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//�޸� dc�� ������ ��Ʈ�� ������� x,y ���� ���
			SRCCOPY  //��Ʈ���� �������� ���� �������� ����
			);
	}
}

//���콺�� �׸��ȿ� ��ġ�ߴ���
bool CLogic_Circuit_SimulatorView::CheckIn(CPoint point) {
	POSITION pos;
	CPoint temp_point;
	startx = point.x;
	starty = point.y;

	current = NULL;

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

//
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
	if (CheckIn(point) == false && 
		(selected_Input == NULL || selected_Output == NULL)) {
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
			if (selected_Input != NULL && selected_Output != NULL) {
				dc.MoveTo((selected_Input->output_pt)[selected_Input_Index].x, (selected_Input->output_pt)[selected_Input_Index].y);
				dc.LineTo((selected_Output->input_pt)[selected_Output_Index].x, (selected_Output->input_pt)[selected_Output_Index].y);

				LineUnit* line = new LineUnit((selected_Input->output_pt)[selected_Input_Index], (selected_Output->input_pt)[selected_Output_Index]);

				LogicUnit::connect_line(line, selected_Input, selected_Input_Index, selected_Output, selected_Output_Index);

				LineList.AddHead(line);

				selected_Input = NULL;
				selected_Output = NULL;
			}
		}
		//�󿵿��� ���õȰ��
		else {
			//�б⸦ ����� ���� �׷��ֱ� �߰� �κ�

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

			Invalidate();
		}
	}
	else {
		//��ǲ �ƿ�ǲ ��ǥ Ȯ��
	}
	move = false;

	CView::OnLButtonUp(nFlags, point);
}

void CLogic_Circuit_SimulatorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnMouseMove(nFlags, point);
	CClientDC dc(this);

	if (nFlags & MK_LBUTTON == 1 && current != NULL) {

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

			Invalidate();
		}
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


void CLogic_Circuit_SimulatorView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnTimer(nIDEvent);
}
