#include "EnemyBase.h"
#include "function.h"
#include "spawnPoint.h"
#include "expItem.h"


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
}

int EnemyBase::Action(const ObjList& base, ObjList& add_base)
{

	//無敵時間
	if (damageCoolTime > 0)damageCoolTime--;
	//ノックバック処理
	if (UpdateKnockBack(map))return 0;
	//HPがなくなった場合、オブジェクト解除
	if (hp <= 0) {
		
		if(spawn != nullptr)
		spawn->enemyAlive = false;
		//EXPを生成
		add_base.push_back(make_unique<CItemExp>(pos,map));
		FLAG = false;
	}
	return 0;
}

void EnemyBase::Draw()
{
	Point draw_pos = CameraToScreen(pos, map->camera);

	sprite.Draw(draw_pos.x, draw_pos.y);
}