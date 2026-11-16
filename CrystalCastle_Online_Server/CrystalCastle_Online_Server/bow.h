//矢
#pragma once
#include "weapon.h"
#include "map.h"

class CBow :public CWeaponBase
{
public:
	//位置,移動ベクトル
	CBow(Point, Vector,int,int, CMap*);
	int Action(const ObjList&, ObjList&);
	void Draw();
};