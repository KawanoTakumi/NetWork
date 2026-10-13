#include "magic.h"
#include "damageObj.h"
#include "function.h"

CMagic::CMagic(Point p, Vector v,int _No, int _calc_damage, CMap* _map)
{
	sprite.img = Resource::magicImg;
	sprite.cutX = 0;
	sprite.cutY = 0;
	sprite.width = 32;
	sprite.height = 32;
	pos = p;
	vec = Vector_SetLength(v, 8.0f);
	sprite.cutX = _No * sprite.width;//‰æ‘œ‚ÌˆÊ’u‚ð•Ší‚ÌNo*‰¡ƒTƒCƒY‚ÅŒvŽZ‚·‚é
	sprite.angle = atan2(vec.y, vec.x);
	calc_damage = _calc_damage;

	map = _map;
	pri = 1;
	ID = (int)ObjID::WEAPON;
	WeaponID = 2;
}

int CMagic::Action(const ObjList& base, ObjList& add_base)
{
	pos = Add_Point_Vector(pos, vec);

	life--;
	if (life == 0)FLAG = false;

	return 0;
}

void CMagic::Draw()
{
	//•`‰æˆÊ’u‚ðŒvŽZ
	Point draw_pos = CameraToScreen(pos, map->camera);

	//•`‰æ
	sprite.Draw(draw_pos.x, draw_pos.y);

}