#include "all.h"

/*****•Ï”*****/
int result_state;

Sprite* sprResult;

void result_init()
{
    result_state = 0;
}

void result_deinit()
{
    safe_delete(sprResult);
}

void result_update()
{
    switch (result_state)
    {
    case 0:
        ///// ‰Šú‰» /////
        sprResult = sprite_load(L"./Data/Images/result.png");
        

        ++result_state;
    case 1:
        ///// ƒpƒ‰ƒ[ƒ^‚Ìİ’è /////
        ++result_state;
    case 2:
        ///// ’Êí /////

        // ‰æ–ÊØ‚è‘Ö‚¦
        if (TRG(0) & PAD_SELECT)
        {
            nextScene = SCENE::TITLE;
            break;
        }

        break;
    }
}

void result_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(sprResult, 0, 0);
}
