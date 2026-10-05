#include "EnemyBase.h"
#include "function.h"

EnemyBase::EnemyBase(Point p, CMap* _map)
{
	sprite.img = Resource::enemy5Img;
	sprite.cutX = 0;
	sprite.cutY = 0;

	sprite.width = ImgWidth = 32;
	sprite.height = ImgHeight = 32;

	map = _map;

	pos = p;

	ID = (int)ObjID::ENEMY;
}

int EnemyBase::Action(const ObjList& base, ObjList& add_base)
{
	return 0;
}

void EnemyBase::Draw()
{
	Point draw_pos = CameraToScreen(pos, map->camera);

	sprite.Draw(draw_pos.x, draw_pos.y);
}