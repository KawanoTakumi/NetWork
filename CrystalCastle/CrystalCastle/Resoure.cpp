//ƒŠƒ[ƒX
#include "Resource.h"

//int Resource::img;
int Resource::map_img;

//‰æ‘œ“Ç‚İ‚İ
void Resource::Load()
{
	//img = LoadGraph("");
	map_img = LoadGraph("image\\map.png");
}

//‰æ‘œíœ
void Resource::Release() {
	//DeleteGraph(img);
	DeleteGraph(map_img);
}

