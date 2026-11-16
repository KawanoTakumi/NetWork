#include "BossBase.h"
#include "function.h"
#include "spawnPoint.h"
#include "expItem.h"
#include "healitem.h"
#include "EnemyProjectile.h"

BossBase::BossBase(Point p, CMap* _map, CSpawnPoint* _sp, int _No)
{
	sprite.img = Resource::enemy_boss_01Img;
	No = _No;
	sprite.cutX = No * 64;
	sprite.cutY = 0;

	sprite.width = ImgWidth = 64;
	sprite.height = ImgHeight = 64;

	HP(100+Range_Random_Number(1,20));//HP初期化

	//スポーン位置保存
	spawn = _sp;
	//マップ情報
	map = _map;
	//位置情報
	pos = p;

	ID = (int)ObjID::ENEMY;
	pri = 3;
	//最初の移動方向を設定
	switch (Range_Random_Number(0, 3))
	{
	case 0: vec.x = 0; vec.y = -move_speed; break;//上
	case 1: vec.x = 0; vec.y = move_speed; break;//下
	case 2: vec.x = move_speed; vec.y = 0; break;//右
	case 3: vec.x = -move_speed; vec.y = 0; break;//左
	}
}

int BossBase::Action(const ObjList& base, ObjList& add_base)
{
	//プレイヤー探索用のオブジェクトを生成
	if (!create_search_obj)
	{
		add_base.push_back(make_unique<CSearchPlayer>(this, map));
		create_search_obj = true;
	}

	//移動処理（ノックバックとは別）
	{
		//サブステップ判定処理
		//処理回数を求める
		int step = (int)max(abs(vec.x), abs(vec.y));
		step = max(step, 1);
		//1ステップの移動距離を計算
		float moveX = vec.x / step;
		float moveY = vec.y / step;
		bool isHit = false;
		//ステップ判定
		for (int i = 0; i < step; i++)
		{
			//マップ判定
			Point nextPos = pos;
			nextPos.x += moveX;
			nextPos.y += moveY;

			if (map->CanMove(nextPos, sprite.width, sprite.height)) {
				UpdateDir(nextPos);//移動方向を求める
				pos = nextPos;
			}
			else {
				//当たったと判定
				isHit = true;
			}
			nextPos = pos;
		}
		//当たった場合移動方向を再設定する
		if (isHit) {
			switch (Range_Random_Number(0, 3))
			{
			case 0: vec.x = 0; vec.y = -move_speed; break;//上
			case 1: vec.x = 0; vec.y = move_speed; break;//下
			case 2: vec.x = move_speed; vec.y = 0; break;//右
			case 3: vec.x = -move_speed; vec.y = 0; break;//左
			}
		}

	}
	HomingPlayer();



	//無敵時間
	if (damageCoolTime > 0)damageCoolTime--;
	//ノックバック処理
	if (UpdateKnockBack(map))return 0;

	//弾丸発射処理
	shoot_timer--;
	if (shoot_timer < 0)
	{
		if (shoot_count < 2)
		{
			if(No==0)
			Beam_Shoot(add_base,7,NPCBase::PROJ_ID::BEAM,0);
			else if(No==1)
			Beam_Shoot(add_base, 7, NPCBase::PROJ_ID::BEAM, 2);
		}
		else if (shoot_count >= 2 && shoot_count < 4)
		{
			if (No == 0)
			Mul_Shoot(add_base, 30, 2, NPCBase::PROJ_ID::BULLET,1,false);
			else if (No == 1)
			Mul_Shoot(add_base, 30, 4, NPCBase::PROJ_ID::BULLET, 7, false);

		}
		else
			shoot_count = 0;
		shoot_timer = MAX_SHOOT_TIMER*3;
		shoot_count++;
	}





	//無敵時間
	if (damageCoolTime > 0)damageCoolTime--;
	//ノックバック処理
	if (UpdateKnockBack(map))return 0;

	//HPがなくなった場合、オブジェクト解除
	if (hp <= 0) {

		//ボスの場合ここで倒された時点でスポーンポイントを削除する
		if (spawn != nullptr)
		{
			spawn->enemyAlive = false;
			spawn->Destroy();
		}

		//アイテムを生成
		add_base.push_back(make_unique<CItemExp>(pos, map, 20 + 3 * No));
		add_base.push_back(make_unique<CItemHeal>(pos, map));

		FLAG = false;
	}
	return 0;
}

void BossBase::Draw()
{
	//描画位置を計算
	Point draw_pos = CameraToScreen(pos, map->camera);

	DrawCustomHpBar(draw_pos, hp, maxHp, 0xeeeeee, 0xee02ee,120,9);

	//描画向き	
	sprite.LR_reverse_flag = false;
	sprite.UD_reverse_flag = false;

	sprite.Draw(draw_pos.x, draw_pos.y);
}
