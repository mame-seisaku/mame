#include "all.h"

/*****変数*****/

stage stage1[STAGE1_MAX];


Sprite* spr1;
Sprite* sprBox1;
Sprite* sprTrolley;
VECTOR2 speed1;

extern VECTOR2 mousePos;
extern Sprite* sprElec; // 電気

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
    safe_delete(spr1);
    safe_delete(sprBox1);
    safe_delete(sprTrolley);
    safe_delete(sprElec);
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
        player.Init();

        spr1 = sprite_load(L"./Data/Images/stage0.png");
        sprBox1 = sprite_load(L"./Data/Images/box.png");
        sprTrolley = sprite_load(L"./Data/Images/trolley.png");

        sprElec = sprite_load(L"./Data/Images/elec.png");

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
        stage1[0].type = 0;
        stage1[0].exist = true;
        // 左壁
        stage1[1].pos = { 5,412 };
        stage1[1].hsize = { 5,412 };
        stage1[1].type = 0;
        stage1[1].exist = true;
        // 右壁
        stage1[2].pos = { 1531,412 };
        stage1[2].hsize = { 15,412 };
        stage1[2].type = 0;
        stage1[2].exist = true;
        //トロッコ
        stage1[3].position = { 682,522 };
        stage1[3].pos = { 768,650 };
        stage1[3].hsize = { 90, 50 };
        stage1[3].type = 0;
        stage1[3].exist = true;
        // BOX
        stage1[4].position = { 890,523 };
        stage1[4].pos = { 979,612.5f };
        stage1[4].hsize = { 89, 88.5f };
        stage1[4].type = 0;
        stage1[4].exist = true;
        // stop
        stage1[5].pos = { 52,658 };
        stage1[5].hsize = { 42, 42 };
        stage1[5].type = 0;
        stage1[5].exist = true;

        // 電気
        Elec = {};

        ++stage_state[1];
    case 2:
        ///// 通常時 /////

        player.Update();

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

        // マウスでの憑依操作
        if (mousePos.x > stage1[3].pos.x - 80 && mousePos.y > stage1[3].pos.y - 50 && mousePos.x < stage1[3].pos.x + 80 && mousePos.y < stage1[3].pos.y + 50)
        {
            // 電気を飛ばす
            if (TRG(0) & PAD_L3)
            {
                // プレイヤーに電気があれば
                if (!Elec.exist && player.elec)
                    SetElecMove();

            }
            // 電気回収
            if (TRG(0) & PAD_R3 && !player.elec)
            {
                Elec.exist = false;
                stage1[3].elec = false;
                player.elec = true;
            }
        }

        // 電気の移動と、当たったか判定
        if (Elec.exist) // 存在したら
        {
            // 移動
            Elec.pos.x += Elec.moveVec.x * 2;
            Elec.pos.y += Elec.moveVec.y * 2;

            // 右下方向へ進む
            if (Elec.moveVec.x > 0)
            {
                // 当たった
                if (Elec.pos.x >= ElecPos.x || Elec.pos.y >= ElecPos.y)
                {
                    player.elec = false;    // プレイヤーの電気消す
                    Elec.exist = false;
                    stage1[3].elec = true;
                }
            }
            // 左下方向へ進む
            else
            {
                // 当たった
                if (Elec.pos.x <= ElecPos.x || Elec.pos.y >= ElecPos.y)
                {
                    player.elec = false;    // プレイヤーの電気消す
                    Elec.exist = false;
                    stage1[3].elec = true;
                }
            }

        }


        if (STATE(0) & PAD_LEFT)
        {
            if (!(STATE(0) & PAD_RIGHT))
            {
                speed1.x = -PLAYER_MOVE;
            }
        }
        else if (STATE(0) & PAD_RIGHT)
        {
            if (!(STATE(0) & PAD_LEFT))
            {
                speed1.x = PLAYER_MOVE;
            }
        }
        else
        {
            speed1.x = 0;
        }

        player.pos.y += player.speed.y;

        // 上下のめり込みチェック
        for (int i = 0; i < STAGE0_MAX; ++i)
        {
            if (hitCheck(&player, &stage1[i]))
            {

                //上に乗った時の移動
                    //if (stop == false) {
                if (stage1[i].type == 0 && stage1[i].elec)
                {
                    player.pos.x += speed1.x;
                }
                //}

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

        //操作切り替え
        if (player.elec == true) {
            player.pos.x += player.speed.x;
        }
        else if (stage1[3].elec == true) {
            stage1[3].pos.x += speed1.x;
            stage1[3].position.x = stage1[3].pos.x - 86;

        }

        // 左右のめり込みチェック
        for (int i = 0; i < STAGE0_MAX; ++i)
        {
            if (player.elec == true) {
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
            if (player.elec == false) {
                if (hitCheck(&player, &stage1[i]))
                {
                    // めり込み対策		// 当たり判定
                    float dist;
                    if (speed1.x >= 0)
                        dist = check(&player, &stage1[i], DIR::RIGHT);
                    else
                        dist = check(&player, &stage1[i], DIR::LEFT);
                    player.pos.x += dist;
                    speed1.x = 0;
                }
                if (hitCheck(&stage1[3], &player))
                {
                    // めり込み対策		// 当たり判定
                    float dist;
                    if (speed1.x >= 0)
                        dist = check(&stage1[3], &player, DIR::RIGHT);
                    else
                        dist = check(&stage1[3], &player, DIR::LEFT);
                    stage1[3].pos.x += dist;
                    speed1.x = 0;
                    stage1[3].position.x += dist;
                }
                if (hitCheck(&stage1[3], &stage1[1]))
                {
                    // めり込み対策		// 当たり判定
                    float dist;
                    if (speed1.x >= 0)
                        dist = check(&stage1[3], &stage1[1], DIR::RIGHT);
                    else
                        dist = check(&stage1[3], &stage1[1], DIR::LEFT);
                    stage1[3].pos.x += dist;
                    speed1.x = 0;
                    stage1[3].position.x += dist;
                }
                if (hitCheck(&stage1[3], &stage1[4]))
                {
                    // めり込み対策		// 当たり判定
                    float dist;
                    if (speed1.x >= 0)
                        dist = check(&stage1[3], &stage1[4], DIR::RIGHT);
                    else
                        dist = check(&stage1[3], &stage1[4], DIR::LEFT);
                    stage1[3].pos.x += dist;
                    speed1.x = 0;
                    stage1[3].position.x += dist;
                }
                if (hitCheck(&stage1[3], &stage1[5]))
                {
                    // めり込み対策		// 当たり判定
                    float dist;
                    if (speed1.x >= 0)
                        dist = check(&stage1[3], &stage1[5], DIR::RIGHT);
                    else
                        dist = check(&stage1[3], &stage1[5], DIR::LEFT);
                    stage1[3].pos.x += dist;
                    speed1.x = 0;
                    stage1[3].position.x += dist;
                }
            }
        }





        break;
    }
}

/// <summary>
/// 描画処理
/// </summary>
void stage1_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(spr1, 0, 0);

    player.Render();
    
#ifdef _DEBUG
    for (int i = 0; i < STAGE1_MAX; ++i)
    {
        primitive::rect(stage1[i].pos, stage1[i].hsize * 2, stage1[i].hsize, 0, { 1,0,0,1 });
    }
#endif

    // 箱
    sprite_render(sprBox1, stage1[4].position.x, stage1[4].position.y);
    // トロッコ
    sprite_render(sprTrolley, stage1[3].position.x, stage1[3].position.y, 1, 1, stage1[3].elec * 178, 0, 177, 177);
   
    // 電気
    if (Elec.exist)
        sprite_render(sprElec, Elec.pos.x, Elec.pos.y, 0.5f, 0.5f, 0, 0, 128, 128, 64, 64);

#ifdef _DEBUG
    debug::setString("player%d", player.elec);
   

#endif
}
