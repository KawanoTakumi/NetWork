#pragma once
#include "DamageObj.h"

class CEnemyProjectile : public CDamageObj
{
public:
	CEnemyProjectile(Point,Vector,CMap*,int,int,bool);
	int Action(const ObjList&,ObjList&);
	void Draw();

private:
	float life{40.0f};
	int proj_id{-1};
	bool is_reverse{ false };//反転フラグ

	float rotate_timer = 0.0f;//回転タイマー
	const float MAX_ROTATE_TIMER = 1.0f;//最大回転タイマー量
	Vector v;

};