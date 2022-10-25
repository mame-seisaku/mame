#include "all.h"

/*****•Ï”*****/
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
        ///// ‰Šúİ’è /////
        spr1 = sprite_load(L"./Data/Images/01.png");

        ++stage_state[0];
    case 1:
        ///// ƒpƒ‰ƒ[ƒ^‚Ìİ’è /////
        ++stage_state[0];
    case 2:
        ///// ’Êí /////

        break;
    }
}

void stage0_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(spr1, 0, 0);
}
