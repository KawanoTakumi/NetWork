//ゲームシーン
#include "game.h"
#include "CollisionUpdate.h"
#include "function.h"
#include "Resource.h"

#include "player.h"
#include "TreasureBaseItem.h"
#include "WeaponBaseItem.h"

int G_SCORE = 0;

//コンストラクタ
CGame::CGame(CManager* p) :CScene(p){
	//画像読み込み
	Resource::Load();

	map = make_unique<CMap>();
	//特殊ブロック生成
	map->Map_Create(base);//特殊マップオブジェクト（リスポーン位置）

	//プレイヤー
	base.push_back(make_unique<CPlayer>(map.get()));


	//マップ内に宝物を設置
	Point _p{0,0};
	for (int i = 0; i < MAX_TREASURE_COUNT; i++)
	{
		_p.x = Range_Random_Number(0, map->MAP_SIZE_X);
		_p.y = Range_Random_Number(0, map->MAP_SIZE_Y);

		//移動不可の場所には置かない
		if (!map->CanMove(_p, 32, 32))
		{
			i--;
			continue;
		}
		//宝物生成
		base.push_back(make_unique<TreasureBaseItem>(Range_Random_Number(0, 23), _p, map.get()));
	}

	//マップ内に武器を設置
	for (int i = 0; i < 60; i++)
	{
		_p.x = Range_Random_Number(0, map->MAP_SIZE_X);
		_p.y = Range_Random_Number(0, map->MAP_SIZE_Y);
		//移動不可の場所には置かない
		if (!map->CanMove(_p, 32, 32))
		{
			i--;
			continue;
		}
		//武器を生成
		base.push_back(make_unique<WeaponBaseItem>(Range_Random_Number(0,2), Range_Random_Number(0, 2), _p, map.get()));
	}

}

//更新処理
int CGame::UpDate(){
	ObjList add_list;//追加処理用オブジェクトリスト

	//マップ更新
	map->Map_Update(base, add_list);

	//更新
	for (auto& obj : base)	
		obj->Action(base,add_list);

	//オブジェクト追加処理
	for (auto& obj : add_list)
		base.push_back(move(obj));

	//当たり判定処理
	CollisionUpDate(base);

	//削除処理
	erase_if(base, [](const auto& obj) {return !obj->FLAG; });

	//オブジェクトのソート処理(クイックソート)指定したインデックス間
	ObjSort_Quick(base, 0, base.size() - 1);

	return 0;
}

//描画処理
void CGame::Draw()
{
	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0x6b8d1c, true);

	//マップの描画
	map->Draw();

	for (auto& obj : base) obj->Draw();

	SetFontSize(16);
	//オブジェクト個数
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Object_Count = %d", base.size());
	DrawFormatString(0, 32, GetColor(255, 255, 0), "SCORE = %d", G_SCORE);
	//3D軸の描画
	DrawLine3D(VGet(0, 0, 0),VGet(0, 0, 100),0x0000ff);
	DrawLine3D(VGet(0, 0, 0),VGet(100, 0, 0),0xff0000);
	DrawLine3D(VGet(0, 0, 0),VGet(0, 100, 0),0x00ff00);
}

CGame::~CGame()
{
	Resource::Release();
}

//c++17 Releaseでerase_ifでエラーが出る場合こちらを利用するかコンパイルバージョンを変更
/*
base.erase(remove_if(base.begin(), base.end(), [](const unique_ptr<BaseVector>& base)
	{return !base->FLAG;}),
	base.end());
*/