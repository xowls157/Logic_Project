
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
	ON_COMMAND(ID_32775, &CLogic_Circuit_SimulatorView::CreateNot)
	ON_COMMAND(ID_32776, &CLogic_Circuit_SimulatorView::CreateNand)
	ON_COMMAND(ID_32777, &CLogic_Circuit_SimulatorView::CreateNor)
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
	CDC memDC;  //�޸� dc(��ġ�� ����Ǿ� ���� ���� dc)
	CPoint point(pt);

	memDC.CreateCompatibleDC(pDC);

	if (unit->isType(InputSwitch_type)) {

		bit.LoadBitmapW(IDB_OnSwitch);
		bit.GetBitmap(&bminfo);
		memDC.SelectObject(&bit);

		CPoint point2(point.x + 40, point.y + 40);

		pDC->StretchBlt( //��Ʈ���� 1:1�� ���
			point.x, point.y, 20, 20,   //��Ʈ���� ��µ� client ����
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//�޸� dc�� ������ ��Ʈ�� ������� x,y ���� ���
			SRCCOPY  //��Ʈ���� �������� ���� �������� ����
			);
	}
	if (unit->isType(OutputSwitch_type)) {

		bit.LoadBitmapW(IDB_OnOUTPUT);
		bit.GetBitmap(&bminfo);
		memDC.SelectObject(&bit);

		CPoint point2(point.x + 40, point.y + 40);

		pDC->StretchBlt( //��Ʈ���� 1:1�� ���
			point.x, point.y, 20, 20,   //��Ʈ���� ��µ� client ����
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//�޸� dc�� ������ ��Ʈ�� ������� x,y ���� ���
			SRCCOPY  //��Ʈ���� �������� ���� �������� ����
			);
	}
	else if (unit->isType(AndGate_type)) {

		bit.LoadBitmapW(IDB_ANDGATE);
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
	else if (unit->isType(OrGate_type)) {

		bit.LoadBitmapW(IDB_ORGATE);
		bit.GetBitmap(&bminfo);
		memDC.SelectObject(&bit);

		CPoint point2(point.x + 40, point.y + 40);

		pDC->StretchBlt( //��Ʈ���� 1:1�� ���
			point.x, point.y, 60, 80,   //��Ʈ���� ��µ� client ����
			&memDC, 0, 0, bminfo.bmWidth, bminfo.bmHeight,	//�޸� dc�� ������ ��Ʈ�� ������� x,y ���� ���
			SRCCOPY  //��Ʈ���� �������� ���� �������� ����
			);
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

	pos = DrawList.GetHeadPosition(); //List�� ����� �̵�

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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnLButtonDown(nFlags, point);

	CheckIn(point);
}


void CLogic_Circuit_SimulatorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnLButtonUp(nFlags, point);


	move = false;
}


void CLogic_Circuit_SimulatorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnMouseMove(nFlags, point);

	if (nFlags & MK_LBUTTON == 1 && current != NULL) {

		if (move)
		{
			LogicUnit *temp;
			POINT pt;
			temp = (LogicUnit *)DrawList.GetAt(current);

			pt = temp->getPoint();

			// �̵�
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

		// ũ�� ����
		boxes[current].right = point.x;
		boxes[current].bottom = point.y;

		dc.Rectangle(boxes[current].left, boxes[current].top, boxes[current].right, boxes[current].bottom);

		}
		*/
	}
}


void CLogic_Circuit_SimulatorView::CreateInput()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	InputSwitch *in1 = new InputSwitch(CPoint(10, 10));

	in1->setOutput(0, true);

	DrawList.AddHead(in1);

	Invalidate();
}


void CLogic_Circuit_SimulatorView::CreateOutput()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	OutputSwitch *in1 = new OutputSwitch(CPoint(10, 10));

	DrawList.AddHead(in1);

	Invalidate();
}


void CLogic_Circuit_SimulatorView::CreateAND()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	AndGate *in1 = new AndGate(CPoint(10, 10));

	DrawList.AddHead(in1);

	Invalidate();
}


void CLogic_Circuit_SimulatorView::CreateOr()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	OrGate *in1 = new OrGate(CPoint(10, 10));

	DrawList.AddHead(in1);

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
