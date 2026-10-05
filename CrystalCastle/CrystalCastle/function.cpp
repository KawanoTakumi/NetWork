#include "function.h"

//描画用座標変換（ワールド座標→画面座標）
Point CameraToScreen(Point p, Point cp) {
	p.x = p.x - cp.x;
	p.y = p.y - cp.y;
	return p;
}
//体力バー(位置,現在HP,最大HP)
void DrawHpBar(Point p, int hp, int maxhp) {
	int barWidth = 50;
	int barHeight = 5;

	float rate = (float)hp / maxhp;
	if (rate < 0)
		rate = 0;

	int x = p.x - barWidth / 2;
	int y = p.y + 30;

	//バー全体(グレー）
	DrawLine(
		x, y,
		x + barWidth, y,
		0x646464,
		barHeight
	);
	//残り体力
	DrawLine(
		x, y,
		x + (int)(barWidth * rate), y,
		0x00ff00,
		barHeight
	);
}