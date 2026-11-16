#pragma once
#include "item.h"

class CMap;

class CItemHeal : public CItem
{
public:
	CItemHeal(Point, CMap*);
	int Action(const ObjList&, ObjList&);
	void Draw();
};