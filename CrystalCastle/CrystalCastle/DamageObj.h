#pragma once
#include "objBase.h"

class CDamageObj : public CCharaOBJ
{
public:
	Vector knockVec{ 0,0 };

	int knockFrame{ 10 };

	void knockBack(Vector);
	bool UpdateKnockBack();

};