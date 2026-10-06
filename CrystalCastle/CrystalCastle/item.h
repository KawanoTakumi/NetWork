#pragma once
#include "objBase.h"

class CItem : public BaseVector
{
public:
	CItem() {
		ID = (int)ObjID::ITEM;
	}

	void GetItem(BaseVector*);

	ItemNo itemNo{ -1 };

	int value{ -1 };//ƒAƒCƒeƒ€ŠÖŒW•Ï”

};