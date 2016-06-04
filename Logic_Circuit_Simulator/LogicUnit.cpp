#include "stdafx.h"
#include "LogicUnit.h"
#include <afxtempl.h>

LogicUnit::LogicUnit()
{
}

LogicUnit::LogicUnit(CPoint init_pt)
{
	this->pt = init_pt;
	this->currentInput = 0;
	this->currentoutput = 0;
	this->MaxInput = 0;
	this->Maxoutput = 0;
	this->direction = EAST;
	this->label.state = false;
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
	for (int i = 0; i != this->getMaxInput(); i++) {
		if (pt == this->input_pt[i]) {
			result = true;
			return i;
		}
	}

	for (int i = 0; i != this->getMaxOutput(); i++) {
		if (pt == this->output_pt[i])
			return i;
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

	disconnect_Unit(unit1, out_number, line, 0);
	disconnect_Unit(line, 0, unit2, in_number);

	delete line;
}

void LogicUnit::onLabelName(CDC *dc) {
	dc->TextOutW(label.pt.x, label.pt.y, label.UnitName);
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
void DFFGate::Op()
{
	SetTimer(0, 1000,0,0);

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