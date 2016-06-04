#pragma once

#include "unitLabel.h"

enum Direction { NORTH, SOUTH, EAST, WEST };
enum Unit_type { InputSwitch_type, OutputSwitch_type, LineUnit_type, 
	Branch_type, AndGate_type, OrGate_type, 
	NotGate_type, NandGate_type, NorGate_type, 
	XorGate_type, DFFGate_type, JKFFGate_type, TFFGate_type};


class LogicUnit
{

	//멤버변수들
private:
	CPoint pt;				//좌표

	bool *input;			//입력받은 신호값
	bool *output;			//출력할 신호값
	bool *clock;			//clock 신호값
	CPtrArray inputList;	//입력받은 객체들의 배열
	CPtrArray outputList;	//출력해줄 객체들의 배열
	int MaxInput;			//입력받은 신호들의 최대갯수
	int currentInput;		//입력받은 신호들의 현재갯수
	int Maxoutput;			//출력해줄 신호들의 최대갯수
	int currentoutput;		//입력받은 신호들의 현재갯수



	Unit_type type;			//유닛 타입
	Direction direction = EAST;	//방향

public:
	CPoint *input_pt;		//입출력 좌표
	CPoint *output_pt;		//입출력 좌표
	CPoint ImageSize;
	unitLabel label;		//라벨


	int get_putIndex(CPoint pt, bool &result);
	bool is_input(CPoint pt);


							//좌표 처리
	void setPoint(CPoint setPt);
	virtual void setPut_point(CPoint pt);
	CPoint getPoint();

	//연산기능
	virtual void Op();

	//Input값 처리
	void initInput(int size);
	void setInput(int index, bool state);
	bool getInput(int index);

	//Output값 처리
	void initOutput(int size);
	void setOutput(int index, bool state);
	bool getOutput(int index);

	//clock값 처리											//미완성
	void setclock(int index, bool state);
	bool getclock(int index);

	//Input 개체들 연결
	void setInputList(LogicUnit *unit);
	void setInputList(LogicUnit *unit, int index);
	LogicUnit* getInputList(int index);

	//Output 개체들 연결
	void setOutputList(LogicUnit *unit);
	void setOutputList(LogicUnit *unit, int index);
	LogicUnit* getOutputList(int index);

	//신호갯수 설정
	void setMaxInput(int size);
	int getMaxInput();
	void setCurrentInput(int size);
	int getCurrentInput();
	void setMaxOutput(int size);
	int getMaxOutput();
	void setCurrentOutput(int size);
	int getCurrentOutput();

	//방향 설정
	void setDirction(Direction dir);
	Direction getDirction();

	//타입
	void setUnitType(Unit_type type);
	bool isType(Unit_type type);

	//각 유닛들 연결하기위한 함수
	void static connect_Unit(LogicUnit *unit1, int out_number, LogicUnit *unit2, int in_number);
	void static connect_line(LogicUnit *line, LogicUnit *unit1, int out_number, LogicUnit *unit2, int in_number);

	//연결 해제
	void static disconnect_Unit(LogicUnit *unit1, int out_number, LogicUnit *unit2, int in_number);
	void static disconnect_line(LogicUnit *line, LogicUnit *unit1, int out_number, LogicUnit *unit2, int in_number);

	void onLabelName(CDC *dc);

 

public:
	LogicUnit();
	LogicUnit(CPoint init_Pt);
	~LogicUnit();
};


//입력신호를 주는 유닛
class InputSwitch : public LogicUnit {
public:
	//호출시 기존값에서 변경함
	void Op();
	void setSwitch() {
		if (this->getOutput(0) == false) {
			this->setOutput(0, true);
		}
		else {
			this->setOutput(0, false);
		}
	}
	void setPut_point(CPoint pt) {
		this->input_pt = NULL;
		this->output_pt = new CPoint[1];
		this->output_pt[0].SetPoint(pt.x+60, pt.y+ 20);
	}

public:
	InputSwitch(CPoint init_Pt) :LogicUnit(init_Pt) {
		this->label.pt.SetPoint(init_Pt.x, init_Pt.y - 40);
		this->label.UnitName.SetString(_T("input"));
		this->setUnitType(InputSwitch_type);
		this->setMaxInput(0);
		this->setMaxOutput(1);
		this->initInput(0);
		this->initOutput(1);
		this->ImageSize.x = 40;
		this->ImageSize.y = 40;
		setPut_point(init_Pt);
	}
};

