#include "weapon.h"

CWeaponBase::CWeaponBase()
{
	ID = (int)ObjID::WEAPON;
}

int CWeaponBase::Action(const ObjList& base, ObjList& add_base)
{


	return 0;
}

void CWeaponBase::Draw()
{

}

int CWeaponBase::GetWeaponID()
{
	return WeaponID;
}