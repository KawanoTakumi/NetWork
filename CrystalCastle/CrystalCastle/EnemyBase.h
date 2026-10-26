#pragma once
#include "damageObj.h"
#include "SearchPlayer.h"

class CSpawnPoint;

class EnemyBase : public CDamageObj
{
public:
	//向き
	enum DIR { DOWN, LEFT, RIGHT, UP };

	EnemyBase(Point, CMap*, CSpawnPoint*,int);
	int Action(const ObjList&, ObjList&);
	void Draw();
	void UpdateDir(Point);	//向き更新
	void HomingPlayer();//プレイヤー追尾
	void Shoot(ObjList&);//弾丸発射
	void Mul_Shoot(ObjList&,float,int);//弾丸扇発射(角度、回数)

	const float MAX_SHOOT_TIMER = 80.0f;

	CSpawnPoint* spawn{ nullptr };
	CDamageObj* target{ nullptr };//追尾するターゲット
	bool create_search_obj{false};//探索用のオブジェクトを生成したか
	float move_speed{ 1.3f };
	int No{0};
	float shoot_timer{ MAX_SHOOT_TIMER };//弾丸発射タイマー
	int shoot_count{0};//弾丸発射回数
};