//출력신호를 주는 유닛
class OutputSwitch : public LogicUnit {
public:
	//호출시 기존값에서 변경함
	bool updateOutput() {
		if (this->getInputList(0) != NULL) {
			this->setInput(0, (this->getInputList(0))->getOutput(0));

			if (this->getInput(0))
				return true;
			else
				return false;
		}
		return false;
	}
	void setPut_point(CPoint pt) {
		this->input_pt = new CPoint[1];
		this->output_pt = NULL;
		this->input_pt[0].SetPoint(pt.x-20, pt.y+20);
	}
public:
	OutputSwitch(CPoint init_Pt) :LogicUnit(init_Pt) {
		this->label.pt.SetPoint(init_Pt.x, init_Pt.y - 40);
		this->label.UnitName.SetString(_T("output"));
		this->setUnitType(OutputSwitch_type);
		this->setMaxInput(1);
		this->setMaxOutput(0);
		this->initInput(1);
		this->initOutput(0);
		this->ImageSize.x = 40;
		this->ImageSize.y = 40;
		setPut_point(init_Pt);
	}

};

//유닛들을 연결하는 라인
class LineUnit : public LogicUnit {
public:
	void setEndPoint(CPoint end_pt) {
		endPoint = end_pt;
	}
	void Op();

public:
	CPoint endPoint;
	LineUnit(CPoint init_Pt, CPoint end_pt) :LogicUnit(init_Pt),endPoint(end_pt) {
		this->setUnitType(LineUnit_type);
		this->setMaxInput(1);
		this->setMaxOutput(1);
		this->initInput(1);
		this->initOutput(1);

		this->input_pt = new CPoint[1];
		this->output_pt = new CPoint[1];
		this->input_pt[0].SetPoint(init_Pt.x, init_Pt.y);
		this->output_pt[0].SetPoint(end_pt.x, end_pt.y);
	}
};

class branch : public LineUnit {
public:
	branch(CPoint init_Pt,int OutNum) : LineUnit(init_Pt, init_Pt) {
		this->setUnitType(Branch_type);
		this->setMaxInput(1);
		this->setMaxOutput(OutNum);
		this->initInput(1);
		this->initOutput(OutNum);

		this->input_pt = new CPoint[1];
		this->output_pt = new CPoint[1];

		this->input_pt[0].SetPoint(init_Pt.x, init_Pt.y);
		this->output_pt[0].SetPoint(init_Pt.x, init_Pt.x);
	}
};

//AND 게이트
class AndGate : public LogicUnit {

public:
	void Op();
	void setPut_point(CPoint pt) {
		this->input_pt = new CPoint[2];
		this->input_pt[0].SetPoint(pt.x - 20, pt.y + 20);
		this->input_pt[1].SetPoint(pt.x - 20, pt.y + 60);
		this->output_pt = new CPoint[1];
		this->output_pt[0].SetPoint(pt.x + 80, pt.y + 40);
	}
public:
	AndGate(CPoint init_Pt) :LogicUnit(init_Pt) {
		this->label.pt.SetPoint(init_Pt.x, init_Pt.y - 40);
		this->label.UnitName.SetString(_T("AndGate"));
		this->setUnitType(AndGate_type);
		this->setMaxInput(2);
		this->setMaxOutput(1);
		this->initInput(2);
		this->initOutput(1);
		this->ImageSize.x = 60;
		this->ImageSize.y = 80;
		setPut_point(init_Pt);
	}
};

//OR 게이트
class OrGate : public LogicUnit {

public:
	void Op();
	void setPut_point(CPoint pt) {
		this->input_pt = new CPoint[2];
		this->input_pt[0].SetPoint(pt.x - 20, pt.y + 20);
		this->input_pt[1].SetPoint(pt.x - 20, pt.y + 60);
		this->output_pt = new CPoint[1];
		this->output_pt[0].SetPoint(pt.x + 80, pt.y + 40);
	}

public:
	OrGate(CPoint init_Pt) :LogicUnit(init_Pt) {
		this->label.pt.SetPoint(init_Pt.x, init_Pt.y - 40);
		this->label.UnitName.SetString(_T("OrGate"));
		this->setUnitType(OrGate_type);
		this->setMaxInput(2);
		this->setMaxOutput(1);
		this->initInput(2);
		this->initOutput(1);
		this->ImageSize.x = 60;
		this->ImageSize.y = 80;
		setPut_point(init_Pt);
	}
};

//NOT 게이트
class NotGate : public LogicUnit {

public:
	void Op();
	void setPut_point(CPoint pt) {
		this->input_pt = new CPoint[2];
		this->input_pt[0].SetPoint(pt.x - 20, pt.y + 20);
		this->input_pt[1].SetPoint(pt.x - 20, pt.y + 60);
		this->output_pt = new CPoint[1];
		this->output_pt[0].SetPoint(pt.x + 80, pt.y + 40);
	}
public:
	NotGate(CPoint init_Pt) :LogicUnit(init_Pt) {
		this->label.pt.SetPoint(init_Pt.x, init_Pt.y - 40);
		this->label.UnitName.SetString(_T("NotGate"));
		this->setUnitType(NotGate_type);
		this->setMaxInput(1);
		this->setMaxOutput(1);
		this->initInput(1);
		this->initOutput(1);
		this->ImageSize.x = 60;
		this->ImageSize.y = 80;
	}
};

