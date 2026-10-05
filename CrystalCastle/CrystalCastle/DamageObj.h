#pragma once
#include "objBase.h"

class CDamageObj : public BaseVector
{
public:
	Vector knockVec{ 0,0 };
	int knockFrame{ 10 };

	void KnockBack(Vector);
	bool UpdateKnockBack(CMap* _map);
	void Damage(int dm, Vector v, int invisible);
};