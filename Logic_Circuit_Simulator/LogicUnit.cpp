#include "stdafx.h"
#include "LogicUnit.h"
#include <afxtempl.h>

LogicUnit::LogicUnit()
{
}

LogicUnit::LogicUnit(CPoint init_pt)
{
	this->base_pt = this->pt = init_pt;
	this->currentInput = 0;
	this->currentoutput = 0;
	this->MaxInput = 0;
	this->Maxoutput = 0;
	this->direction = EAST;
	this->label.state = false;
	this->rotate_on = false;
}

LogicUnit::~LogicUnit()
{
}

void LogicUnit::Op() {


}


//��ǥ�� �Է� ����
void LogicUnit::setPoint(CPoint setPt) {
	this->pt = setPt;
}
CPoint LogicUnit::getPoint() {

	return pt;
}
void LogicUnit::setPut_point(CPoint pt) {
	;
}
//==============================================================

//Input���� size�� ��ŭ �ʱ�ȭ ��Ŵ
void LogicUnit::initInput(int size) {

	this->input = new bool[size];
	for (int i = 0; i < size; i++) {
		this->input[i] = false;
	}

	this->inputList.SetSize(size);

	for (int i = 0; i < size; i++) {
		this->inputList[i] = NULL;
	}
}
//==============================================================

//Index��ȣ�� �Է°��� �ٲ���
void LogicUnit::setInput(int index, bool state) {
	this->input[index] = state;
}
//==============================================================

//Input���� ����
bool LogicUnit::getInput(int index) {
	return this->input[index];
}
//==============================================================


//Output���� size�� ��ŭ �ʱ�ȭ ��Ŵ 
void LogicUnit::initOutput(int size) {

	this->output = new bool[size];

	for (int i = 0; i < size; i++) {
		this->output[i] = false;
	}
	this->outputList.SetSize(size);

	for (int i = 0; i < size; i++) {
		this->outputList[i] = NULL;
	}

}
//==============================================================

//Index��ȣ�� �Է°��� �ٲ���
void LogicUnit::setOutput(int index, bool state) {

	this->output[index] = state;
}
//==============================================================

//Output ���� ����
bool LogicUnit::getOutput(int index) {

	return this->output[index];
}
//==============================================================

//clock��ȣ�� �Է°��� �ٲ���(�̿�)				
void LogicUnit::setclock(int index, bool state) {
	this->clock[index] = state;
}
//==============================================================

//clock���� ����(�̿�)
bool LogicUnit::getclock(int index) {
	return this->clock[index];
}
//==============================================================

//Input���� ������ Unit�� �����͸� �迭�� ����
void LogicUnit::setInputList(LogicUnit *unit) {

	this->currentInput++;
	this->inputList.Add(unit);
}

//Input���� ������ Unit�� �����͸� �迭�� ����(input������ ���� ���������ٰ�)
void LogicUnit::setInputList(LogicUnit *unit, int index) {

	if (this->inputList[index] == NULL) {
		this->currentInput++;
	}
	this->inputList[index] = unit;
}
//==============================================================

//index��ȣ�� ����� �Է� Unit�����͸� �ҷ���
LogicUnit* LogicUnit::getInputList(int index) {

	return (LogicUnit*)this->inputList[index];
}
//==============================================================

//Output���� ������ Unit�� �����͸� �迭�� ����
void LogicUnit::setOutputList(LogicUnit *unit) {

	this->currentoutput++;
	this->outputList.Add(unit);
}
//output���� ������ Unit�� �����͸� �迭�� ����(������ ���� ���������ٰ�)
void LogicUnit::setOutputList(LogicUnit *unit, int index) {
	if (this->outputList[index] == NULL) {
		this->currentoutput++;
	}
	this->outputList[index] = unit;
}
//==============================================================

//index��ȣ�� ����� �Է� Unit�����͸� �ҷ���
LogicUnit* LogicUnit::getOutputList(int index) {

	return (LogicUnit*)this->outputList[index];
}
//==============================================================

//�ִ� Input ������ ����
void LogicUnit::setMaxInput(int size) {
	this->MaxInput = size;
}
//==============================================================

//�ִ� Input ������ �ҷ���
int LogicUnit::getMaxInput() {

	return this->MaxInput;
}
//==============================================================

//���� Input ������ ����
void LogicUnit::setCurrentInput(int size) {
	this->currentInput = size;
}
//==============================================================

//���� Input ������ �ҷ���
int LogicUnit::getCurrentInput() {

	return this->currentInput;
}
//==============================================================

//�ִ� Output ������ ����
void LogicUnit::setMaxOutput(int size) {

	this->Maxoutput = size;
}
//==============================================================

//�ִ� Output ������ �ҷ���
int LogicUnit::getMaxOutput() {

	return this->Maxoutput;
}
//==============================================================

