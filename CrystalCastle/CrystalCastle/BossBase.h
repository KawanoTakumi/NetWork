#pragma once
#include "damageObj.h"
#include "SearchPlayer.h"

class CSpawnPoint;

class BossBase : public CDamageObj
{
public:
	//Œü‚«
	enum DIR { DOWN, LEFT, RIGHT, UP };

	BossBase(Point, CMap*, CSpawnPoint*, int);
	int Action(const ObjList&, ObjList&);
	void Draw();
	void UpdateDir(Point);	//Œü‚«XV

	CSpawnPoint* spawn{ nullptr };
	float move_speed{ 1.3f };
	int No{ 0 };
};