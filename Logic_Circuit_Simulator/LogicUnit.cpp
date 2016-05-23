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
}

LogicUnit::~LogicUnit()
{
}


//��ǥ�� �Է� ����
void LogicUnit::setPoint(CPoint setPt) {
	this->pt = setPt;
}
CPoint LogicUnit::getPoint() {

	return pt;
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

//AND ����
void AndGate::andOp() {
	bool result;

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
void OrGate::orOp() {

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