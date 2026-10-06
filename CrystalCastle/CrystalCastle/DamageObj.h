#pragma once
#include "objBase.h"

class CDamageObj : public BaseVector
{
public:
	Vector knockVec{ 0,0 };	//ノックバック移動ベクトル
	int knockFrame{ 0 };//ノックバックフレーム

	int hp{ 0 };//体力
	int maxHp{ 0 };//最大体力

	int damageCoolTime{ 0 };//無敵時間

	void KnockBack(Vector);//ノックバック開始
	bool UpdateKnockBack(CMap* _map);//ノックバック処理

	void HP(int);

	//ダメージ処理(ダメージ量,ノックバック距離,無敵時間）
	void Damage(int dm, Vector v);
};