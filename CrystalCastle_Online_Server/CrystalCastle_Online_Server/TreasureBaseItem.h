#pragma once
#include "ObjBase.h"
#include "map.h"
//宝物のベースクラス

class TreasureBaseItem : public BaseVector
{
public:
	TreasureBaseItem(int ID,Point p,CMap* m);
	int Action(const ObjList&, ObjList&);
	void Draw();

private:
	int treasure_ID = -1;//宝物のID
	int score_value = 0;//スコア値
	
	void GetTreasureItem();//アイテム取得関数
	void CutSprite(int x, int y, int No);//
};