#pragma once
#include "objBase.h"

class CItem : public BaseVector
{
public:
	CItem() {
		ID = (int)ObjID::ITEM;
	}

	void GetItem(BaseVector*);//アイテム取得関数
	ItemNo itemNo{ -1 };//アイテムの番号
	int value{ -1 };//アイテム関係変数

};