#include "all.h"

/*****変数*****/
int game_state;

int PossibleStage;

bool pause;

Sprite* sprGame;
Sprite* sprPause;

Player player;

// extern 宣言
extern int stage;


/// <summary>
/// ゲームの初期設定
/// </summary>
void game_init()
{
    game_state = 0;
    pause = false;
}

/// <summary>
/// ゲームの終了処理
/// </summary>
void game_deinit()
{
    player.Dinit();

    safe_delete(sprGame);
    safe_delete(sprPause);
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
        sprPause = sprite_load(L"./Data/Images/pause.png");

        ++game_state;
    case 1:
        ///// パラメーターの設定 /////
        PossibleStage = 1;

        ++game_state;
    case 2:
        ///// 通常時 /////

        // 画面切り替え
        if (TRG(0) & PAD_SELECT)
        {
            nextScene = SCENE::RESULT;
            break;
        }
        // ポーズ画面
        if (TRG(0) & PAD_L1)
        {
            pause = pause ? false : true;
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

    // ポーズ画面
    if (pause)
    {
        sprite_render(sprPause, 0, 0);
    }
}