//���� Output ������ ����
void LogicUnit::setCurrentOutput(int size) {

	this->currentoutput = size;
}
//==============================================================

//���� Output ������ �ҷ���
int LogicUnit::getCurrentOutput() {

	return this->currentoutput;
}
//==============================================================



//���� ����
void LogicUnit::setDirction(Direction dir) {

	this->direction = dir;
}
//���� �ҷ���
Direction LogicUnit::getDirction() {

	return this->direction;
}

//������ Ÿ���� ����
void LogicUnit::setUnitType(Unit_type type) {
	this->type = type;
}

//������ Ÿ���� �´��� Ȯ��
bool LogicUnit::isType(Unit_type type) {
	if (this->type == type)
		return true;
	else
		return false;
}

//�Է¹��� ��ǥ�� ���° �Է� Ȥ�� ������� Ȯ��
int LogicUnit::get_putIndex(CPoint pt,bool &result) {
	result = false;

	for (int i = 0; i != this->getMaxOutput(); i++) {
		if (pt == this->output_pt[i])
			return i;
	}
	
	for (int i = 0; i != this->getMaxInput(); i++) {
		if (pt == this->input_pt[i]) {
			result = true;
			return i;
		}
	}

	return -1;
}

//�Է¹��� ��ǥ�� �Է����� Ȯ��
bool LogicUnit::is_input(CPoint pt) {

	for (int i = 0; i != this->getMaxInput(); i++) {
		if (pt == this->input_pt[i])
			return true;
	}
	for (int i = 0; i != this->getMaxOutput(); i++) {
		if (pt == this->output_pt[i])
			return false;
	}
	return false;
}


//unit1�� unit2�� Input���� ����
void LogicUnit::connect_Unit(LogicUnit *unit1, int out_number, LogicUnit *unit2, int in_number) {
	unit1->setOutputList(unit2, out_number);
	unit2->setInputList(unit1, in_number);

	unit2->setInput(in_number, (unit2->getInputList(in_number))->getOutput(out_number));
}


//unit1�� unit2�� line���� ���������
void LogicUnit::connect_line(LogicUnit *line, LogicUnit *unit1, int out_number, LogicUnit *unit2, int in_number) {
	connect_Unit(unit1, out_number, line, 0);
	line->setOutput(0, (line->getInputList(0))->getOutput(out_number));
	connect_Unit(line, 0, unit2, in_number);
}


void LogicUnit::disconnect_Unit(LogicUnit *unit1, int out_number, LogicUnit *unit2, int in_number) {

	unit1->setOutputList(NULL, out_number);
	unit2->setInputList(NULL, in_number);

	unit1->currentoutput--;
	unit2->currentInput--;

	unit2->setInput(in_number, false);
}
void LogicUnit::disconnect_line(LogicUnit *line, LogicUnit *unit1, int out_number, LogicUnit *unit2, int in_number) {
	
	if (unit1 != NULL)
		disconnect_Unit(unit1, out_number, line, 0);
	if (unit2 != NULL)
		disconnect_Unit(line, 0, unit2, in_number);

	delete line;
}

//�󺧺��̱�
void LogicUnit::onLabelName(CDC *dc) {
	dc->TextOutW(label.pt.x, label.pt.y, label.UnitName);
}
void LogicUnit::OnRotateInput() {
	int inputNum, temp;
	bool OutRange=false;
	inputNum = this->getMaxInput();

	CPoint* temp_input_pt = new CPoint[inputNum];

	for (int i = 0; i < inputNum; i++) {
		temp_input_pt[i].x = this->getPoint().x + (this->input_pt[i].y - this->getPoint().y);
		temp_input_pt[i].y = (this->getPoint().y - (this->input_pt[i].x-this->getPoint().x) + this->ImageSize.y);

		if (temp_input_pt[i].x < 20 || temp_input_pt[i].y < 20) {
			OutRange = true;
		}
		
	}

	if (OutRange != true) {
		this->input_pt = temp_input_pt;
	}

}
void LogicUnit::OnRotateOutput() {
	int outputNum, temp;
	bool OutRange = false;

	outputNum = this->getMaxOutput();

	CPoint* temp_output_pt = new CPoint[outputNum];

	for (int i = 0; i < outputNum; i++) {
		temp_output_pt[i].x = this->getPoint().x + (this->output_pt[i].y - this->getPoint().y);
		temp_output_pt[i].y = this->getPoint().y -(this->output_pt[i].x - this->getPoint().x) + this->ImageSize.y;

		if (temp_output_pt[i].x < 20 || temp_output_pt[i].y < 20) {
			OutRange = true;
		}
		
	}
	if (OutRange != true) {
		this->output_pt = temp_output_pt;
	}
}

void InputSwitch::Op(){
	if(this->getCurrentOutput() != 0)
		this->getOutputList(0)->setInput(0, this->getOutput(0));
}

