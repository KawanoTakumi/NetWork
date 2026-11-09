#include "EnemyProjectile.h"
#include "function.h"
#include "player.h"
CEnemyProjectile::CEnemyProjectile(Point _pos,Vector _vec,CMap* _map,int _id,int _no)
{
	pos = _pos;
	vec = Vector_SetLength(_vec, 6.0f);//‰¼
	HP(1);
	map = _map;
	proj_id = _id;
	sprite.img = Resource::enemy_projectile_Img;
	sprite.cutX = _no*32;//No–ˆ‚É’e‚Ì‰æ‘œ‚ð•Ï‚¦‚é
	sprite.cutY = _id*32;//ID–ˆ‚É’e‚ÌŽí—Þ‚ð•Ï‚¦‚é
	sprite.width = 32;
	sprite.height = 32;
	sprite.angle = atan2(vec.y, vec.x);
	ID = (int)ObjID::ENEMY_PROJ;
	pri = 5;
}

int CEnemyProjectile::Action(const ObjList& base,ObjList& add_base)
{
	switch (proj_id)
	{
	default:
		break;
	case 0:case 1:
	{
		pos = Add_Point_Vector(pos, vec);

		//•Ç‚ðŠÑ’Ê‚µ‚È‚¢
		if (!map->CanMove(pos, 32, 32))
			FLAG = false;
	}break;


	}



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