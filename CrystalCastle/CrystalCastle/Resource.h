//リソースクラス
#pragma once
#include "main.h"

class Resource {
public:
	static int playerImg;
	static int effectImg;
	static int enemy5Img;
	static int enemy6Img;
	static int bowImg;
	static int mapImg;

	//マップ画像
	static int map_cave_Img;

	//武器の画像
	static int weaponImg;
	static int magicImg;
	//敵の画像
	static int enemy_n_01Img;
	static int enemy_n_02Img;
	static int enemy_boss_01Img;
	static int enemy_boss_02Img;

	//宝物画像
	static int treasure_Img;


	//リソースの読み込み
	static void Load();
	//各リソースの削除処理
	static void Release();
};