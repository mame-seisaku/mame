#include "all.h"

/*****変数*****/
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
        ///// 初期化 /////
        sprTutorial = sprite_load(L"./Data/Images/tutorial.png");

        ++tutorial_state;
    case 1:
        ///// パラメータの設定
        ++tutorial_state;
    case 2:
        ///// 通常時 /////

        // 画面切り替え
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
