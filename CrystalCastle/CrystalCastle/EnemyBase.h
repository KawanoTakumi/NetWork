#pragma once
#include "damageObj.h"
#include "SearchPlayer.h"

class CSpawnPoint;

class EnemyBase : public CDamageObj
{
public:
	//向き
	enum DIR { DOWN, LEFT, RIGHT, UP };

	EnemyBase(Point, CMap*, CSpawnPoint*);
	int Action(const ObjList&, ObjList&);
	void Draw();
	void UpdateDir(Point);	//向き更新
	void HomingPlayer();//プレイヤー追尾

	CSpawnPoint* spawn{ nullptr };
	CDamageObj* target{ nullptr };//追尾するターゲット
	bool create_search_obj = false;//探索用のオブジェクトを生成したか
};