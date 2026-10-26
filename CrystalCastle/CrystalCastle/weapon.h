#pragma once
#include "objBase.h"

class CWeaponBase : public BaseVector
{
public:
	CWeaponBase();
	int Action(const ObjList&, ObjList&);
	void Draw();
	int GetWeaponID();
	int WeaponID{ -1 };//武器ID
	int calc_damage = 0;//計算後のダメージ
	float angle{ 0 };//角度
	int life{ 90 };//出現時間
};