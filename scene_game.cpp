#include "all.h"

/*****変数*****/
int game_state;

Sprite* sprGame;

Player player;

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
    player.Dinit();

    safe_delete(sprGame);
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
        player.Init();

        sprGame = sprite_load(L"./Data/Images/game.png");

        ++game_state;
    case 1:
        ///// パラメーターの設定 /////

        ++game_state;
    case 2:
        ///// 通常時 /////

        // 画面切り替え
        if (TRG(0) & PAD_SELECT)
        {
            nextScene = SCENE_TITLE;
            break;
        }

        // プレイヤー更新処理
        player.Update();


        break;
    }
}

/// <summary>
/// ゲームの描画処理
/// </summary>
void game_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(sprGame, 0, 0);   // 背景

    // プレイヤー更新処理    
    player.Render();
}
