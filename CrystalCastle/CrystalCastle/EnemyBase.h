#pragma once
//エネミーベースh

#include "objBase.h"
#include "damageObj.h"
#include "map.h"

class EnemyBase : public CDamageObj
{
public:
	EnemyBase(Point, CMap*);
	int Action(const ObjList&, ObjList&);
	void Draw();

	//CMap* map = nullptr;

};