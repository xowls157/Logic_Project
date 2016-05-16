#pragma once

#include "unitLabel.h"

enum Direction { NORTH, SOUTH, EAST, WEST };


class LogicUnit
{

	//���������
private:
	CPoint pt;				//��ǥ
	bool *input;			//�Է¹��� ��ȣ��
	bool *output;			//����� ��ȣ��
	CPtrArray inputList;	//�Է¹��� ��ü���� �迭
	CPtrArray outputList;	//������� ��ü���� �迭
	int MaxInput;			//�Է¹��� ��ȣ���� �ִ밹��
	int currentInput;		//�Է¹��� ��ȣ���� ���簹��
	int Maxoutput;			//������� ��ȣ���� �ִ밹��
	int currentoutput;		//�Է¹��� ��ȣ���� ���簹��

	Direction direction = EAST;	//����

public:
	unitLabel *label;		//��

							//��ǥ ó��
	void setPoint(CPoint setPt);
	CPoint getPoint();

	//Input�� ó��
	void initInput(int size);
	void setInput(int index, bool state);
	bool getInput(int index);

	//Output�� ó��
	void initOutput(int size);
	void setOutput(int index, bool state);
	bool getOutput(int index);

	//Input ��ü�� ����
	void setInputList(LogicUnit *unit);
	void setInputList(LogicUnit *unit, int index);
	LogicUnit* getInputList(int index);

	//Output ��ü�� ����
	void setOutputList(LogicUnit *unit);
	void setOutputList(LogicUnit *unit, int index);
	LogicUnit* getOutputList(int index);

	//��ȣ���� ����
	void setMaxInput(int size);
	int getMaxInput();
	void setCurrentInput(int size);
	int getCurrentInput();
	void setMaxOutput(int size);
	int getMaxOutput();
	void setCurrentOutput(int size);
	int getCurrentOutput();

	//���� ����
	void setDirction(Direction dir);
	Direction getDirction();

	//�� ���ֵ� �����ϱ����� �Լ�
	void static connect_Unit(LogicUnit *unit1, int out_number, LogicUnit *unit2, int in_number);
	void static connect_line(LogicUnit *line, LogicUnit *unit1, int out_number, LogicUnit *unit2, int in_number);

	//���� ����
	void static disconnect_Unit(LogicUnit *unit1, int out_number, LogicUnit *unit2, int in_number);
	void static disconnect_line(LogicUnit *line, LogicUnit *unit1, int out_number, LogicUnit *unit2, int in_number);

public:
	LogicUnit();
	LogicUnit(CPoint init_Pt);
	~LogicUnit();
};


//�Է½�ȣ�� �ִ� ����
class InputSwitch : public LogicUnit {
public:
	//ȣ��� ���������� ������
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

//���ֵ��� �����ϴ� ����
class LineUnit : public LogicUnit {

public:
	LineUnit(CPoint init_Pt) :LogicUnit(init_Pt) {
		this->setMaxInput(1);
		this->setMaxOutput(1);
		this->initInput(1);
		this->initOutput(1);
	}
};



//AND ����Ʈ
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

//OR ����Ʈ
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

