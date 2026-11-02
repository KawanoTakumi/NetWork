#include "EnemyProjectile.h"
#include "function.h"
CEnemyProjectile::CEnemyProjectile(Point _pos,Vector _vec,CMap* _map)
{
	pos = _pos;
	vec = Vector_SetLength(_vec, 6.0f);//‰¼
	HP(1);
	map = _map;
	sprite.img = Resource::enemy_projectile_Img;
	sprite.cutX = 0;
	sprite.cutY = 0;
	sprite.width = 32;
	sprite.height = 32;
	sprite.angle = atan2(vec.y, vec.x);
	ID = (int)ObjID::ENEMY_PROJ;
	pri = 5;
}

int CEnemyProjectile::Action(const ObjList& base,ObjList& add_base)
{
	pos = Add_Point_Vector(pos, vec);

	//‹|–î‚Ìê‡A•Ç‚ðŠÑ’Ê‚µ‚È‚¢
	if (!map->CanMove(pos, 32, 32))
		FLAG = false;

	//ˆê’èŽžŠÔŒo‰ß‚µ‚½‚çÁ‚·
	life--;
	if (life == 0)FLAG = false;

	return 0;
}

void CEnemyProjectile::Draw()
{
	//•`‰æˆÊ’u‚ðŒvŽZ
	Point draw_pos = CameraToScreen(pos, map->camera);
	//•`‰æ
	sprite.Draw(draw_pos.x, draw_pos.y);
}