#include "title.h"
#include "function.h"
#include "Resource.h"
#include "game.h"

CTitle::CTitle(CManager* p) :CScene(p) {

}

int CTitle::UpDate() {
	if (CheckHitKey(KEY_INPUT_RETURN)) {
		manager->Scene_Change(make_unique<CGame>(manager));
	}
	return 0;
}

void CTitle::Draw() {
	DrawFormatString(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0xffffff, "GameStartÅFENTER");
}