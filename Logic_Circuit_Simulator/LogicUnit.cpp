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


//좌표를 입력 받음
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

//Input값을 size수 만큼 초기화 시킴
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

//Index번호의 입력값을 바꿔줌
void LogicUnit::setInput(int index, bool state) {
	this->input[index] = state;
}
//==============================================================

//Input값을 얻음
bool LogicUnit::getInput(int index) {
	return this->input[index];
}
//==============================================================


//Output값을 size수 만큼 초기화 시킴 
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

//Index번호의 입력값을 바꿔줌
void LogicUnit::setOutput(int index, bool state) {

	this->output[index] = state;
}
//==============================================================

//Output 값을 얻음
bool LogicUnit::getOutput(int index) {

	return this->output[index];
}
//==============================================================

//clock번호의 입력값을 바꿔줌(미완)				
void LogicUnit::setclock(int index, bool state) {
	this->clock[index] = state;
}
//==============================================================

//clock값을 얻음(미완)
bool LogicUnit::getclock(int index) {
	return this->clock[index];
}
//==============================================================

//Input으로 들어오는 Unit의 포인터를 배열에 저장
void LogicUnit::setInputList(LogicUnit *unit) {

	this->currentInput++;
	this->inputList.Add(unit);
}

//Input으로 들어오는 Unit의 포인터를 배열에 저장(input갯수는 따로 증가시켜줄것)
void LogicUnit::setInputList(LogicUnit *unit, int index) {

	if (this->inputList[index] == NULL) {
		this->currentInput++;
	}
	this->inputList[index] = unit;
}
//==============================================================

//index번호의 저장된 입력 Unit포인터를 불러옴
LogicUnit* LogicUnit::getInputList(int index) {

	return (LogicUnit*)this->inputList[index];
}
//==============================================================

//Output으로 나가는 Unit의 포인터를 배열에 저장
void LogicUnit::setOutputList(LogicUnit *unit) {

	this->currentoutput++;
	this->outputList.Add(unit);
}
//output으로 나가는 Unit의 포인터를 배열에 저장(갯수는 따로 증가시켜줄것)
void LogicUnit::setOutputList(LogicUnit *unit, int index) {
	if (this->outputList[index] == NULL) {
		this->currentoutput++;
	}
	this->outputList[index] = unit;
}
//==============================================================

//index번호의 저장된 입력 Unit포인터를 불러옴
LogicUnit* LogicUnit::getOutputList(int index) {

	return (LogicUnit*)this->outputList[index];
}
//==============================================================

//최대 Input 갯수를 지정
void LogicUnit::setMaxInput(int size) {
	this->MaxInput = size;
}
//==============================================================

//최대 Input 갯수를 불러옴
int LogicUnit::getMaxInput() {

	return this->MaxInput;
}
//==============================================================

//현재 Input 갯수를 지정
void LogicUnit::setCurrentInput(int size) {
	this->currentInput = size;
}
//==============================================================

//현재 Input 갯수를 불러옴
int LogicUnit::getCurrentInput() {

	return this->currentInput;
}
//==============================================================

//최대 Output 갯수를 지정
void LogicUnit::setMaxOutput(int size) {

	this->Maxoutput = size;
}
//==============================================================

//최대 Output 갯수를 불러옴
int LogicUnit::getMaxOutput() {

	return this->Maxoutput;
}
//==============================================================

//현재 Output 갯수를 지정
void LogicUnit::setCurrentOutput(int size) {

	this->currentoutput = size;
}
//==============================================================

//현재 Output 갯수를 불러옴
int LogicUnit::getCurrentOutput() {

	return this->currentoutput;
}
//==============================================================



//방향 설정
void LogicUnit::setDirction(Direction dir) {

	this->direction = dir;
}
//방향 불러옴
Direction LogicUnit::getDirction() {

	return this->direction;
}

//유닛의 타입을 설정
void LogicUnit::setUnitType(Unit_type type) {
	this->type = type;
}

//유닛의 타입이 맞는지 확인
bool LogicUnit::isType(Unit_type type) {
	if (this->type == type)
		return true;
	else
		return false;
}

//입력받은 좌표가 몇번째 입력 혹은 출력인지 확인
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

