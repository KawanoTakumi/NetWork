#pragma once
#include "main.h"
#include "Scene_Manager.h"
#include "objBase.h"
#include "CCamera.h"

class CTitle :public CScene
{
public:
	//コンストラクタ
	CTitle(CManager*);

	//デストラクタ
	~CTitle() {};

	int UpDate();//更新処理
	void Draw();//描画処理
};
