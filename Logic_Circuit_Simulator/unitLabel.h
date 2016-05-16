#pragma once
class unitLabel
{
public:
	CString UnitName;
	CPoint pt;

public:
	unitLabel();
	unitLabel(LPCWSTR str, CPoint point);
	~unitLabel();
};

