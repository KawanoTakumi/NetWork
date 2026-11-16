#pragma once
#include "weapon.h"
#include "map.h"

class CSword :public CWeaponBase
{
public:
	//位置,向き,武器No、マップ,オーナーオブジェクト
	CSword(Point,int,int,int,CMap*);

	int Action(const ObjList&, ObjList&);
	void Draw();

	//角度
	float start_angle{ 0 };
	//剣の長さ
	const float SWORD_LENGTH = 48;
};