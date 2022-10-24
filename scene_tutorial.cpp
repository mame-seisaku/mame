#include "all.h"

/*****•Ï”*****/
int tutorial_state;

Sprite* sprTutorial;

void tutorial_init()
{
    tutorial_state = 0;
}

void tutorial_deinit()
{
    safe_delete(sprTutorial);
}

void tutorial_update()
{
    switch (tutorial_state)
    {
    case 0:
        ///// ‰Šú‰» /////
        sprTutorial = sprite_load(L"./Data/Images/tutorial.png");

        ++tutorial_state;
    case 1:
        ///// ƒpƒ‰ƒ[ƒ^‚Ìİ’è
        ++tutorial_state;
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

void tutorial_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(sprTutorial, 0, 0);
}
