#include "NPCBase.h"
#include "function.h"
#include "spawnPoint.h"
#include "expItem.h"
#include "healitem.h"
#include "EnemyProjectile.h"

//向きの更新処理
void NPCBase::UpdateDir(Point target)
{
	float dx = target.x - pos.x;
	float dy = target.y - pos.y;

	if (fabs(dx) > fabs(dy))
		Dir = (dx > 0) ? RIGHT : LEFT;
	else
		Dir = (dy > 0) ? DOWN : UP;
}

//プレイヤー追尾
void NPCBase::HomingPlayer()
{
	//プレイヤーがいない場合は終了
	if (target == nullptr)return;

	Vector homing_vec{
		homing_vec.x = target->pos.x - pos.x,
		homing_vec.y = target->pos.y - pos.y
	};

	//プレイヤーの方向に移動する
	vec = Vector_SetLength(homing_vec, 2);
}

//弾丸発射
void NPCBase::Shoot(ObjList& add_base,PROJ_ID _id,int _no,bool _reverse)
{
	//プレイヤーがいない場合は終了
	if (target == nullptr)return;

	Vector shoot_vec{
		shoot_vec.x = target->pos.x - pos.x,
		shoot_vec.y = target->pos.y - pos.y
	};
	add_base.push_back(make_unique<CEnemyProjectile>(pos, shoot_vec, map,(int)_id,_no,_reverse));
}

//弾丸扇発射
void NPCBase::Mul_Shoot(ObjList& add_base, float _angle, int _count,PROJ_ID _id,int _no,bool _reverse)
{
	if (target == nullptr)return;

	//中央の弾丸のベクトル作成
	Vector shoot_vec{
	shoot_vec.x = target->pos.x - pos.x,
	shoot_vec.y = target->pos.y - pos.y
	};

	//左右に角度毎に展開
	for (int i = 0; i < _count; i++)
	{
		Vector right_Vec = Vector_Rotation(shoot_vec, _angle);
		Vector left_Vec = Vector_Rotation(shoot_vec, -_angle);
		_angle += _angle;
		add_base.push_back(make_unique<CEnemyProjectile>(pos, right_Vec, map,(int)_id,_no,_reverse));
		add_base.push_back(make_unique<CEnemyProjectile>(pos, left_Vec, map,(int)_id,_no,_reverse));

	}
	//中央の弾丸発射
	add_base.push_back(make_unique<CEnemyProjectile>(pos, shoot_vec, map, (int)_id,_no, _reverse));
}

//ビーム配列型発射
void NPCBase::Beam_Shoot(ObjList& add_base, int count, PROJ_ID _id,int _no)
{
	//プレイヤーがいない場合は終了
	if (target == nullptr)return;

	Vector shoot_vec{
		shoot_vec.x = target->pos.x - pos.x,
		shoot_vec.y = target->pos.y - pos.y
	};
	//最初の弾丸
	Vector shoot_v = Vector_Normalize(shoot_vec);
	add_base.push_back(make_unique<CEnemyProjectile>(pos, shoot_vec, map, (int)_id,_no,false));
	
	//後続の弾丸
	for (int i = 0;i < count;i++)
	{
		Point add_p{ pos.x - shoot_v.x * (32 * i),pos.y - shoot_v.y * (32 * i) };
		add_base.push_back(make_unique<CEnemyProjectile>(add_p, shoot_vec, map, (int)_id,_no,false));
	}
}