//リロース
#include "Resource.h"

int Resource::playerImg;
int Resource::effectImg;
int Resource::enemy5Img;
int Resource::bowImg;
int Resource::magicImg;
int Resource::weaponImg;

int Resource::itemImg;

int Resource::Boss_Img;

int Resource::enemy_projectile_Img;


int Resource::treasure_Img;
int Resource::map_cave_Img;


//画像読み込み
void Resource::Load()
{
	playerImg = LoadGraph("image\\player32.png");//プレイヤー
	effectImg = LoadGraph("image\\effect02.png");//エフェクト
	enemy5Img = LoadGraph("image\\enemy5.png");//雑魚敵
	
	weaponImg = LoadGraph("image\\weapon_image.png");//武器画像
	magicImg = LoadGraph("image\\Projectile_Magic.png");//魔法の画像
	bowImg = LoadGraph("image\\Projectile_Bow.png");//矢の画像

	itemImg = LoadGraph("image\\item.png");//アイテム画像

	Boss_Img = LoadGraph("image\\Boss_1_King.png");//ボス画像
	enemy_projectile_Img = LoadGraph("image\\Enemy_Bullet.png");//敵の画像

	treasure_Img     = LoadGraph("image\\TreasureItem.png");//お宝画像
	map_cave_Img     = LoadGraph("image\\Tile_Caves_mod.png");//マップチップ
}
//画像削除
void Resource::Release() {
	DeleteGraph(playerImg);
	DeleteGraph(effectImg);
	DeleteGraph(enemy5Img);
	DeleteGraph(bowImg);
	DeleteGraph(magicImg);
	DeleteGraph(itemImg);
	DeleteGraph(Boss_Img);
	DeleteGraph(weaponImg);
	DeleteGraph(enemy_projectile_Img);
	DeleteGraph(treasure_Img);
	DeleteGraph(map_cave_Img);
}