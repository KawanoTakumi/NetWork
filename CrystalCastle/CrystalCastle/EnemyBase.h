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

	CSpawnPoint* spawn{ nullptr };
	CDamageObj* target{ nullptr };//追尾するターゲット
	bool create_search_obj{false};//探索用のオブジェクトを生成したか
	float move_speed{ 1.3f };
	int No{0};
	float shoot_timer{20.0f};//弾丸発射タイマー
};