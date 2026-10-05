//ゲームシーン
#include "game.h"
#include "CollisionUpdate.h"
#include "function.h"

//コンストラクタ
CGame::CGame(CManager* p) :CScene(p){
	//リソースの読み込み
	Resource::Load();
}

//更新処理
int CGame::UpDate(){
	ObjList add_list;//追加処理用オブジェクトリスト

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

	SetFontSize(16);
	//オブジェクト個数
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Object_Count = %d", base.size());
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