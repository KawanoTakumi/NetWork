#pragma once
#include "NPCBase.h"
#include "SearchPlayer.h"

class CSpawnPoint;

class BossBase : public NPCBase
{
public:
	//Œü‚«
	enum DIR { DOWN, LEFT, RIGHT, UP };

	BossBase(Point, CMap*, CSpawnPoint*, int);
	int Action(const ObjList&, ObjList&);
	void Draw();

	CSpawnPoint* spawn{ nullptr };
	float move_speed{ 1.3f };
	int No{ 0 };
};