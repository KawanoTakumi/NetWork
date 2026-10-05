#pragma once
//エネミーベースh

#include "objBase.h"
#include "map.h"

class EnemyBase : public BaseVector
{
public:
	EnemyBase(Point, CMap*);
	int Action(const ObjList&, ObjList&);
	void Draw();

	CMap* map = nullptr;

};