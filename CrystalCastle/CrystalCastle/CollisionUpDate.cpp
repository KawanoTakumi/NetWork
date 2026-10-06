//当たり判定関数
#include "CollisionUpdate.h"
#include "function.h"
#include "player.h"
#include "sword.h"

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

			//仮作成の武器と敵の当たり判定
			//if (a->ID == (int)ObjID::WEAPON && b->ID == (int)ObjID::ENEMY)
			//{
			//	if (HitCheck_Box(a, b))
			//	{
			//		CCharaOBJ* obj = dynamic_cast<CCharaOBJ*>(b);

			//		obj->Damage(10, obj->vec);
			//	}
			//}
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

//敵と武器のあたり判定
void Enemy_Weapon_Collison(BaseVector* a, BaseVector* b)
{
	//現状剣のみ対応

	float enemyRad = 32;
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
}