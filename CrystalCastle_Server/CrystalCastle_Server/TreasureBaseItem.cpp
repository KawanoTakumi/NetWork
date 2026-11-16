#include "TreasureBaseItem.h"
#include "function.h"

TreasureBaseItem::TreasureBaseItem(int _NoID,Point p,CMap* _map)
{
	pos = p;
	treasure_ID = _NoID;
	map = _map;
	//念の為に設定
	sprite.img = Resource::treasure_Img;
	sprite.height = 32;
	sprite.width = 32;
	CutSprite(8,3,treasure_ID);
	ID = (int)ObjID::ITEM;

	//IDの値毎にスコアの値を変える//仮
	if (treasure_ID < 6)
		score_value = 200;
	else if (treasure_ID < 12)
		score_value = 500;
	else
		score_value = 1000;

}

int TreasureBaseItem::Action(const ObjList& base, ObjList& add_base)
{

	for (auto& i : base)
	{
		//プレイヤーに当たった場合
		if (i->ID == (int)ObjID::PLAYER)
		{
			if (HitCheck_Box(pos.x, pos.y, i->pos.x, i->pos.y, 32, 32))
			{
				GetTreasureItem();
			}
		}
	}

	return 0;
}

void TreasureBaseItem::Draw()
{
	Point draw_pos = CameraToScreen(pos, map->camera);

	sprite.Draw(draw_pos.x, draw_pos.y);
}

void TreasureBaseItem::GetTreasureItem()
{
	//スコアを加算させる
	G_SCORE += score_value;
	FLAG = false;//このオブジェクトを削除する
}

void TreasureBaseItem::CutSprite(int _x, int _y, int _No)
{
	int s_y = _No / _x;
	if (s_y > _y)
		s_y = _y;//仮に計算で範囲外にいった場合、範囲内に戻す

	int s_x = _No - s_y * _x;//縦の列は求めたのでそこから横の位置を求める

	//計算結果をもとに切り取り位置を設定
	sprite.cutX = s_x * sprite.width;
	sprite.cutY = s_y * sprite.height;
}