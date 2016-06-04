#pragma once

#include "unitLabel.h"

enum Direction { NORTH, SOUTH, EAST, WEST };
enum Unit_type { InputSwitch_type, OutputSwitch_type, LineUnit_type, 
	Branch_type, AndGate_type, OrGate_type, 
	NotGate_type, NandGate_type, NorGate_type, 
	XorGate_type, DFFGate_type, JKFFGate_type, TFFGate_type};


class LogicUnit
{

	//���������
private:
	CPoint pt;				//��ǥ

	bool *input;			//�Է¹��� ��ȣ��
	bool *output;			//����� ��ȣ��
	bool *clock;			//clock ��ȣ��
	CPtrArray inputList;	//�Է¹��� ��ü���� �迭
	CPtrArray outputList;	//������� ��ü���� �迭
	int MaxInput;			//�Է¹��� ��ȣ���� �ִ밹��
	int currentInput;		//�Է¹��� ��ȣ���� ���簹��
	int Maxoutput;			//������� ��ȣ���� �ִ밹��
	int currentoutput;		//�Է¹��� ��ȣ���� ���簹��



	Unit_type type;			//���� Ÿ��
	Direction direction = EAST;	//����

public:
	CPoint *input_pt;		//����� ��ǥ
	CPoint *output_pt;		//����� ��ǥ
	CPoint ImageSize;
	unitLabel label;		//��


	int get_putIndex(CPoint pt, bool &result);
	bool is_input(CPoint pt);


							//��ǥ ó��
	void setPoint(CPoint setPt);
	virtual void setPut_point(CPoint pt);
	CPoint getPoint();

	//������
	virtual void Op();

	//Input�� ó��
	void initInput(int size);
	void setInput(int index, bool state);
	bool getInput(int index);

	//Output�� ó��
	void initOutput(int size);
	void setOutput(int index, bool state);
	bool getOutput(int index);

	//clock�� ó��											//�̿ϼ�
	void setclock(int index, bool state);
	bool getclock(int index);

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

	//Ÿ��
	void setUnitType(Unit_type type);
	bool isType(Unit_type type);

	//�� ���ֵ� �����ϱ����� �Լ�
	void static connect_Unit(LogicUnit *unit1, int out_number, LogicUnit *unit2, int in_number);
	void static connect_line(LogicUnit *line, LogicUnit *unit1, int out_number, LogicUnit *unit2, int in_number);

	//���� ����
	void static disconnect_Unit(LogicUnit *unit1, int out_number, LogicUnit *unit2, int in_number);
	void static disconnect_line(LogicUnit *line, LogicUnit *unit1, int out_number, LogicUnit *unit2, int in_number);

	void onLabelName(CDC *dc);

 

public:
	LogicUnit();
	LogicUnit(CPoint init_Pt);
	~LogicUnit();
};


//�Է½�ȣ�� �ִ� ����
class InputSwitch : public LogicUnit {
public:
	//ȣ��� ���������� ������
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

//��½�ȣ�� �ִ� ����
class OutputSwitch : public LogicUnit {
public:
	//ȣ��� ���������� ������
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

//���ֵ��� �����ϴ� ����
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

//AND ����Ʈ
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

//OR ����Ʈ
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

//NOT ����Ʈ
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

//Nand ����Ʈ
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

//Nor ����Ʈ
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

// Xor ����Ʈ
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

//D�ø��÷�
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

//JK�ø��÷�
//clock ������
class JKFFGate : public LogicUnit
{

public:
	void JkffOp(int num); // num�� Ŭ�Ͻ�ȣ

public:
	JKFFGate(CPoint init_Pt) :LogicUnit(init_Pt)		//clock ���� ?
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

//T�ø��÷�
//clock ������
class TFFGate : public LogicUnit
{
	    
public:
	void TffOp(int num); // num�� Ŭ�Ͻ�ȣ

public:
	TFFGate(CPoint init_Pt) :LogicUnit(init_Pt)		//clock ���� ?
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