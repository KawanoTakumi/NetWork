#pragma once
#include "NetData.h"

class CClient
{
public:
	//ネットワークハンドル
	int netHandle{ -1 };

	//初回接続
	bool Connect(const IPDATA ip);
	//データの送信
	void Send(const ObjList&);
};
