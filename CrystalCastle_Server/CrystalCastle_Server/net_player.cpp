//プレイヤー
#include "net_player.h"
#include "sword.h"
#include "bow.h"
#include "magic.h"
#include "WeaponBaseItem.h"
#include "function.h"

const float MOVE_SPEED = 4.0f;

CNet_Player::CNet_Player(PlayerData* _data,CMap* _map)
{
	sprite.img = Resource::playerImg;
	sprite.cutX = 0;
	sprite.cutY = 0;
	NowUseWeaponID = (int)WeaponID::SWORD;//初期武器は剣
	NowUseWeaponNo = 0;
	sprite.width = 32;
	sprite.height = 32;

	pos = startPos;

	map = _map;

	data = _data;

	pri = 1;

	ID = (int)ObjID::NETPLAYER;

	hp = maxHp = 10;
	base_damage = 1;//基礎攻撃力を1に設定
	CalcDamage(NowUseWeaponID, NowUseWeaponNo);
}

int CNet_Player::Action(const ObjList& base, ObjList& add_base)
{
	//補完して移動(毎フレーム２０％ずつ近づける)
	pos.x += (data->pos.x - pos.x) * 0.2f;
	pos.y += (data->pos.y - pos.y) * 0.2f;
	//pos = data->pos;
	return 0;
}

//HP確認
int CNet_Player::CheckHP(int _hp)
{
	return CheckHP(_hp, 0);
}

int CNet_Player::CheckHP(int _hp, int heal)
{
	int healhp = _hp + heal;
	if (healhp > maxHp)healhp = maxHp;

	return healhp;
}

//リスポーン処理
void CNet_Player::Respawn()
{
	hp = maxHp;//体力全快
	pos = startPos;//初期位置
	lv = lv / 2;//レベル半減
}
//経験値取得
void CNet_Player::GetEXP(int _exp)
{
	exp += _exp;
	GetLevel(exp);
}

//レベル計算
void CNet_Player::GetLevel(int _exp)
{
	if (_exp > lv * 10) {
		lv++;
		//lv99でカンスト
		if (lv > 99) {
			lv = 99;
			exp = lv * 10;
			return;
		}
		maxHp = lv * 5 + 10;
		hp = maxHp;
		base_damage = lv * 1.2 + 1;
		CalcDamage(NowUseWeaponID, NowUseWeaponNo);
	}
}

//最終攻撃力計算
void CNet_Player::CalcDamage(int _Weap_type, int _Weap_no)
{
	//武器種を増やしたなら２をその分増加
	int type_value = abs(_Weap_type - 2);
	int no_value = _Weap_no + 1;

	calc_damage = type_value * no_value + base_damage;
}

void CNet_Player::Draw()
{
	//描画位置を計算
	Point draw_pos = CameraToScreen(pos, map->camera);
	//体力ゲージ
	DrawCustomHpBar(draw_pos, hp, maxHp, 0xeeeeee, 0x04ff08, 50, 5);

	if (!is_view_status)
	{
		//UIタイル
		DrawBox(0, 0, 200, 80, GetColor(50, 50, 50), true);
		DrawFormatString(0, 48, GetColor(255, 255, 255), "Qでステータス表示");
	}
	else
	{
		//UIタイル
		DrawBox(0, 0, 200, 140, GetColor(50, 50, 50), true);
		//ステータス
		DrawFormatString(0, 48, GetColor(255, 255, 255), "Qで閉じる");
		DrawFormatString(0, 80, GetColor(255, 255, 255), "体力        : %d/%d", hp, maxHp);
		DrawFormatString(0, 96, GetColor(255, 255, 255), "経験値      : %d/%d", exp, lv * 10);
		DrawFormatString(0, 112, GetColor(255, 255, 255), "攻撃力      : %d", calc_damage);
	}
	DrawFormatString(0, 64, GetColor(255, 255, 90), "レベル      :%d", lv);

	//プレイヤー
	sprite.Draw(draw_pos.x, draw_pos.y);
}

void CNet_Player::Attack(ObjList& add_base)
{
	WeaponID w_no = (WeaponID)NowUseWeaponID;
	//武器種毎に攻撃の挙動を変化させる
	switch (w_no)
	{
	case WeaponID::SWORD:
		add_base.push_back(make_unique<CSword>(pos, Dir, NowUseWeaponNo, calc_damage, map));
		break;
	case WeaponID::BOW:
		add_base.push_back(make_unique<CBow>(pos, old_vec, NowUseWeaponNo, calc_damage, map));
		break;
	case WeaponID::MAGIC:
		add_base.push_back(make_unique<CMagic>(pos, old_vec, NowUseWeaponNo, calc_damage, map));
		break;
	default:
		break;
	}
}

//武器切り替え関数
void CNet_Player::GetNewWeapon(int _NewWeaponID, int _NewWeaponNo, ObjList& add_base)
{
	//もともと持っていた武器を捨てる
	Point new_pos = pos;
	//もともとの武器を足元に生成
	add_base.push_back(make_unique<WeaponBaseItem>(NowUseWeaponID, NowUseWeaponNo, new_pos, map));
	//装備中の武器を更新する
	NowUseWeaponID = _NewWeaponID;
	NowUseWeaponNo = _NewWeaponNo;
}