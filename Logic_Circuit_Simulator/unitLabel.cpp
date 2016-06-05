#include "stdafx.h"
#include "unitLabel.h"


unitLabel::unitLabel()
{
}

unitLabel::unitLabel(LPCWSTR str, CPoint point) {
	this->UnitName.Format(str);
	this->pt = point;
	this->state = false;

}

unitLabel::~unitLabel()
{
}
