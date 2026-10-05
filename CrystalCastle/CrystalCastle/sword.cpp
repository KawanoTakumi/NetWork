//剣
#include "sword.h"
#include "function.h"


CSword::CSword(Point p, int _dir,int _No,int base_damage,CMap* _map)
{
	sprite.img = Resource::weaponImg;
	sprite.cutX = _No * 32;
	sprite.cutY = 0;
	sprite.width = 32;
	sprite.height =32;
	pos = p;
	Dir = _dir;
	map = _map;
	calc_damage = base_damage + (_No * 3);//仮のダメージ
	//初回の剣の向き
	if (Dir == (int)DIR::UP) {
		//上
		angle = start_angle = 180;
	}
	else if (Dir == (int)DIR::DOWN) {
		//下
		angle = start_angle = 0;
	}
	else if (Dir >= (int)DIR::LEFT_DOWN && Dir <= (int)DIR::LEFT_UP) {	
		//左
		angle = start_angle = -270;
	}
	else {
		//右
		angle = start_angle = 270;
	}

	pri = 1;

	//初期位置
	vec.x = cos(RADIAN(angle)) * sprite.width;
	vec.y = sin(RADIAN(angle)) * sprite.height;
	sprite.angle = RADIAN(angle);

	ID = (int)ObjID::WEAPON;
}

int CSword::Action(const ObjList& base, ObjList& add_base)
{
	//回転
	vec.x = cos(RADIAN(angle)) * sprite.width;
	vec.y = sin(RADIAN(angle)) * sprite.height;
	sprite.angle = RADIAN(angle);
	angle += 15;

	for (auto& i : base)
	{
		if (i->ID == (int)ObjID::ENEMY)
		{
			if (HitCheck_Box(pos.x, pos.y, i->pos.x, i->pos.y, 32, 32))
			{
				CCharaOBJ* obj = dynamic_cast<CCharaOBJ*>(i.get());
				obj->Damage(calc_damage,vec);
			}
		}
	}

	//半周したら消える
	if (angle > start_angle + 195)
	{
		FLAG = false;
	}
	return 0;
}

void CSword::Draw()
{
	sprite.Draw(pos.x - map->camera.x+vec.x, pos.y - map->camera.y+vec.y);
}
