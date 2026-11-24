#include "client.h"
#include "player.h"
#include "function.h"

bool CClient::Connect(const IPDATA ip)
{
	//指定したIPアドレスとポートに接続
	netHandle = ConnectNetWork(ip, 40);//40...ポート番号
	if (netHandle != -1)
	{
		return true;
	}
	return false;
}

//プレイヤーデータをサーバーへ送信
void CClient::Send(const ObjList& base)
{
	//playerオブジェクトを取得
	CPlayer* player = dynamic_cast<CPlayer*>(Get_obj(base, (int)ObjID::PLAYER));

	//送信データの準備
	char str[512]{ 0 };//送信のバッファデータ
	PlayerSendData data{};//送信データ

	if (player) {
		//プレイヤーの位置をコピー
		data.pos = player->pos;
		//向きやその他の送信したい情報をここで作成
	}
	//送信用のバッファにコピー
	memcpy_s(str, sizeof(PlayerSendData), &data, sizeof(PlayerSendData));

	//サーバーへデータを送信
	NetWorkSend(netHandle, str, sizeof(PlayerSendData));
}
