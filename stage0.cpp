#include "all.h"

/*****変数*****/
Sprite* spr1;

void stage0_init()
{
    stage_state[0] = 0;
}

void stage0_deinit()
{
    safe_delete(spr1);
}

void stage0_update()
{
    switch (stage_state[0])
    {
    case 0:
        ///// 初期設定 /////
        spr1 = sprite_load(L"./Data/Images/01.png");

        ++stage_state[0];
    case 1:
        ///// パラメータの設定 /////
        ++stage_state[0];
    case 2:
        ///// 通常時 /////

        break;
    }
}

void stage0_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(spr1, 0, 0);
}
