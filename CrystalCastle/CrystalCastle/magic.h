#pragma once
#include "objBase.h"
#include "map.h"

class CMagic : public CCharaOBJ
{
public:
	CMagic(Point, Vector,int _No, int base_damage,CMap*);
	int Action(const ObjList&, ObjList&);
	void Draw();

private:
	float angle{ 0 };
	int life{ 90 };//出現時間
	int calc_damage = 0;//最終計測ダメージ
};