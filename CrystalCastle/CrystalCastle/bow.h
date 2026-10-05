//矢
#pragma once
#include "objBase.h"
#include "map.h"

class CBow :public BaseVector
{
public:
	//位置,移動ベクトル
	CBow(Point, Vector,int,int, CMap*);

	int Action(const ObjList&, ObjList&);
	void Draw();

	float angle{ 0 };
	int life{ 90 };//出現時間
	int calc_damage = 0;
};