//Nand 게이트
class NANDGate : public LogicUnit
{

public:
	void Op();
	void setPut_point(CPoint pt) {
		this->input_pt = new CPoint[2];
		this->input_pt[0].SetPoint(pt.x - 20, pt.y + 20);
		this->input_pt[1].SetPoint(pt.x - 20, pt.y + 60);
		this->output_pt = new CPoint[1];
		this->output_pt[0].SetPoint(pt.x + 80, pt.y + 40);
	}
public:
	NANDGate(CPoint init_Pt) :LogicUnit(init_Pt) {
		this->label.pt.SetPoint(init_Pt.x, init_Pt.y - 40);
		this->label.UnitName.SetString(_T("NandGate"));
		this->setUnitType(NandGate_type);
		this->setMaxInput(2);
		this->setMaxOutput(1);
		this->initInput(2);
		this->initOutput(1);

		this->ImageSize.x = 60;
		this->ImageSize.y = 80;
	}
};

//Nor 게이트
class NorGate : public LogicUnit
{

public:
	void Op();
	void setPut_point(CPoint pt) {
		this->input_pt = new CPoint[2];
		this->input_pt[0].SetPoint(pt.x - 20, pt.y + 20);
		this->input_pt[1].SetPoint(pt.x - 20, pt.y + 60);
		this->output_pt = new CPoint[1];
		this->output_pt[0].SetPoint(pt.x + 80, pt.y + 40);
	}
public:
	NorGate(CPoint init_Pt) :LogicUnit(init_Pt) {
		this->label.pt.SetPoint(init_Pt.x, init_Pt.y - 40);
		this->label.UnitName.SetString(_T("NorGate"));
		this->setUnitType(NorGate_type);
		this->setMaxInput(2);
		this->setMaxOutput(1);
		this->initInput(2);
		this->initOutput(1);

		this->ImageSize.x = 60;
		this->ImageSize.y = 80;
	}
};

// Xor 게이트
class XorGate : public LogicUnit
{

public:
	void Op();
	void setPut_point(CPoint pt) {
		this->input_pt = new CPoint[2];
		this->input_pt[0].SetPoint(pt.x - 20, pt.y + 20);
		this->input_pt[1].SetPoint(pt.x - 20, pt.y + 60);
		this->output_pt = new CPoint[1];
		this->output_pt[0].SetPoint(pt.x + 80, pt.y + 40);
	}
public:
	XorGate(CPoint init_Pt) :LogicUnit(init_Pt) {
		this->label.pt.SetPoint(init_Pt.x, init_Pt.y - 40);
		this->label.UnitName.SetString(_T("XorGate"));
		this->setUnitType(XorGate_type);
		this->setMaxInput(2);
		this->setMaxOutput(1);
		this->initInput(2);
		this->initOutput(1);

		this->ImageSize.x = 60;
		this->ImageSize.y = 80;
	}
};

//D플립플롭
class DFFGate : public LogicUnit
{

public:
	void Op();

public:
	DFFGate(CPoint init_Pt) :LogicUnit(init_Pt) {
		this->label.pt.SetPoint(init_Pt.x, init_Pt.y - 40);
		this->label.UnitName.SetString(_T("D-FF"));
		this->setUnitType(DFFGate_type);
		this->setMaxInput(1);
		this->setMaxOutput(2);
		this->initInput(1);
		this->initOutput(2);

		this->ImageSize.x = 60;
		this->ImageSize.y = 80;
	}
};

//JK플립플롭
//clock 미포함
class JKFFGate : public LogicUnit
{

public:
	void JkffOp(int num); // num은 클록신호

public:
	JKFFGate(CPoint init_Pt) :LogicUnit(init_Pt)		//clock 별도 ?
	{
		this->setUnitType(JKFFGate_type);
		this->setMaxInput(2);
		this->setMaxOutput(2);
		this->initInput(2);
		this->initOutput(2);

		this->ImageSize.x = 60;
		this->ImageSize.y = 80;
		setPut_point(init_Pt);
	}
};

//T플립플롭
//clock 미포함
class TFFGate : public LogicUnit
{
	    
public:
	void TffOp(int num); // num은 클록신호

public:
	TFFGate(CPoint init_Pt) :LogicUnit(init_Pt)		//clock 별도 ?
	{
		this->setUnitType(TFFGate_type);
		this->setMaxInput(1);
		this->setMaxOutput(2);
		this->initInput(1);
		this->initOutput(2);

		this->ImageSize.x = 60;
		this->ImageSize.y = 80;
		setPut_point(init_Pt);
	}
};