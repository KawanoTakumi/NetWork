#pragma once
//エネミーベースh

#include "objBase.h"
#include "damageObj.h"
#include "map.h"

class CSpawnPoint;

class EnemyBase : public CDamageObj
{
public:
	EnemyBase(Point, CMap*, CSpawnPoint*);
	EnemyBase(Point, CMap*);
	int Action(const ObjList&, ObjList&);
	void Draw();

	//対象スポナー
	CSpawnPoint* spawn{ nullptr };

};