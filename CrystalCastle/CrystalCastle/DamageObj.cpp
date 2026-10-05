#include "damageObj.h"
#include "map.h"

void CDamageObj::KnockBack(Vector v)
{

	knockVec = v;
	knockFrame = 10;
}

bool CDamageObj::UpdateKnockBack(CMap* _map) {
	if (knockFrame <= 0)
		return false;

	map = _map;
	knockFrame--;

	//サブステップ判定
	//処理回数を計算
	int step = (int)max(abs(knockVec.x), abs(knockVec.y));
	step = max(step, 1);
	//1ステップの移動量を計算
	float moveX = knockVec.x / step;
	float moveY = knockVec.y / step;
	//ステップ判定
	for (int i = 0; i < step; i++) {
		//マップ判定
		Point nextPos = pos;
		nextPos.x += moveX;
		if (map->CanMove(nextPos, sprite.width, sprite.height))pos.x = nextPos.x;
		nextPos = pos;
		nextPos.y += moveY;
		if (map->CanMove(nextPos, sprite.width, sprite.height))pos.y = nextPos.y;
	}
	knockVec.x *= 0.8f;
	knockVec.y *= 0.8f;

	return 0;

}

//ダメージ処理
void CDamageObj::Damage(int dm, Vector v, int invisible = 10)
{
		//if (damageCoolTime > 0) return;
		//hp -= dm;
		//KnockBack(v);
		//damageCoolTime = invisible;
}