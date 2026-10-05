#include "bow.h"
#include "damageObj.h"
#include "function.h"

CBow::CBow(Point p, Vector v,int _No, int base_damage, CMap* _m) {

	sprite.img = Resource::bowImg;
	sprite.cutX = 0;
	sprite.cutY = 0;
	sprite.width = 32;
	sprite.height = 32;
	sprite.cutX = _No * sprite.width;
	pos = p;
	vec = Vector_SetLength(v, 4.0f * (_No+1));

	sprite.angle = atan2(vec.y, vec.x);
	calc_damage = base_damage + (_No * 2);//‰¼‚Ìƒ_ƒ[ƒW
	map = _m;
	
	ID = (int)ObjID::WEAPON;
}

int CBow::Action(const ObjList& base, ObjList& add_base) 
{
	pos = Add_Point_Vector(pos, vec);

	//‹|–î‚Ìê‡A•Ç‚ðŠÑ’Ê‚µ‚È‚¢
	if (!map->CanMove(pos, 32, 32))
		FLAG = false;
	for (auto& i : base)
	{
		if (i->ID == (int)ObjID::ENEMY)
		{
			if (HitCheck_Box(pos.x, pos.y, i->pos.x, i->pos.y, 32, 32))
			{
				CDamageObj* obj = dynamic_cast<CDamageObj*>(i.get());
				obj->Damage(calc_damage, { 0,0 });
				FLAG = false;
			}
		}
	}
	life--;
	if (life == 0)FLAG = false;

	return 0;
}

void CBow::Draw()
{
	//•`‰æˆÊ’u‚ðŒvŽZ
	Point draw_pos = CameraToScreen(pos, map->camera);

	//•`‰æ
	sprite.Draw(draw_pos.x, draw_pos.y);
}