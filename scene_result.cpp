#include "all.h"

/*****変数*****/
int result_state;

Sprite* sprResult;

/// <summary>
/// 初期設定
/// </summary>
void result_init()
{
    result_state = 0;
}

/// <summary>
/// 終了処理
/// </summary>
void result_deinit()
{
    safe_delete(sprResult);
}

/// <summary>
/// 更新処理
/// </summary>
void result_update()
{
    switch (result_state)
    {
    case 0:
        ///// 初期化 /////
        sprResult = sprite_load(L"./Data/Images/result.png");
        

        ++result_state;
    case 1:
        ///// パラメータの設定 /////
        ++result_state;
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

/// <summary>
/// 描画処理
/// </summary>
void result_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(sprResult, 0, 0);
}
