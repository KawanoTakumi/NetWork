#pragma once
#include "objBase.h"
#include "map.h"

class CSword :public CCharaOBJ
{
public:
	//位置,向き,武器No、マップ,オーナーオブジェクト
	CSword(Point,int,int,int,CMap*);

	int Action(const ObjList&, ObjList&);
	void Draw();

	//角度
	float angle{ 0 };
	float start_angle{ 0 };

	//剣の長さ
	const float SWORD_LENGTH = 48;
	int calc_damage = 0;//最終ダメージ;
};