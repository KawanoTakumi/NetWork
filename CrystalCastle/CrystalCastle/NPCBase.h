#pragma once
#include "damageObj.h"
#include "NPCBase.h"
#include "SearchPlayer.h"

class CSpawnPoint;

class NPCBase : public CDamageObj
{
public:

#pragma region 列挙

	//向き
	enum DIR { DOWN, LEFT, RIGHT, UP };

	//弾丸のID
	enum PROJ_ID {BULLET,BEAM};

#pragma endregion

#pragma region 関数

	void UpdateDir(Point);	//向き更新
	void HomingPlayer();//プレイヤー追尾
	void Shoot(ObjList&,PROJ_ID,int);//弾丸発射(ID)
	void Mul_Shoot(ObjList&, float, int,PROJ_ID,int);//弾丸扇発射(角度、回数)
	void Beam_Shoot(ObjList&, int, PROJ_ID,int);

#pragma endregion

#pragma region 定数

	const float MAX_SHOOT_TIMER = 80.0f;
#pragma endregion

#pragma region 変数
	bool create_search_obj{ false };//探索用のオブジェクトを生成したか
	float shoot_timer{ MAX_SHOOT_TIMER };//弾丸発射タイマー
	int shoot_count{ 0 };//弾丸発射回数
	CDamageObj* target{ nullptr };//追尾するターゲット

#pragma endregion

};