#include "WeaponBaseItem.h"
#include "2D_function.h"
#include "function.h"
#include "player.h"

WeaponBaseItem::WeaponBaseItem(int _WeaponID,int _Weapon_No,Point p,CMap* _map)
{
	pos = p;
	weapon_id = _WeaponID;
	weapon_no = _Weapon_No;
	map = _map;
	pri = 30;
	//武器のスプライトを設定する
	sprite.img = Resource::weaponImg;
	sprite.scale = 2.0f;
	//武器毎に切り取り位置を変更する
	CutSprite(weapon_id,weapon_no);

	isPushE = CheckHitKey(KEY_INPUT_E);
}

int WeaponBaseItem::Action(const ObjList& base, ObjList& add_list)
{
	//当たり判定

	for (auto& i : base)
	{
		//プレイヤーに当たった場合
		if (i->ID == (int)ObjID::PLAYER)
		{
			if (HitCheck_Box(pos.x, pos.y, i->pos.x, i->pos.y, 32, 32))
			{
				if(!isHit)
				isHit = true;
				if (CheckHitKey(KEY_INPUT_E) && !isPushE)
				{
					isGet = true;//取得フラグ有効化
				}
				if (isGet && !CheckHitKey(KEY_INPUT_E))
				{
					FLAG = false;//このアイテムを削除
					CPlayer* player = dynamic_cast<CPlayer*>(i.get());//プレイヤー取得
					player->GetNewWeapon(weapon_id, weapon_no, add_list);//プレイヤーの武器をWeaponID毎に変化させる
					isGet = false;
				}
			}
			else
			{
				//初期化
				isHit = false;
				isGet = false;
			}
		}
	}

	isPushE = CheckHitKey(KEY_INPUT_E);

	return 0;
}

void WeaponBaseItem::Draw()
{
	Point draw_pos = CameraToScreen(pos, map->camera);

	if (isHit)
	{
		DrawBox(draw_pos.x - 66, draw_pos.y - 34, draw_pos.x + 60, draw_pos.y - 10, GetColor(0, 0, 0), true);
		DrawFormatString(draw_pos.x - 64, draw_pos.y - 32, GetColor(255, 255, 255), "E:武器切り替え");
	}
	sprite.Draw(draw_pos.x, draw_pos.y);
}

//画像切り取り関数
void WeaponBaseItem::CutSprite(int ID,int No)
{
	//計算結果をもとに切り取り位置を設定
	sprite.cutY = ID * sprite.height;
	sprite.cutX = No * sprite.width;
}