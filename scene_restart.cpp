#include "all.h"

int restart_state;
int restart_timer;

Sprite* sprRestart;

stage R_anime;

void restart_init()
{
    restart_state = 0;
    restart_timer = 0;
}

void restart_deinit()
{
    safe_delete(sprRestart);
}

void restart_update()
{
    switch (restart_state)
    {
    case 0:
        ///// ‰ŠúÝ’è /////
        sprRestart = sprite_load(L"./Data/Images/elecAnime.png");

        ++restart_state;
    case 1:
        ///// ƒpƒ‰ƒ[ƒ^‚ÌÝ’è /////

        R_anime = {};
        R_anime.texSize = { 614,824 };
        R_anime.open = true;

        ++restart_state;
    case 2:
        ///// ’ÊíŽž /////

    //if(restart_timer>30)
        if (R_anime.end)
        {
            NotmouseClick(selectStage);
            break;
        }

        anime(&R_anime, 9, 5, false, 1);

        break;
    }
    ++restart_timer;
}

void restart_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(sprRestart, 461, -100, 1, 1, R_anime.texPos.x, 0, 614, 824);
}
