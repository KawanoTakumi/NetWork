#include "DamageObj.h"
#include "map.h"

void CDamageObj::knockBack(Vector v)
{
	knockVec = v;
	knockFrame = 10;
}

bool CDamageObj::UpdateKnockBack()
{
	if (knockFrame <= 0)
		return false;


	knockFrame--;

	//サブステップ判定
	int step = (int)max(abs(knockVec.x), abs(knockVec.y));
	step = max(step, 1);

	float moveX = knockVec.x / step;
	float moveY = knockVec.y / step;

	for (int i = 0; i < step; i++)
	{
		Point nextPos = pos;
		nextPos.x += moveX;
		if (map->CanMove(nextPos, sprite.width, sprite.height))pos.x = nextPos.x;
		nextPos = pos;
		nextPos.y += moveY;
		if (map->CanMove(nextPos, sprite.width, sprite.height))pos.y = nextPos.y;
	}
	knockVec.x *= 0.8f;
	knockVec.y *= 0.8f;


	return true;
}