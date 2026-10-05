#include "magic.h"
#include "function.h"

CMagic::CMagic(Point p, Vector v,int _No, int base_damage, CMap* _map)
{
	sprite.img = Resource::magicImg;
	sprite.cutX = 0;
	sprite.cutY = 0;
	sprite.width = 32;
	sprite.height = 32;
	pos = p;
	vec = Vector_SetLength(v, 8.0f);
	sprite.cutX = _No * sprite.width;//画像の位置を武器のNo*横サイズで計算する
	sprite.angle = atan2(vec.y, vec.x);
	calc_damage = base_damage + (_No * 1);//仮のダメージ

	map = _map;
	
	ID = (int)ObjID::WEAPON;

}

int CMagic::Action(const ObjList& base, ObjList& add_base)
{
	pos = Add_Point_Vector(pos, vec);

	for (auto& i : base)
	{
		if (i->ID == (int)ObjID::ENEMY)
		{
			if (HitCheck_Box(pos.x, pos.y, i->pos.x, i->pos.y, 32, 32))
			{
				CCharaOBJ* obj = dynamic_cast<CCharaOBJ*>(i.get());
				obj->Damage(calc_damage, { 0,0 });
			}
		}
	}
	life--;
	if (life == 0)FLAG = false;


	return 0;
}

void CMagic::Draw()
{
	//描画位置を計算
	Point draw_pos = CameraToScreen(pos, map->camera);

	//描画
	sprite.Draw(draw_pos.x, draw_pos.y);

}