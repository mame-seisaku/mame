#include "all.h"

/*****変数*****/

obj2d stage0[STAGE0_MAX];

Sprite* sprStage0;

extern VECTOR2 mousePos;

void stage0_init()
{
    stage_state[0] = 0;
}

void stage0_deinit()
{
    safe_delete(sprStage0);
}

void stage0_update()
{
    switch (stage_state[0])
    {
    case 0:
        ///// 初期設定 /////
        sprStage0 = sprite_load(L"./Data/Images/stage0.png");

        ++stage_state[0];
    case 1:
        ///// パラメータの設定 /////

        stage0[0].pos = { 768,764 };
        stage0[0].hsize = { 768, 64};
        stage0[1].pos = { 585,625 };
        stage0[1].hsize = { 95, 75 };
        stage0[2].pos = { 1430,640 };
        stage0[2].hsize = { 60, 60 };

        ++stage_state[0];
    case 2:
        ///// 通常時 /////
        
        // マウスカーソル
#ifdef _DEBUG
        std::ostringstream oss;                                 // 文字列ストリーム
        POINT point;                                            // 位置用の変数を宣言する
        GetCursorPos(&point);                                   // スクリーン座標を取得する
        ScreenToClient(window::getHwnd(), &point);              // クライアント座標に変換する
        mousePos.x = (float)(point.x);
        mousePos.y = (float)(point.y);
        oss << "(x=" << point.x << " y=" << point.y << ")";
        SetWindowTextA(window::getHwnd(), oss.str().c_str());   // タイトルバーにを表示させる
        debug::setString("PossibleStage:%d", PossibleStage);
#endif

        // 上下のめり込みチェック
        for (int i = 0; i < STAGE0_MAX; ++i)
        {
            if (hitCheck(&player, &stage0[i]))
            {
                // めり込み対策		// 当たり判定
                float dist;
                if (player.speed.y >= 0)
                    dist = check(&player, &stage0[i], DIR::DOWN);
                else
                    dist = check(&player, &stage0[i], DIR::UP);
                player.pos.y += dist;
                player.speed.y = 0;
            }
        }

        // 左右のめり込みチェック
        for (int i = 0; i < STAGE0_MAX; ++i)
        {
            if (hitCheck(&player, &stage0[i]))
            {
                // めり込み対策		// 当たり判定
                float dist;
                if (player.speed.x >= 0)
                    dist = check(&player, &stage0[i], DIR::RIGHT);
                else
                    dist = check(&player, &stage0[i], DIR::LEFT);
                player.pos.x += dist;
                player.speed.x = 0;
            }
        } 



        break;
    }
}

void stage0_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(sprStage0, 0, 0);

    // プレイヤー
    primitive::rect(player.pos, player.hsize * 2, player.hsize, 0, { 0,0,1,1 });

    primitive::rect(stage0[0].pos, stage0[0].hsize * 2, stage0[0].hsize, 0, { 1,1,1,1 });
    primitive::rect(stage0[1].pos, stage0[1].hsize * 2, stage0[1].hsize, 0, { 1,0,0,1 });
    primitive::rect(stage0[2].pos, stage0[2].hsize * 2, stage0[2].hsize, 0, { 0,1,0,1 });
}

