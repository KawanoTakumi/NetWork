#include "Effect.h"

CEffect::CEffect(Point _p, int no, float size, float _speed, CMap* _map) {
	sprite.img = Resource::effectImg;

	switch (no)
	{
	case 0:
		startCutX = sprite.cutX = 0;
		startCutY = sprite.cutY = 0;
		sprite.width = 32;
		sprite.height = 32;
		frame = 5;
		break;
	case 1:
		startCutX = sprite.cutX = 0;
		startCutY = sprite.cutY = 32;
		sprite.width = 16;
		sprite.height = 16;
		frame = 4;
		break;
	case 2:
		startCutX = sprite.cutX = 64;
		startCutY = sprite.cutY = 32;
		sprite.width = 16;
		sprite.height = 16;
		frame = 6;
		break;
	case 3:
		startCutX = sprite.cutX = 0;
		startCutY = sprite.cutY = 48;
		sprite.width = 16;
		sprite.height = 16;
		frame = 5;
		break;
	case 4:
		startCutX = sprite.cutX = 0;
		startCutY = sprite.cutY = 64;
		sprite.width = 32;
		sprite.height = 32;
		frame = 4;
		break;
	}

	sprite.scale = size;

	speed = _speed;

	pos = _p;

	pri = 5;

	map = _map;

	ID = (int)ObjID::EFFECT;
}

int CEffect::Action(const ObjList& base, ObjList& add_base) 
{
	timer++;
	animFrame = timer / speed;
	if (animFrame == frame) FLAG = false;
	
	sprite.cutX = startCutX + animFrame * sprite.width;

	return 0;
}

void CEffect::Draw()
{
	sprite.Draw(pos.x - map->camera.x, pos.y - map->camera.y);
}