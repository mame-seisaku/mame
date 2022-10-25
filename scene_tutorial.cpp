#include "all.h"

<<<<<<< HEAD
int tutorial_state;

=======
/*****変数*****/
int tutorial_state;

Sprite* sprTutorial;

/// <summary>
/// 初期設定
/// </summary>
>>>>>>> 2ccefa9e3716e6aa28dc92d8de0ebaeab916b8d8
void tutorial_init()
{
    tutorial_state = 0;
}

<<<<<<< HEAD
void tutorial_deinit()
{

}

=======
/// <summary>
/// 終了処理
/// </summary>
void tutorial_deinit()
{
    safe_delete(sprTutorial);
}

/// <summary>
/// 更新処理
/// </summary>
>>>>>>> 2ccefa9e3716e6aa28dc92d8de0ebaeab916b8d8
void tutorial_update()
{
    switch (tutorial_state)
    {
    case 0:
<<<<<<< HEAD
        ++tutorial_state;
    case 1:
        ++tutorial_state;
    case 2:
=======
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

>>>>>>> 2ccefa9e3716e6aa28dc92d8de0ebaeab916b8d8
        break;
    }
}

<<<<<<< HEAD
void tutorial_render()
{

=======
/// <summary>
/// 描画処理
/// </summary>
void tutorial_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(sprTutorial, 0, 0);
>>>>>>> 2ccefa9e3716e6aa28dc92d8de0ebaeab916b8d8
}
