#include "title.h"
#include "function.h"
#include "Resource.h"
#include "game.h"

CTitle::CTitle(CManager* p) :CScene(p) {
	title_img = LoadGraph("image//Title_new.png");
}

int CTitle::UpDate() {
	if (CheckHitKey(KEY_INPUT_RETURN)) {
		manager->Scene_Change(make_unique<CGame>(manager));
	}
	return 0;
}

void CTitle::Draw() {
	DrawGraph(0, 0, title_img, true);
	SetFontSize(32);
	DrawFormatString(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 + 50, 0x000000, "GameStartÅFENTER");
	SetFontSize(16);
}
