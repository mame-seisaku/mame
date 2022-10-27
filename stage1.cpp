#include "all.h"

/*****変数*****/

stage stage1[STAGE1_MAX];

VECTOR2 operation[STAGE1_MAX];

Sprite* spr2;

extern VECTOR2 mousePos;


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

        for (int i = 0; i < STAGE1_MAX; ++i)
        {
            stage1[i] = {};
        }

        // 床
        stage1[0].pos = { 768,764 };
        stage1[0].hsize = { 768, 64 };
        stage1[0].exist = true;
        // 左壁
        stage1[1].pos = { 5,412 };
        stage1[1].hsize = { 5,412 };
        stage1[1].exist = true;
        // 右壁
        stage1[2].pos = { 1531,412 };
        stage1[2].hsize = { 15,412 };
        stage1[2].exist = true;
        //オブジェ
        stage1[3].pos = { 768,678 };
        stage1[3].hsize = { 50, 22 };
        stage1[3].exist = true;


        ++stage_state[1];
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

        player.pos.y += player.speed.y;

        // 上下のめり込みチェック
        for (int i = 0; i < STAGE0_MAX; ++i)
        {
            if (hitCheck(&player, &stage1[i]))
            {
                // めり込み対策		// 当たり判定
                float dist;
                if (player.speed.y >= 0)
                    dist = check(&player, &stage1[i], DIR::DOWN);
                else
                    dist = check(&player, &stage1[i], DIR::UP);
                player.pos.y += dist;
                player.speed.y = 0;
            }
        }

        player.pos.x += player.speed.x;

        // 左右のめり込みチェック
        for (int i = 0; i < STAGE0_MAX; ++i)
        {
            if (hitCheck(&player, &stage1[i]))
            {
                // めり込み対策		// 当たり判定
                float dist;
                if (player.speed.x >= 0)
                    dist = check(&player, &stage1[i], DIR::RIGHT);
                else
                    dist = check(&player, &stage1[i], DIR::LEFT);
                player.pos.x += dist;
                player.speed.x = 0;
            }
        }
        if (TRG(0) & PAD_R3)
        {
            if (mousePos.x > 718 && mousePos.y > 656 && mousePos.x < 818 && mousePos.y < 700)
            {
            }
        }

                stage1[3].pos.x = player.pos.x;
        operation[0] = player.pos;

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

    primitive::rect(operation[0], player.hsize * 2, player.hsize, 0, { 0,0,1,1 });
    
    for (int i = 0; i < STAGE1_MAX; ++i)
    {
        primitive::rect(stage1[i].pos, stage1[i].hsize * 2, stage1[i].hsize, 0, { 1,0,0,1 });
    }

}
