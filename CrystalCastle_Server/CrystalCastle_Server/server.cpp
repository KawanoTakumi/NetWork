#include "server.h"
#include "net_player.h"

//接続処理
bool CServer::Accept(int port)
{
	//接続処理
	PreparationListenNetWork(port);
	netHandle = GetNewAcceptNetWork();

	if (netHandle == -1)return false;

	//接続があった場合、netHandleを保存
	//PLAYER.netHandle = netHandle;

	return true;
}

//サーバー側のプレイヤー情報へ登録
void CServer::New_Receive(ObjList& add_base, int _netHandle, CMap* _map) {
	//[0]はサーバー側のプレイヤー専用
	//空いているスロットを探して登録
	for (int i = 1; i < 4; i++) {
		if (PLAYER[i].netHandle == -1) {
			//接続したネットワークハンドルを保存
			PLAYER[i].netHandle = _netHandle;
			//新しく接続したプレイヤーオブジェクトを生成
			add_base.push_back(make_unique<CNet_Player>(&PLAYER[i].playerData, _map));
			break;
		}
	}
}

//データ受信
void CServer::Receive()
{
	//クライアントから受信するデータ
	PlayerSendData data{};

	for (int i = 1; i < 4; i++) {
		//受信データのチェック
		if (GetNetWorkDataLength(PLAYER[i].netHandle) > 0)
		{
			//データの受信
			NetWorkRecv(PLAYER[i].netHandle, (char*)&data, sizeof(PlayerSendData));

			//受信したデータをプレイヤー情報へ反映
			PLAYER[i].playerData.pos = data.pos;
		}
	}
}
