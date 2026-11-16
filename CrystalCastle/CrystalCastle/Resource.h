//リソースクラス
#pragma once
#include "main.h"

class Resource {
public:

	//プレイヤー画像
	static int playerImg;
	static int effectImg;

	//マップ画像
	static int map_cave_Img;

	//武器の画像
	static int weaponImg;
	static int magicImg;
	static int bowImg;

	//敵の画像
	static int enemy5Img;
	static int Boss_Img;
	static int enemy_projectile_Img;

	//アイテム画像
	static int itemImg;
	static int treasure_Img;


	//リソースの読み込み
	static void Load();
	//各リソースの削除処理
	static void Release();
};