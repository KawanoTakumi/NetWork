//当たり判定関数
#include "CollisionUpdate.h"

//当たり判定関数
//この関数を使用する場合、baseに登録しているオブジェクトの順番についてソートが必要
// 使用する場合の注意
//　①priの値を設定して、オブジェクトは、必ずソートしていること
//　②判定の条件を描く場合、aオブジェクトのpriが必ずbオブジェクトより小さくなるように指定すること
void CollisionUpDate(ObjList& base) {
	for (int i = 0; i < base.size(); i++) {
		BaseVector* a = base[i].get();
		for(int j = i + 1; j < base.size(); j++) 
		{
			BaseVector* b = base[j].get();
			//ID順を統一
			//if(a==b)とif(b==a)は同じオブジェクトの判定になるので、ID順を統一する
		}
	}
}