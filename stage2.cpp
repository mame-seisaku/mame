#include "all.h"

/*****•Ï”*****/

Sprite* sprStage2;

void stage2_init()
{
    stage_state[2] = 0;
}

void stage2_deinit()
{
    player.Dinit();

    safe_delete(sprStage2);

    music::stop(game_bgm);
}

void stage2_update()
{
    switch (stage_state[2])
    {
    case 0:
        ///// ‰Šúİ’è /////
        sprStage2 = sprite_load(L"./Data/Images/04.png");

        ++stage_state[2];
    case 1:
        ///// ƒpƒ‰ƒ[ƒ^‚Ìİ’è /////
        ++stage_state[2];
    case 2:
        ///// ’Êí /////
        break;
    }
}

void stage2_render()
{
    GameLib::clear(1, 1, 1);

    // ”wŒi
    sprite_render(sprStage2, 0, 0);


}
