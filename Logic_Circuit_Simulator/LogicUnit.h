#pragma once

#include "unitLabel.h"

enum Direction { NORTH, SOUTH, EAST, WEST };


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

	Direction direction = EAST;	//방향

public:
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
		this->setMaxInput(0);
		this->setMaxOutput(1);
		this->initInput(0);
		this->initOutput(1);
	}

};

//유닛들을 연결하는 라인
class LineUnit : public LogicUnit {

public:
	LineUnit(CPoint init_Pt) :LogicUnit(init_Pt) {
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
		this->setMaxInput(2);
		this->setMaxOutput(1);
		this->initInput(2);
		this->initOutput(1);
	}
};

//OR 게이트
class OrGate : public LogicUnit {

public:
	void orOp();

public:
	OrGate(CPoint init_Pt) :LogicUnit(init_Pt) {
		this->setMaxInput(2);
		this->setMaxOutput(1);
		this->initInput(2);
		this->initOutput(1);
	}
};

