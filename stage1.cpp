#include "all.h"

/*****変数*****/

obj2d stage1[STAGE1_MAX];

Sprite* spr2;

/// <summary>
/// 初期設定
/// </summary>
void stage1_init()
{
    stage_state[1] = 0;
}

/// <summary>
/// 終了処理
/// </summary>
void stage1_deinit()
{
    safe_delete(spr2);
}

/// <summary>
/// 更新処理
/// </summary>
void stage1_update()
{
    switch (stage_state[1])
    {
    case 0:
        ///// 初期設定 /////
        spr2 = sprite_load(L"./Data/Images/stage0.png");

        ++stage_state[1];
    case 1:
        ///// パラメータの設定 /////
        ++stage_state[1];
    case 2:
        ///// 通常時 /////



        break;
    }
}

/// <summary>
/// 描画処理
/// </summary>
void stage1_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(spr2, 0, 0);

    primitive::rect(player.pos, player.hsize * 2, player.hsize*0.005, 0, { 0,0,1,1 });
}
