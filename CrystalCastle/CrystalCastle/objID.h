#pragma once

//敵行動パターン
enum class EnemyState {
	NON,
	PATROL,
	CHASE,
	RETURN,
	ATTACK
};

//アイテム
enum class ItemNo
{
	EXP,//経験値
	HEART,//回復
	BOSS_STONE,//ボス出現アイテム
};

//武器
enum class WeaponID
{
	SWORD,//剣
	BOW,//弓
	MAGIC//魔法杖
};

//プレイヤーの状態
enum class PlayerState
{
	NORMAL,
	DEAD
};

//オブジェクトID
enum class ObjID {
	PLAYER,
	WEAPON,
	ENEMY,
	BOW,
	EFFECT,
	SPAWN_EFFECT,
	ITEM,
};