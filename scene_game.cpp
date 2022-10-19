#include "all.h"

/*****変数*****/
int game_state;

/// <summary>
/// ゲームの初期設定
/// </summary>
void game_init()
{
    game_state = 0;
}

/// <summary>
/// ゲームの終了処理
/// </summary>
void game_deinit()
{

}

/// <summary>
/// ゲームの更新処理
/// </summary>
void game_update()
{
    switch (game_state)
    {
    case 0:
        ///// 初期設定 /////
        ++game_state;
    case 1:
        ///// パラメーターの設定 /////

        // test

        ++game_state;
    case 2:
        ///// 通常時 /////
        break;
    }
}

/// <summary>
/// ゲームの描画処理
/// </summary>
void game_render()
{
    GameLib::clear(1, 1, 1);
}
