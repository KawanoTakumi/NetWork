#pragma once
#include "healItem.h"
#include "function.h"
#include "map.h"

CItemHeal::CItemHeal(Point p, CMap* _map)
{
	sprite.img = Resource::itemImg;
	sprite.cutX = 0;
	sprite.cutY = 0;
	sprite.width = ImgWidth = 32;
	sprite.height = ImgHeight = 32;

	pos = p;
	map = _map;

	//生成時ランダムな方向にとぶように移動ベクトルを設定
	vec.x = Range_Random_NumberF(-8, 8);
	vec.y = Range_Random_NumberF(-8, 8);
	//取得時の効果量
	value = 1;
	//アイテムの種類設定
	itemNo = ItemNo::HEART;
	//描画順を設定
	pri = 2;

}

int CItemHeal::Action(const ObjList&, ObjList&)
{
	//座標更新
	pos.x += vec.x;
	pos.y += vec.y;

	//移動速度を徐々に減速
	vec.x *= 0.9f;
	vec.y *= 0.9f;
	//一定速度以下になったら停止
	if (abs(vec.x) < 0.1f) vec.x = 0;
	if (abs(vec.y) < 0.1f) vec.y = 0;

	return 0;

}

void CItemHeal::Draw()
{
	Point draw_pos = CameraToScreen(pos, map->camera);
	sprite.Draw(draw_pos.x, draw_pos.y);
}