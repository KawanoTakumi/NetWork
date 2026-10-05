//プレイヤー
#include "player.h"
#include "sword.h"
#include "bow.h"
#include "magic.h"
#include "WeaponBaseItem.h"
#include "function.h"

const float MOVE_SPEED = 4.0f;

CPlayer::CPlayer(CMap* _map)
{
	sprite.img = Resource::playerImg;
	sprite.cutX = 0;
	sprite.cutY = 0;
	NowUseWeaponID = (int)WeaponID::SWORD;//初期武器は剣
	NowUseWeaponNo = 0;
	sprite.width =  32;
	sprite.height =  32;

	pos = startPos;

	map = _map;

	pri = 2;

	ID = (int)ObjID::PLAYER;

	hp = maxHp = 10;
	base_damage = 1;//基礎攻撃力を1に設定

}

int CPlayer::Action(const ObjList& base, ObjList& add_base) 
{
	int PAD_INFO = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	switch (state) {
	case PlayerState::NORMAL:
		//死亡チェック
		if (hp <= 0) {
			//SE
			PlaySoundMem(player_down_SE, DX_PLAYTYPE_BACK);
			state = PlayerState::DEAD;
			return 0;
		}
		break;
	case PlayerState::DEAD:
		deadTimer++;
		if (deadTimer == 30)
		{
			Respawn();
			state = PlayerState::NORMAL;
			deadTimer = 0;
		}
		return 0;
	}

	vec.x = vec.y = 0;

	if (UpdateKnockBack(map))return 0;
	if (att_frame > 0) att_frame--;
	//攻撃中判定フラグ
	bool isAttack = (att_frame > 0);

	//ノックバック処理
	//SE
	if (damageCoolTime == 20) PlaySoundMem(player_damage_SE, DX_PLAYTYPE_BACK);


	if (!isAttack) {
		//キー入力
		if (CheckHitKey(KEY_INPUT_A) || (PAD_INFO & PAD_INPUT_LEFT)) vec.x = -1.0f;
		if (CheckHitKey(KEY_INPUT_D) || (PAD_INFO & PAD_INPUT_RIGHT)) vec.x = 1.0f;
		if (CheckHitKey(KEY_INPUT_W) || (PAD_INFO & PAD_INPUT_UP)) vec.y = -1.0f;
		if (CheckHitKey(KEY_INPUT_S) || (PAD_INFO & PAD_INPUT_DOWN)) vec.y = 1.0f;

		//ステータス表示
		if ((CheckHitKey(KEY_INPUT_Q) || (PAD_INFO & PAD_INPUT_START)) && (!key[(PAD_INFO & PAD_INPUT_START)] && !key[KEY_INPUT_Q]))
		{
			if (is_view_status)
				is_view_status = false;
			else
				is_view_status = true;
		}

		//攻撃処理
		if ((CheckHitKey(KEY_INPUT_SPACE) || (PAD_INFO & PAD_INPUT_1)) && (!key[(PAD_INFO & PAD_INPUT_1)] &&!key[KEY_INPUT_SPACE])) {
			//SE
			PlaySoundMem(player_att_SE, DX_PLAYTYPE_BACK);
			switch (NowUseWeaponID)
			{
			default:
				break;
			}
			Attack(add_base);
			att_frame = 13;
			attackCount++;
		}
	}
	//移動しているかフラグ
	bool isMove = (vec.x != 0 || vec.y != 0);

	//向き
	Dir = GetDir(Dir);

	//切り取り位置計算
	if (Dir == (int)DIR::DOWN) {
		sprite.cutY = 32;
	}
	else if (Dir == (int)DIR::UP) {
		sprite.cutY = 0;
	}
	else {
		sprite.LR_reverse_flag = true;
		if (Dir >= (int)DIR::LEFT_DOWN && Dir <= (int)DIR::LEFT_UP)
			sprite.LR_reverse_flag = false;
		sprite.cutY = 64;
	}

	//アニメーション処理
	if (isMove) {
		animTimer++;
		if (animTimer >= 10) 
		{
			animTimer = 0;
			sprite.cutX += sprite.width;
			if (sprite.cutX > sprite.width)	sprite.cutX = 0;
		}
	}
	else {
		animFrame = 0;
	}

	//移動ベクトル計算
	if (isMove) {
		//移動ベクトル計算
		vec = Vector_SetLength(vec, MOVE_SPEED);
		//移動できるかチェック
		Point nextPos = pos;
		//x方向
		nextPos.x += vec.x;
		if (map->CanMove(nextPos, sprite.width, sprite.height))
		{
			pos.x = nextPos.x;
		}
		//y方向
		nextPos = pos;
		nextPos.y = pos.y + vec.y;
		if (map->CanMove(nextPos, sprite.width, sprite.height)) {
			pos.y = nextPos.y;
		}
		old_vec = vec;
	}

	//入力状態の保存
	GetHitKeyStateAll(key);
	key[(PAD_INFO & PAD_INPUT_1)] = PAD_INFO & PAD_INPUT_1;

	//レベルチェック
	GetLevel(exp);

	return 0;
}

