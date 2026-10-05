#pragma once
#include "objBase.h"
#include "map.h"
//武器のベースクラス

class WeaponBaseItem : public CCharaOBJ
{
public:
	WeaponBaseItem(int WeaponID,int WeaponNo,Point p,CMap* m);
	int Action(const ObjList&, ObjList&);
	void Draw();
	void CutSprite(int ID,int No);
private:
	int weapon_id = { -1 };//武器の種類ID
	int weapon_no = { -1 };//武器の番号ID(剣の0番、1番など)
	bool isHit = false;
	bool isGet = false;
	bool isPushE = false;
};