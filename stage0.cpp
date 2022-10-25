#include "all.h"

/*****変数*****/

stage stage0[STAGE0_MAX];

Sprite* sprStage0;
Sprite* sprStage0Floor;

extern VECTOR2 mousePos;

void stage0_init()
{
    stage_state[0] = 0;
}

void stage0_deinit()
{
    safe_delete(sprStage0);
    safe_delete(sprStage0Floor);
}

void stage0_update()
{
    switch (stage_state[0])
    {
    case 0:
        ///// 初期設定 /////
        sprStage0 = sprite_load(L"./Data/Images/stage0.png");
        sprStage0Floor = sprite_load(L"./Data/Images/03.png");

        ++stage_state[0];
    case 1:
        ///// パラメータの設定 /////

        for (int i = 0; i < STAGE0_MAX; ++i)
        {
            stage0[i] = {};
        }

        // 床
        stage0[0].position = { 0,700 };
        stage0[0].pos = { 768,764 };
        stage0[0].hsize = { 768, 64};
        stage0[0].type = 0;
        stage0[0].exist = true;
        // 四角
        stage0[1].position = { 0,700 };
        stage0[1].pos = { 585,625 };
        stage0[1].hsize = { 95, 75 };
        stage0[1].type = 1;
        stage0[1].exist = true;
        // 扉
        stage0[2].pos = { 1430,640 };
        stage0[2].hsize = { 60, 60 };
        stage0[2].type = 2;
        stage0[2].exist = true;
        // 左壁
        stage0[3].pos = { 5,412 };
        stage0[3].hsize = { 5,412 };
        stage0[3].type = 0;
        stage0[3].exist = true;
        // アンチ
        stage0[4].position = {70,630};
        stage0[4].pos = {105,640};
        stage0[4].hsize = { 35,10 };
        stage0[4].type = 0;
        stage0[4].exist = true;

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

        // 位置にスピードを足す
        //if (player.moveFlag)
        //{
            player.pos.y += player.speed.y;
        //}
        //else
        //{
        //    player.speed.y = 0;
        //}

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

        // 位置にスピードを足す
        //if (player.moveFlag)
        //{
            player.pos.x += player.speed.x;
        //}
        //else
        //{
        //    player.speed.x = 0;
        //}

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

        // 四角の色設定
        for (int i = 0; i < STAGE0_MAX; ++i)
        {
            switch (stage0[i].type)
            {
            case 0:
                stage0[i].color = { 1,1,1,1 };
                break;
            case 1:
                stage0[i].color = { 1,0,0,1 };
                break;
            case 2:
                stage0[i].color = { 0,1,0,1 };
                break;
            }
        }

        // 床スクロール
        if (STATE(0) & PAD_TRG1)
        {
            stage0[0].position.x += 10;
        }
        // 範囲外
        if (stage0[0].position.x > 0)
        {
            stage0[0].position.x = -1536;
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

    // 地形描画
    for (int i = 0; i < STAGE0_MAX; ++i)
    {
        primitive::rect(stage0[i].pos, stage0[i].hsize * 2, stage0[i].hsize, 0, { stage0[i].color.x,stage0[i].color.y,stage0[i].color.z,stage0[i].color.w });
    }

    sprite_render(sprStage0Floor, stage0[0].position.x, stage0[0].position.y);
}