void LineUnit::Op() {

	for (int i = 0; i < this->getCurrentOutput(); i++) {
		if (this->getInput(0) == true) {
			this->setOutput(i, true);
		}
		else
			this->setOutput(i, false);
	}

}

//AND ����
void AndGate::Op() {
	if (this->getCurrentInput() == this->getMaxInput()) {
		if (this->getInput(0) && this->getInput(1)) {
			setOutput(0, true);
		}
		else {
			setOutput(0, false);
		}
	}
	else {
		setOutput(0, false);
	}
}

//or����
void OrGate::Op() {

	if (this->getCurrentInput() == this->getMaxInput()) {
		if (this->getInput(0) || this->getInput(1)) {
			setOutput(0, true);
		}
		else {
			setOutput(0, false);
		}
	}
	else {
		setOutput(0, false);
	}

}

//not����
void NotGate::Op() 
{

	if (this->getCurrentInput() == this->getMaxInput()) 
	{
		if (this->getInput(0)) 
		{
			setOutput(0, false);
		}
		else 
		{
			setOutput(0, true);
		}
	}
	else 
	{
		setOutput(0, false);
	}

}

//nand ����
void NANDGate::Op()
{

	if (this->getCurrentInput() == this->getMaxInput())
	{
		if (this->getInput(0) && this->getInput(1))
		{
			setOutput(0, false);
		}
		else
		{
			setOutput(0, true);
		}
	}
	else
	{
		setOutput(0, false);
	}

}

//nor ����
void NorGate::Op()
{

	if (this->getCurrentInput() == this->getMaxInput())
	{
		if ((this->getInput(0) && this->getInput(1)) == false)
		{
			setOutput(0, true);
		}
		else
		{
			setOutput(0, false);
		}
	}
	else
	{
		setOutput(0, false);
	}

}

//xor ����
void XorGate::Op()
{

	if (this->getCurrentInput() == this->getMaxInput())
	{
		if ((this->getInput(0))) //���̸�
		{
			if (this->getInput(1)) //���̸�
			{
				setOutput(0, true);
			}
			else //�����̸�
			{
				setOutput(0, false);
			}
		}
		else //�����̸�
		{
			if (this->getInput(1)) //���̸�
			{
				setOutput(0, false);
			}
			else //�����̸�
			{
				setOutput(0, true);
			}
		}
	}
	else
	{
		setOutput(0, false);
	}

}

//DFF����
//getinput(0) : �Է½�ȣ
void DFFGate::Op(int num)
{
	if (this->getCurrentInput() == this->getMaxInput())
	{
		if (num % 2 == 0) //clock�� �޾Ƽ�, '0'�� ������ ������ �������� �ʰ� �Ѿ
		{

		}
		else
		{
			if ((this->getInput(0))) //���̸� 1 - 1
			{
				setOutput(0, true);
			}
			else //�����̸� 0 - 0
			{
				setOutput(0, false);
			}
		}
	}
	else
	{
		setOutput(0, false);
	}

}

//JKFF����
//getinput(0) : J�Է�
//getintput(1) : K�Է�
//setoutput(0) : Q���
//setoutput(1) : Q'���
void JKFFGate::Op(int num) //Ŭ����ȣ ������
{

	if (this->getCurrentInput() == this->getMaxInput())
	{
		if (num % 2 == 0) //clock�� �޾Ƽ�, '0'�� ������ ������ �������� �ʰ� �Ѿ
		{

		}
		else
		{
			/*
			if (!(this->getInput(0))) // J�� false 0�̶��
			{
				if (!(this->getOutput(1))) // Q'�� 0�̶��
				{
					this->setInput(0, false);
				}
				else if (this->getOutput(1)) // Q'�� 1�̶��
				{
					this->setInput(0, false);
				}
			}
			else if (this->getInput(0)) //J�� True 1�̶��
			{
				if (!(this->getOutput(1))) // Q'�� 0�̶��
				{
					this->setInput(0, false);
				}
				else if (this->getOutput(1)) // Q'�� 1�̶��
				{
					this->setInput(0, true);
				}

				if (!(this->getInput(1))) // K�� false 0�̶��
				{
					if (!(this->getOutput(0))) // Q�� 0�̶��
					{
						this->setInput(1, false);
					}
					else if (this->getOutput(0)) // Q'�� 1�̶��
					{
						this->setInput(1, false);
					}
				}
				else if (this->getInput(1)) //K�� True 1�̶��
				{
					if (!(this->getOutput(0))) // Q'�� 0�̶��
					{
						this->setInput(1, false);
					}
					else if (this->getOutput(0)) // Q'�� 1�̶��
					{
						this->setInput(1, true);
					}
					//�۾���
				}
				*/
			


		}
	}
		else
		{
			setOutput(0, false);
			setOutput(1, false);
		}

}



