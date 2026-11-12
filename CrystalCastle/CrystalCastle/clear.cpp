#include "clear.h"
#include "title.h"
#include "function.h"
#include "Resource.h"

CClear::CClear(CManager* p) :CScene(p) {

}

int CClear::UpDate() {
	if (CheckHitKey(KEY_INPUT_BACK)) {
		manager->Scene_Change(make_unique<CTitle>(manager));
		return 0;
	}
	return 0;
}

void CClear::Draw() {

}