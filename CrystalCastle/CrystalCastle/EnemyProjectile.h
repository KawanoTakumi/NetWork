#pragma once
#include "DamageObj.h"

class CEnemyProjectile : public CDamageObj
{
public:
	CEnemyProjectile(Point,Vector,CMap*);
	int Action(const ObjList&,ObjList&);
	void Draw();

private:
	float life{40.0f};
};