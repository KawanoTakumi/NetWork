#include "item.h"
#include "player.h"

void CItem::GetItem(BaseVector* b) {
	//æ“¾‚µ‚½‚Ìˆ—
	CPlayer* p = dynamic_cast<CPlayer*>(b);

	switch (itemNo) {
	case ItemNo::EXP:
		p->GetEXP(value);
		break;
	case ItemNo::HEART:
		p->hp = p->CheckHP(p->hp, value);
		break;
	}
	FLAG = false;
}