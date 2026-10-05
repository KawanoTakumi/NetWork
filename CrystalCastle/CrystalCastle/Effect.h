#pragma once
#include "objBase.h"
#include "map.h"

class CEffect :public CCharaOBJ
{
public:
	//位置,エフェクトNo,サイズ,スピード,マップ
	CEffect(Point, int, float, float, CMap*);

	int Action(const ObjList&, ObjList&);
	void Draw();

	int frame{ 0 };//フレーム数
	int speed{ 0 };//アニメーションスピード
	int startCutX{ 0 };//切り取りスタート位置x
	int startCutY{ 0 };//切り取りスタート位置y
};