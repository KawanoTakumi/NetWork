#pragma once
#include "main.h"
#include "Scene_Manager.h"
#include "objBase.h"
#include "CCamera.h"

class CClear :public CScene
{
private:
	bool score_update{ false };
	int check_img{ -1 };
	int cross_img{ -1 };
public:
	//コンストラクタ
	CClear(CManager*);

	//デストラクタ
	~CClear() {};

	int UpDate();//更新処理
	void Draw();//描画処理
};