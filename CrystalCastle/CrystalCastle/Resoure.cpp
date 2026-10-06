//リロース
#include "Resource.h"

int Resource::playerImg;
int Resource::effectImg;
int Resource::enemy5Img;
int Resource::enemy6Img;
int Resource::bowImg;
int Resource::mapImg;
int Resource::itemImg;

int Resource::enemy_boss_01Img;
int Resource::enemy_boss_02Img;
int Resource::enemy_n_01Img;
int Resource::enemy_n_02Img;
int Resource::weaponImg;
int Resource::magicImg;
int Resource::treasure_Img;
int Resource::map_cave_Img;


//画像読み込み
void Resource::Load()
{
	playerImg = LoadGraph("image\\player32.png");
	effectImg = LoadGraph("image\\effect02.png");
	enemy5Img = LoadGraph("image\\enemy5.png");
	enemy6Img = LoadGraph("image\\enemy6.png");
	bowImg = LoadGraph("image\\bow.png");
	mapImg = LoadGraph("image\\map.png");
	itemImg = LoadGraph("image\\item.png");

	enemy_boss_01Img = LoadGraph("");
	enemy_boss_02Img = LoadGraph("");
	enemy_n_01Img    = LoadGraph("");
	enemy_n_02Img    = LoadGraph("");
	weaponImg        = LoadGraph("image\\TestWeapon.png");//テスト用武器画像
	magicImg         = LoadGraph("image\\TestMagic.png");//テスト用魔法弾
	treasure_Img     = LoadGraph("image\\TreasureItem.png");
	map_cave_Img     = LoadGraph("image\\Tile_Caves.png");
}
//画像削除
void Resource::Release() {
	DeleteGraph(playerImg);
	DeleteGraph(effectImg);
	DeleteGraph(enemy5Img);
	DeleteGraph(enemy6Img);
	DeleteGraph(bowImg);
	DeleteGraph(mapImg);
	DeleteGraph(itemImg);

	DeleteGraph(enemy_boss_01Img);
	DeleteGraph(enemy_boss_02Img);
	DeleteGraph(enemy_n_01Img);
	DeleteGraph(enemy_n_02Img);
	DeleteGraph(weaponImg);
	DeleteGraph(treasure_Img);

}