#include"all.h"

//  関数ポインタ
float(* const ToRadian)(float) = DirectX::XMConvertToRadians;  // 角度をラジアンに
float(* const ToDegree)(float) = DirectX::XMConvertToDegrees;  // ラジアンを角度に

void anime(obj2d* obj, int total, int flame, bool loop,int type)
{
	switch (obj->state)
	{
	case 0:
		obj->anime = obj->animeTimer = 0;
		obj->end = false;
		obj->one = false;
		GameLib::sound::play(type, 0);

		++obj->state;
	case 1:
		if (loop)
		{
			obj->anime = obj->animeTimer / flame;
			if (obj->anime >= total)
			{
				obj->anime = 0;
				obj->animeTimer = 0;
			}
			obj->texPos.x = obj->anime * obj->texSize.x;
			++obj->animeTimer;
		}
		else
		{
			if (obj->open)
			{
				obj->anime = obj->animeTimer / flame;
				if (obj->anime >= total - 1)obj->one = true;
				if (obj->anime >= total)
				{
					obj->anime = total - 1;
					obj->end = true;
					return;
				}
				obj->texPos.x = obj->anime * obj->texSize.x;
				++obj->animeTimer;
			}
		}
		break;
	}

}