#include "clear.h"
#include "title.h"
#include "function.h"
#include "Resource.h"

CClear::CClear(CManager* p) :CScene(p) {
	check_img = LoadGraph("image\\check.png");
	cross_img = LoadGraph("image\\cross.png");

	score_update = false;
	//ハイスコアの更新処理
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
	//DrawLine(WINDOW_WIDTH / 2 - 33 * 2, 0, WINDOW_WIDTH / 2 - 33 * 2, WINDOW_HEIGHT, 0xff0000);

	SetFontSize(48);
	//スコア・ハイスコアの表示
	DrawFormatString(WINDOW_WIDTH / 2 - 25 * 6 - 33 * 2, 350, 0xffffff, "SCORE：%d", G_SCORE);
	DrawFormatString(WINDOW_WIDTH / 2 - 25 * 10 - 33 * 2, 200, 0xffffff, "HIGHSCORE：%d", G_HIGH_SCORE);
	//ハイスコアを更新した時に出す
	if (score_update) {
		SetFontSize(16);
		DrawString(WINDOW_WIDTH / 2 - 25 * 10 - 33 * 2, 180, "NEW HIGHSCORE", 0xff0000);
	}
	SetFontSize(64);
	//タイトルに行く方法の表示
	DrawString(WINDOW_WIDTH / 2 - 33 * 8, 550, "TITLE：BACKSPACE", 0xffffff);
	SetFontSize(32);
	DrawString(WINDOW_WIDTH / 2 - 10 * 4, 620, "Player1：", 0xffffff);
	DrawGraph(WINDOW_WIDTH / 2, 700, check_img, true);

	SetFontSize(16);
}