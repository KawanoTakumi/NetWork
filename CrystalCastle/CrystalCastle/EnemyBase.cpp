#include "EnemyBase.h"
#include "function.h"
#include "spawnPoint.h"
#include "expItem.h"
#include "healitem.h"

EnemyBase::EnemyBase(Point p, CMap* _map,CSpawnPoint* _sp)
{
	sprite.img = Resource::enemy5Img;
	sprite.cutX = 0;
	sprite.cutY = 0;

	sprite.width = ImgWidth = 32;
	sprite.height = ImgHeight = 32;

	HP(3);//HP初期化

	//スポーン位置保存
	spawn = _sp;
	//マップ情報
	map = _map;
	//位置情報
	pos = p;

	ID = (int)ObjID::ENEMY;
	pri = 2;

	switch (Range_Random_Number(0, 3))
	{
	case 0: vec.x = 0; vec.y = -3.0f; break;//上
	case 1: vec.x = 0; vec.y = 3.0f; break;//下
	case 2: vec.x = 3.0f; vec.y = 0; break;//右
	case 3: vec.x = -3.0f; vec.y = 0; break;//左
	}
}

int EnemyBase::Action(const ObjList& base, ObjList& add_base)
{

	//無敵時間
	if (damageCoolTime > 0)damageCoolTime--;
	//ノックバック処理
	if (UpdateKnockBack(map))return 0;
	//行動処理
	{
		//アニメーション
		animTimer++;
		if (animTimer >= 15)
		{
			animTimer = 0;
			animFrame++;
			if (animFrame > 1)
				animFrame = 0;
		}
		sprite.cutX = animFrame * sprite.width;
		if (Dir == LEFT || Dir == RIGHT) sprite.cutY = 64;
		if (Dir == UP) sprite.cutY = 0;
		if (Dir == DOWN) sprite.cutY = 32;

	}

	//HPがなくなった場合、オブジェクト解除
	if (hp <= 0) {
		
		if(spawn != nullptr)
		spawn->enemyAlive = false;
		//EXPを生成
		add_base.push_back(make_unique<CItemExp>(pos,map));
		add_base.push_back(make_unique<CItemHeal>(pos, map));
		FLAG = false;
	}
	return 0;
}

void EnemyBase::Draw()
{
	//描画位置を計算
	Point draw_pos = CameraToScreen(pos, map->camera);

	//体力ゲージ
	DrawHpBar(draw_pos, hp, maxHp);

	//描画向き	
	sprite.LR_reverse_flag = false;
	if (Dir == LEFT)sprite.LR_reverse_flag = true;

	sprite.Draw(draw_pos.x, draw_pos.y);
}

//向きの更新処理
void EnemyBase::UpdateDir(Point target)
{
	float dx = target.x - pos.x;
	float dy = target.y - pos.y;

	if (fabs(dx) > fabs(dy))
		Dir = (dx > 0) ? RIGHT : LEFT;
	else
		Dir = (dy > 0) ? DOWN : UP;
}