#pragma once
#include "main.h"
#include "Scene_Manager.h"
#include "objBase.h"
#include "CCamera.h"

class CClear :public CScene
{
public:
	//コンストラクタ
	CClear(CManager*);

	//デストラクタ
	~CClear();

	int UpDate();//更新処理
	void Draw();//描画処理
};