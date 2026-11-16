#pragma once
#include "objBase.h"

class CSpawnPoint : public BaseVector
{
public:
	CSpawnPoint(Point, int,int, CMap*);

	int Action(const ObjList&, ObjList&);
	void Draw();
	void Destroy();//削除
	int EnemyNo{ 0 };//出現する敵の種類
	int id{0};//ボスの場合どのボスを出すのか指定
	bool enemyAlive{ false };//敵が存在しているかのフラグ

};