//リスポーン処理
void CPlayer::Respawn()
{
	hp = maxHp;//体力全快
	pos = startPos;//初期位置
}
//経験値取得
void CPlayer::GetEXP(int _exp)
{
	exp += _exp;
	GetLevel(exp);
}

//レベル計算
void CPlayer::GetLevel(int exp) 
{
	if (exp > lv * 10) {
		lv++;
		//lv99でカンスト
		if (lv > 99) return;
		maxHp += 5;
		hp += 5;
		base_damage = lv * 1.2;
	}
}

void CPlayer::Draw()
{
	//描画位置を計算
	Point draw_pos = CameraToScreen(pos, map->camera);
	//体力ゲージ
	DrawHpBar(draw_pos, hp, maxHp);

	DrawBox(0, 0, 200, 120, GetColor(50, 50, 50), true);
	DrawFormatString(0, 64, GetColor(255, 255, 255), "Lv = %d", lv);
	if (!is_view_status)
	{
		//現在の武器ID
	//	DrawFormatString(0, 48, GetColor(255, 0, 0), "NowWeaponID = %d", NowUseWeaponID);
	//	DrawFormatString(0, 64, GetColor(255, 0, 0), "NowWeaponNo = %d", NowUseWeaponNo);

		DrawFormatString(0, 48, GetColor(255, 255, 255), "Qでステータス表示");
	}
	else
	{
		//ステータス
		DrawFormatString(0, 48, GetColor(255, 255, 255), "Qで閉じる");
		DrawFormatString(0, 80, GetColor(255, 255, 255), "hp/maxHp : %d/%d", hp, maxHp);
		DrawFormatString(0, 96, GetColor(255, 255, 255), "damage   : %d", base_damage);
	}
	//プレイヤー
	sprite.Draw(draw_pos.x, draw_pos.y);
}

void CPlayer::Attack(ObjList& add_base)
{
	WeaponID w_no = (WeaponID)NowUseWeaponID;
	//武器種毎に攻撃の挙動を変化させる
	switch (w_no)
	{
	case WeaponID::SWORD:
		add_base.push_back(make_unique<CSword>(pos,Dir, NowUseWeaponNo,base_damage, map));
		break;
	case WeaponID::BOW:
		add_base.push_back(make_unique<CBow>(pos, old_vec, NowUseWeaponNo, base_damage, map));
		break;
	case WeaponID::MAGIC:
		add_base.push_back(make_unique<CMagic>(pos,old_vec, NowUseWeaponNo, base_damage, map));
		break;
	default:
		break;
	}
}

//武器切り替え関数
void CPlayer::GetNewWeapon(int _NewWeaponID,int _NewWeaponNo, ObjList& add_base)
{
	//もともと持っていた武器を捨てる
	//Point new_pos = CameraToScreen(pos, map->camera);
	Point new_pos = pos;
	//少しずらす

	add_base.push_back(make_unique<WeaponBaseItem>(NowUseWeaponID,NowUseWeaponNo, new_pos,map));
	//装備中の武器を更新する
	NowUseWeaponID = _NewWeaponID;
	NowUseWeaponNo = _NewWeaponNo;
}