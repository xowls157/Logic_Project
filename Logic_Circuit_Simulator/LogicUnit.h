#pragma once

#include "unitLabel.h"

enum Direction { NORTH, SOUTH, EAST, WEST };
enum Unit_type { InputSwitch_type, OutputSwitch_type, LineUnit_type, AndGate_type, OrGate_type, NotGate_type, NandGate_type, NorGate_type };


class LogicUnit
{

	//멤버변수들
private:
	CPoint pt;				//좌표
	bool *input;			//입력받은 신호값
	bool *output;			//출력할 신호값
	CPtrArray inputList;	//입력받은 객체들의 배열
	CPtrArray outputList;	//출력해줄 객체들의 배열
	int MaxInput;			//입력받은 신호들의 최대갯수
	int currentInput;		//입력받은 신호들의 현재갯수
	int Maxoutput;			//출력해줄 신호들의 최대갯수
	int currentoutput;		//입력받은 신호들의 현재갯수



	Unit_type type;			//유닛 타입
	Direction direction = EAST;	//방향

public:
	CPoint ImageSize;
	unitLabel *label;		//라벨

							//좌표 처리
	void setPoint(CPoint setPt);
	CPoint getPoint();

	//Input값 처리
	void initInput(int size);
	void setInput(int index, bool state);
	bool getInput(int index);

	//Output값 처리
	void initOutput(int size);
	void setOutput(int index, bool state);
	bool getOutput(int index);

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

public:
	LogicUnit();
	LogicUnit(CPoint init_Pt);
	~LogicUnit();
};


//입력신호를 주는 유닛
class InputSwitch : public LogicUnit {
public:
	//호출시 기존값에서 변경함
	void setSwitch() {
		if (this->getOutput(0) == false) {
			this->setOutput(0, true);
		}
		else {
			this->setOutput(0, false);
		}
	}

public:
	InputSwitch(CPoint init_Pt) :LogicUnit(init_Pt) {
		this->setUnitType(InputSwitch_type);
		this->setMaxInput(0);
		this->setMaxOutput(1);
		this->initInput(0);
		this->initOutput(1);
		this->ImageSize.x = 20;
		this->ImageSize.y = 20;
	}

};

//출력신호를 주는 유닛
class OutputSwitch : public LogicUnit {
public:
	//호출시 기존값에서 변경함
	bool updateOutput() {
		this->setInput(0, (this->getInputList(0))->getOutput(0));

		if (this->getInput(0))
			return true;
		else
			return false;
	}

public:
	OutputSwitch(CPoint init_Pt) :LogicUnit(init_Pt) {

		this->setUnitType(OutputSwitch_type);
		this->setMaxInput(1);
		this->setMaxOutput(0);
		this->initInput(1);
		this->initOutput(0);
		this->ImageSize.x = 20;
		this->ImageSize.y = 20;
	}

};

//유닛들을 연결하는 라인
class LineUnit : public LogicUnit {

public:
	LineUnit(CPoint init_Pt) :LogicUnit(init_Pt) {
		this->setUnitType(LineUnit_type);
		this->setMaxInput(1);
		this->setMaxOutput(1);
		this->initInput(1);
		this->initOutput(1);
	}
};



//AND 게이트
class AndGate : public LogicUnit {

public:
	void andOp();

public:
	AndGate(CPoint init_Pt) :LogicUnit(init_Pt) {
		this->setUnitType(AndGate_type);
		this->setMaxInput(2);
		this->setMaxOutput(1);
		this->initInput(2);
		this->initOutput(1);

		this->ImageSize.x = 60;
		this->ImageSize.y = 80;
	}
};

//OR 게이트
class OrGate : public LogicUnit {

public:
	void orOp();

public:
	OrGate(CPoint init_Pt) :LogicUnit(init_Pt) {
		this->setUnitType(OrGate_type);
		this->setMaxInput(2);
		this->setMaxOutput(1);
		this->initInput(2);
		this->initOutput(1);

		this->ImageSize.x = 60;
		this->ImageSize.y = 80;
	}
};

//NOT 게이트
class NotGate : public LogicUnit {

public:
	void notOp();

public:
	NotGate(CPoint init_Pt) :LogicUnit(init_Pt) {
		this->setUnitType(NotGate_type);
		this->setMaxInput(1);
		this->setMaxOutput(1);
		this->initInput(1);
		this->initOutput(1);

		this->ImageSize.x = 60;
		this->ImageSize.y = 80;
	}
};

class NANDGate : public LogicUnit
{

public:
	void NandOp();

public:
	NANDGate(CPoint init_Pt) :LogicUnit(init_Pt) {
		this->setUnitType(NandGate_type);
		this->setMaxInput(2);
		this->setMaxOutput(1);
		this->initInput(2);
		this->initOutput(1);

		this->ImageSize.x = 60;
		this->ImageSize.y = 80;
	}
};

class NorGate : public LogicUnit
{

public:
	void NorOp();

public:
	NorGate(CPoint init_Pt) :LogicUnit(init_Pt) {
		this->setUnitType(NorGate_type);
		this->setMaxInput(2);
		this->setMaxOutput(1);
		this->initInput(2);
		this->initOutput(1);

		this->ImageSize.x = 60;
		this->ImageSize.y = 80;
	}
};