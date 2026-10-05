//ゲームシーン
#include "game.h"
#include "CollisionUpdate.h"
#include "function.h"

//コンストラクタ
CGame::CGame(CManager* p) :CScene(p){
	//リソースの読み込み
	Resource::Load();

	//マップオブジェクト
	map = make_unique<CMap>();
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
	map->Draw();

	for (auto& obj : base)obj->Draw();


	SetFontSize(16);
	//オブジェクト個数
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Object_Count = %d", base.size());
	

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