#include "SearchPlayer.h"

CSearchPlayer::CSearchPlayer(EnemyBase* _enemy_base,CMap* _map)
{
	map = _map;
	enemy_base = _enemy_base;
	ID = (int)ObjID::SEARCH;
}

int CSearchPlayer::Action(const ObjList& base, ObjList& add_base)
{
	if (enemy_base == nullptr)return 0;

	//位置を常に親オブジェクトに付ける
	pos = enemy_base->pos;

	//敵が倒されたらこのオブジェクトを削除
	if (enemy_base->FLAG == false)
		FLAG = false;

	return 0;
}

void CSearchPlayer::Draw()
{

}

//プレイヤーが中にいる場合
void CSearchPlayer::InPlayer()
{
	if (enemy_base == nullptr)return;
	//親オブジェクトにターゲットを設定
	enemy_base->target = target;
}