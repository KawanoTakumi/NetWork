#pragma once
#include "objBase.h"

class CSpawnPoint : public BaseVector
{
public:
	CSpawnPoint(Point, int, CMap*);

	int Action(const ObjList&, ObjList&);
	void Draw();

	int EnemyNo{ 0 };//oŒ»‚·‚é“G‚Ìí—Ş

	bool enemyAlive{ false };//“G‚ª‘¶İ‚µ‚Ä‚¢‚é‚©‚Ìƒtƒ‰ƒO

};