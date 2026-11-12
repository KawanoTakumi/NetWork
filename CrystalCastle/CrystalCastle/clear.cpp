#include "clear.h"
#include "title.h"
#include "function.h"
#include "Resource.h"

CClear::CClear(CManager* p) :CScene(p) {
	score_update = false;
	//ハイスコアの更新
	if (G_SCORE > G_HIGH_SCORE) {
		G_HIGH_SCORE = G_SCORE;
		score_update = true;
	}
}

int CClear::UpDate() {
	if (CheckHitKey(KEY_INPUT_BACK)) {
		manager->Scene_Change(make_unique<CTitle>(manager));
		return 0;
	}
	return 0;
}

void CClear::Draw() {
	SetFontSize(48);

	DrawFormatString(WINDOW_WIDTH / 2 - 25 * 6, 350, 0xffffff, "SCORE：%d", G_SCORE);
	DrawFormatString(WINDOW_WIDTH / 2 - 25 * 10, 200, 0xffffff, "HIGHSCORE：%d", G_HIGH_SCORE);
	//ハイスコアを更新した時に出す
	if (score_update) {
		SetFontSize(16);
		DrawString(WINDOW_WIDTH / 2 - 25 * 10, 180, "NEW HIGHSCORE", 0xff0000);
	}

	SetFontSize(16);
}