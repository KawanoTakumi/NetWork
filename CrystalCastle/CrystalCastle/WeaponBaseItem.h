#pragma once
#include "objBase.h"
#include "map.h"


class WeaponBaseItem : public BaseVector
{
public:
	WeaponBaseItem(int WeaponID,int WeaponNo,Point p,CMap* m);
	int Action(const ObjList&, ObjList&);
	void Draw();
	void CutSprite(int ID,int No);
private:
	int weapon_id = { -1 };//•Ší‚Ìí—ŞID
	int weapon_no = { -1 };//•Ší‚Ì”Ô†ID(Œ•‚Ì0”ÔA1”Ô‚È‚Ç)
	bool isHit = false;
	bool isGet = false;
	bool isPushE = false;
};