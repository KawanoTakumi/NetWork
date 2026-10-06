//当たり判定関数
#include "CollisionUpdate.h"
#include "function.h"
#include "player.h"
#include "item.h"
#include "sword.h"
#include "bow.h"
#include "magic.h"

//当たり判定関数
//この関数を使用する場合、objIDについて取り扱いに注意すること
void CollisionUpDate(ObjList& base) {
	for (int i = 0; i < base.size(); i++) {
		BaseVector* a = base[i].get();
		for(int j = i + 1; j < base.size(); j++) 
		{
			BaseVector* b = base[j].get();
			//ID順を統一
			//if(a==b)とif(b==a)は同じオブジェクトの判定になるので、ID順を統一する
			if (a->ID > b->ID) swap(a, b);

			//プレイヤーと敵の当たり判定
			if (a->ID == (int)ObjID::PLAYER && b->ID == (int)ObjID::ENEMY){
				Player_Enemy_Collision(a, b);
			}

			//プレイヤーとアイテム
			if (a->ID == (int)ObjID::PLAYER && b->ID == (int)ObjID::ITEM) {
				Player_Item_Collision(a, b);
			}

			if (a->ID == (int)ObjID::WEAPON && b->ID == (int)ObjID::ENEMY) {
				Enemy_Weapon_Collison(a, b);
			}


			/*
			例）
			IDがPLAYERとENEMYの場合
			if (a->ID == (int)ObjID::PLAYER && b->ID == (int)ObjID::ENEMY) {
				//判定処理
			}
			*/
		}
	}
}

void Player_Enemy_Collision(BaseVector* a, BaseVector* b)
{
	//判定処理
	if (HitCheck_Box2(a, b))
	{
		//当たった場合

		CDamageObj* player = dynamic_cast<CDamageObj*>(a);
		
		Vector v{
			a->pos.x - b->pos.x,
			a->pos.y - b->pos.y
		};

		v = Vector_SetLength(v, 15);
		player->KnockBack(v);
	}
}

//プレイヤーとアイテム
void Player_Item_Collision(BaseVector* a, BaseVector* b)
{
	if (HitCheck_Box2(a, b)) 
	{
		//アイテムオブジェクトにキャスト
		CItem* item = dynamic_cast<CItem*>(b);
		//アイテムゲット処理
		item->GetItem(a);
	}
}

//敵と武器のあたり判定
void Enemy_Weapon_Collison(BaseVector* a, BaseVector* b)
{
	//敵のあたり判定の範囲
	float enemyRad = 32;

	//武器かどうかを調べる
	CWeaponBase* w = dynamic_cast<CWeaponBase*>(a);
	//武器だった場合武器のIDを取得
	int WeaponID = w->GetWeaponID();

	//ID毎に武器の挙動を設定
	switch (WeaponID)
	{
	case 0://剣
	{
		CSword* s = dynamic_cast<CSword*>(a);
		Point swordStart{ s->pos.x,s->pos.y };

		Point swordEnd
		{
			s->pos.x + cos(s->sprite.angle) * s->SWORD_LENGTH,
			s->pos.y + sin(s->sprite.angle) * s->SWORD_LENGTH
		};

		Point lp = Position_Closest_Line(b->pos, swordStart, swordEnd);

		float dx = b->pos.x - lp.x;
		float dy = b->pos.y - lp.y;
		float dist = sqrt(dx * dx + dy * dy);

		if (dist <= enemyRad)
		{
			CDamageObj* enemy = dynamic_cast<CDamageObj*>(b);

			Vector v
			{
				enemy->pos.x - s->pos.x,
				enemy->pos.y - s->pos.y
			};
			v = Vector_SetLength(v, 15);
			enemy->Damage(s->calc_damage, v);
			;
		}
	}break;
	case 1://弓
	{
		CBow* bow = dynamic_cast<CBow*>(a);

		//弓と敵のあたり判定
		if (HitCheck_Box2(bow,b))
		{
			//敵を取得
			CDamageObj* enemy = dynamic_cast<CDamageObj*>(b);

			//ノックバックの方向を計算
			Vector v
			{
				enemy->pos.x - bow->pos.x,
				enemy->pos.y - bow->pos.y
			};
			v = Vector_SetLength(v, 15);
			enemy->Damage(bow->calc_damage,v);
			bow->FLAG = false;
		}
	}break;
	case 2://杖
	{
		CMagic* magic = dynamic_cast<CMagic*>(a);
		//弓と敵のあたり判定
		if (HitCheck_Box2(magic,b))
		{
			//敵を取得
			CDamageObj* enemy = dynamic_cast<CDamageObj*>(b);

			//ノックバックの方向を計算
			Vector v
			{
				enemy->pos.x - magic->pos.x,
				enemy->pos.y - magic->pos.y
			};
			v = Vector_SetLength(v, 15);
			enemy->Damage(magic->calc_damage, v);
			
		}


	}break;
	default:
	{

	}break;
	}


}