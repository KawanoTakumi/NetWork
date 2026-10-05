#pragma once
#include "objBase.h"

class CDamageObj : public BaseVector
{
public:
	Vector knockVec{ 0,0 };
	int knockFrame{ 10 };

	void KnockBack(Vector);
	bool UpdateKnockBack(CMap* _map);
	//void Damage(int dm, Vector v, int invisible);

	//体力
	int hp{ 0 };
	int maxHp{ 0 };

	void HP(int);

	//無敵時間
	int damageCoolTime{ 0 };
	//ダメージ処理(ダメージ量,ノックバック距離,無敵時間）
	void Damage(int dm, Vector v);
};