//입력받은 좌표가 입력인지 확인
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


//unit1을 unit2의 Input으로 연결
void LogicUnit::connect_Unit(LogicUnit *unit1, int out_number, LogicUnit *unit2, int in_number) {
	unit1->setOutputList(unit2, out_number);
	unit2->setInputList(unit1, in_number);

	unit2->setInput(in_number, (unit2->getInputList(in_number))->getOutput(out_number));
}


//unit1과 unit2를 line으로 연결시켜줌
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

//라벨붙이기
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

//AND 연산
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

//or연산
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

//not연산
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

//nand 연산
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

//nor 연산
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

//xor 연산
void XorGate::Op()
{

	if (this->getCurrentInput() == this->getMaxInput())
	{
		if ((this->getInput(0))) //참이면
		{
			if (this->getInput(1)) //참이면
			{
				setOutput(0, true);
			}
			else //거짓이면
			{
				setOutput(0, false);
			}
		}
		else //거짓이면
		{
			if (this->getInput(1)) //참이면
			{
				setOutput(0, false);
			}
			else //거짓이면
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

//DFF연산
//getinput(0) : 입력신호
void DFFGate::Op(int num)
{
	if (this->getCurrentInput() == this->getMaxInput())
	{
		if (num % 2 == 0) //clock을 받아서, '0'이 들어오면 과정을 수행하지 않고 넘어감
		{

		}
		else
		{
			if ((this->getInput(0))) //참이면 1 - 1
			{
				setOutput(0, true);
			}
			else //거짓이면 0 - 0
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

//JKFF연산
//getinput(0) : J입력
//getintput(1) : K입력
//setoutput(0) : Q출력
//setoutput(1) : Q'출력
void JKFFGate::Op(int num) //클럭신호 미포함
{

	if (this->getCurrentInput() == this->getMaxInput())
	{
		if (num % 2 == 0) //clock을 받아서, '0'이 들어오면 과정을 수행하지 않고 넘어감
		{

		}
		else
		{
			/*
			if (!(this->getInput(0))) // J가 false 0이라면
			{
				if (!(this->getOutput(1))) // Q'이 0이라면
				{
					this->setInput(0, false);
				}
				else if (this->getOutput(1)) // Q'이 1이라면
				{
					this->setInput(0, false);
				}
			}
			else if (this->getInput(0)) //J가 True 1이라면
			{
				if (!(this->getOutput(1))) // Q'이 0이라면
				{
					this->setInput(0, false);
				}
				else if (this->getOutput(1)) // Q'이 1이라면
				{
					this->setInput(0, true);
				}

				if (!(this->getInput(1))) // K가 false 0이라면
				{
					if (!(this->getOutput(0))) // Q이 0이라면
					{
						this->setInput(1, false);
					}
					else if (this->getOutput(0)) // Q'이 1이라면
					{
						this->setInput(1, false);
					}
				}
				else if (this->getInput(1)) //K가 True 1이라면
				{
					if (!(this->getOutput(0))) // Q'이 0이라면
					{
						this->setInput(1, false);
					}
					else if (this->getOutput(0)) // Q'이 1이라면
					{
						this->setInput(1, true);
					}
					//작업중
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



//TFF연산
//getinput(0) : T입력
//getinput(1) : clock
//setoutput(0) : Q출력
//setoutput(1) : Q'출력
void TFFGate::Op(int num) //클럭신호 미포함
{

	if (this->getCurrentInput() == this->getMaxInput())
	{
		if (num % 2 == 0)		//clock을 받아서, '0'이 들어오면 과정을 수행하지 않고 넘어감
		{

		}
		else // T입력신호
		{
			/*
			if (this->getInput(0)) //입력이 true 1 이면
			{
				if (this->getOutput(0)) // 출력이 1이면
				{
					this->setInput(0, false);
				}
				else if (this->getOutput(0) == false)
				{
					this->setInput(0, true);
				}
			}
			else if (this->getInput(0) == false) // 입력이 false 0이면
			{
				if (this->getOutput(0)) // 출력이 1이면
				{
					this->setInput(0, true);
				}
				else if (this->getOutput(0) == false) // 출력이 0이면
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


//==================segment 그리기==================================================================

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