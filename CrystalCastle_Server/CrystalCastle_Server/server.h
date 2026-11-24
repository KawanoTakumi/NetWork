#pragma once
#include "NetData.h"

//接続中のプレイヤーの情報
class CPlayerInfo
{
public:
	int netHandle{ -1 };

	//接続しているプレイヤーのデータ
	PlayerData playerData;
};

class CServer {
public:
	//ネットワークハンドル
	int netHandle{ -1 };
	//接続処理
	bool Accept(int);

	//接続中のプレイヤー情報
	CPlayerInfo PLAYER[4];

	//クライアントからデータ受信
	void Receive();

	//接続してきたプレイヤーを登録
	void New_Receive(ObjList&, int, CMap*);
};