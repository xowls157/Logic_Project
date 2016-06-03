#pragma once
class unitLabel
{
public:
	CString UnitName;
	CPoint pt;
	bool state;

public:
	unitLabel();
	unitLabel(LPCWSTR str, CPoint point);
	~unitLabel();
};

