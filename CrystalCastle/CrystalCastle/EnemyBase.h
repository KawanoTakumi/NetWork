#pragma once

#include "objBase.h"
#include "damageObj.h"
#include "map.h"

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

	CSpawnPoint* spawn{ nullptr };
	CDamageObj* target{ nullptr };//追尾するターゲット

};