//TFF����
//getinput(0) : T�Է�
//getinput(1) : clock
//setoutput(0) : Q���
//setoutput(1) : Q'���
void TFFGate::Op(int num) //Ŭ����ȣ ������
{

	if (this->getCurrentInput() == this->getMaxInput())
	{
		if (num % 2 == 0)		//clock�� �޾Ƽ�, '0'�� ������ ������ �������� �ʰ� �Ѿ
		{

		}
		else // T�Է½�ȣ
		{
			/*
			if (this->getInput(0)) //�Է��� true 1 �̸�
			{
				if (this->getOutput(0)) // ����� 1�̸�
				{
					this->setInput(0, false);
				}
				else if (this->getOutput(0) == false)
				{
					this->setInput(0, true);
				}
			}
			else if (this->getInput(0) == false) // �Է��� false 0�̸�
			{
				if (this->getOutput(0)) // ����� 1�̸�
				{
					this->setInput(0, true);
				}
				else if (this->getOutput(0) == false) // ����� 0�̸�
				{
					this->setInput(0, false);
				}
			}
			*/
			
		}
			
		
	}
	else
	{
		setOutput(0, false);
		setOutput(1, false);
	}

}


//==================segment �׸���==================================================================

void Segment::acivateSegment(seg Number, CClientDC &dc) {
	CBrush *old;
	CBrush white(RGB(255, 255, 255));
	CBrush red(RGB(255, 0, 0));

	old = dc.SelectObject(&white);

	dc.Polygon(Number.a, 6);
	dc.Polygon(Number.b, 6);
	dc.Polygon(Number.c, 6);
	dc.Polygon(Number.d, 6);
	dc.Polygon(Number.e, 6);
	dc.Polygon(Number.f, 6);
	dc.Polygon(Number.g, 6);

	dc.SelectObject(&red);

	if(this->getInput(0))
		dc.Polygon(Number.a, 6);
	if (this->getInput(1))
		dc.Polygon(Number.b, 6);
	if (this->getInput(2))
		dc.Polygon(Number.c, 6);
	if (this->getInput(3))
		dc.Polygon(Number.d, 6);
	if (this->getInput(4))
		dc.Polygon(Number.e, 6);
	if (this->getInput(5))
		dc.Polygon(Number.f, 6);
	if (this->getInput(6))
		dc.Polygon(Number.g, 6);
	dc.SelectObject(old);
}
void Segment::drawNumber(seg s, CPoint startPoint, CDC* dc){
	CPoint oldpoint = startPoint;
	POINT* temp; 

	this->Number.a = drawSegment1(startPoint, dc);

	startPoint.x += 0;
	startPoint.y += 5;
	this->Number.f = drawSegment2(startPoint, dc);

	startPoint.x += 40;
	startPoint.y += 0;
	this->Number.b = drawSegment2(startPoint, dc);

	startPoint.x -= 40;
	startPoint.y += 25;
	this->Number.g = drawSegment1(startPoint, dc);


	startPoint.x += 0;
	startPoint.y += 5;
	this->Number.e = drawSegment2(startPoint, dc);

	startPoint.x += 40;
	startPoint.y += 0;
	this->Number.c = drawSegment2(startPoint, dc);


	startPoint.x -= 40;
	startPoint.y += 25;
	this->Number.d = drawSegment1(startPoint, dc);
}
POINT* Segment::drawSegment1(CPoint startPoint, CDC* dc){
	POINT oldPoint = startPoint;

	dc->MoveTo(startPoint);

	POINT* poly;

	poly = new POINT[6];

	poly[0] = MyMoveTo(startPoint, 5, -5);
	poly[1] = MyMoveTo(startPoint, 30, 0);
	poly[2] = MyMoveTo(startPoint, 5, 5);
	poly[3] = MyMoveTo(startPoint, -5, 5);
	poly[4] = MyMoveTo(startPoint, -30, 0);
	poly[5] = MyMoveTo(startPoint, -5, -5);

	dc->MoveTo(oldPoint);
	dc->Polygon(poly, 6);

	return poly;
}
POINT* Segment::drawSegment2(CPoint startPoint, CDC* dc) {
	POINT oldPoint = startPoint;

	dc->MoveTo(startPoint);

	POINT* poly;

	poly = new POINT[6];

	poly[0] = MyMoveTo(startPoint, 5, 5);
	poly[1] = MyMoveTo(startPoint, 0, 10);
	poly[2] = MyMoveTo(startPoint, -5, 5);
	poly[3] = MyMoveTo(startPoint, -5, -5);
	poly[4] = MyMoveTo(startPoint, 0, -10);
	poly[5] = MyMoveTo(startPoint, 5, -5);

	dc->MoveTo(oldPoint);

	dc->Polygon(poly, 6);

	return poly;
}