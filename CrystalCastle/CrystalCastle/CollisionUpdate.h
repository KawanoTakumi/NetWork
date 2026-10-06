//当たり判定用関数
#pragma once
#include "objBase.h"

//当たり判定メイン関数
void CollisionUpDate(ObjList&);

//プレイヤーと敵
void Player_Enemy_Collision(BaseVector* a, BaseVector* b);

//プレイヤーとアイテム
void Player_Item_Collision(BaseVector* a, BaseVector* b);

//敵と武器
void Enemy_Weapon_Collison(BaseVector* a, BaseVector* b);
