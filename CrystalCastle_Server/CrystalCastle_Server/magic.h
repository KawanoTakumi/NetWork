#pragma once
#include "weapon.h"
#include "map.h"

class CMagic : public CWeaponBase
{
public:
	CMagic(Point, Vector,int _No, int base_damage,CMap*);
	int Action(const ObjList&, ObjList&);
	void Draw();
};