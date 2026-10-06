#pragma once
#include "objBase.h"
#include "damageObj.h"
#include "map.h"



class CPlayer :public CDamageObj
{
private:
	Point startPos{ 7660,5370 };
	//Point startPos{ 6*32,7*32 };
public:
	CPlayer(CMap*);

	int Action(const ObjList&, ObjList&);
	void Draw();

	//CMap* map;

	//キーの状態保存
	char key[256]{ 0 };

	//攻撃中フレーム
	int att_frame{ 0 };
	//攻撃カウント
	int attackCount{ 0 };

	//レベル
	int lv{ 1 };
	//経験値
	int exp{ 0 };
	//攻撃力
	int base_damage{ 0 };

	//リスポーン処理
	void Respawn();

	//攻撃処理
	void Attack(ObjList&);

	PlayerState state{ PlayerState::NORMAL };
	int deadTimer{ 0 };

	Vector old_vec = { 0,0 };
	int NowUseWeaponID = 0;//現在装備中の武器の種類ID
	int NowUseWeaponNo = 0;//現在装備中の武器の番号ID
	void GetNewWeapon(int NewWeaponID, int NewWeaponNo,ObjList& add_base);//地面で当たった武器を拾う
	//経験値取得
	void GetEXP(int);
	//レベル計算
	void GetLevel(int);

	//SE
	int player_att_SE{ -1 };
	int player_damage_SE{ -1 };
	int player_down_SE{ -1 };

	//画面切り替え
	bool is_view_status = false;//ステータス表示

};