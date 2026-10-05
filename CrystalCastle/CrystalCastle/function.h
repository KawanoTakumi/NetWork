#pragma once
#include "2D_function.h"
#include "3D_function.h"
#include "library_function.h"

//描画用座標変換（ワールド座標→画面座標）
Point CameraToScreen(Point, Point);
//体力バー
void DrawHpBar(Point, int, int);//位置,現在のHP,最大HP
