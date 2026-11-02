#pragma once
#include "EnemyBase.h"

class EnemyBase;

class CSearchPlayer : public  CDamageObj
{
public:
	CSearchPlayer(EnemyBase*, CMap*);
	int Action(const ObjList&, ObjList&);
	void Draw();

	void InPlayer();//プレイヤーが範囲内に入っていることを検知
	float search_length = 500.0f;//探索範囲
	CDamageObj* target = {nullptr};
private:
	EnemyBase* enemy_base{ nullptr };//親オブジェクト
};