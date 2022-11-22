#include "all.h"

void stage4_init()
{
    stage_state[4] = 0;
}

void stage4_deinit()
{
    player.Dinit();

    music::stop(game_bgm);
}

void stage4_update()
{
    switch (stage_state[4])
    {
    case 0:
        ///// 初期設定 /////
        player.Init();

        ++stage_state[4];
    case 1:
        ///// パラメーターの設定 /////
        ++stage_state[4];
    case 2:
        ///// 通常時 /////

        // ポーズ  F
        if (TRG(0) & PAD_TRG4)
        {
            pause = pause ? false : true;
        }

        // マウスカーソル
        std::ostringstream oss;                                 // 文字列ストリーム
        POINT point;                                            // 位置用の変数を宣言する
        GetCursorPos(&point);                                   // スクリーン座標を取得する
        ScreenToClient(window::getHwnd(), &point);              // クライアント座標に変換する
        mousePos.x = (float)(point.x);
        mousePos.y = (float)(point.y);

        if (!pause)
        {
            player.Update({ 100,500 });
        }

        break;
    }
}

void stage4_render()
{
    GameLib::clear(1, 1, 1);
}
