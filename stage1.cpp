#include "all.h"

/*****変数*****/

stage stage1[STAGE1_MAX];


Sprite* spr1;
Sprite* sprBox1;
Sprite* sprTrolley;

VECTOR2 speed1;

extern VECTOR2 mousePos;
extern stage door;

extern Sprite* sprElec; // 電気
extern Sprite* sprDoor; // ドア

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
    player.Dinit();

    safe_delete(spr1);
    safe_delete(sprBox1);
    safe_delete(sprTrolley);


    safe_delete(sprElec);
    safe_delete(sprDoor);
    safe_delete(sprEV);
    safe_delete(sprEvPlayer);

    safe_delete(sprTerrain);

    safe_delete(sprPause);

    music::stop(game_bgm);
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

        spr1 = sprite_load(L"./Data/Images/04.png");
        sprBox1 = sprite_load(L"./Data/Images/box.png");
        sprTrolley = sprite_load(L"./Data/Images/trolley.png");

        sprElec = sprite_load(L"./Data/Images/elec.png");
        sprDoor = sprite_load(L"./Data/Images/door.png");
        sprEV = sprite_load(L"./Data/Images/EV.png");
        sprEvPlayer = sprite_load(L"./Data/Images/p.png");

        sprTerrain = sprite_load(L"./Data/Images/terrain.png");

        sprPause = sprite_load(L"./Data/Images/pause.png");

        ++stage_state[1];
    case 1:
        ///// パラメータの設定 /////

        // ポーズ
        pause = false;

        for (int i = 0; i < STAGE1_MAX; ++i)
        {
            stage1[i] = {};
        }

        // type
        // 1 トロッコ
        // 2 とびら　

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
        stage1[3].position = { 190,522 };
        stage1[3].pos = { 277,650 };
        stage1[3].hsize = { 90, 50 };
        stage1[3].type = 1;
        stage1[3].exist = true;
        // BOX
        stage1[4].position = { 890,523 };
        stage1[4].pos = { 979,612.5f };
        stage1[4].hsize = { 89, 88.5f };
        stage1[4].type = 0;
        stage1[4].exist = true;
        // stop
        stage1[5].pos = { 52,650 };
        stage1[5].hsize = { 135, 50 };
        stage1[5].type = 0;
        stage1[5].exist = true;

        // 扉
        stage1[6].position = { 1239,530 };
        stage1[6].pos = { 1330,620 };
        stage1[6].hsize = { 80, 89 };
        stage1[6].texPos = {};
        stage1[6].texSize = { 178,177 };
        stage1[6].type = 2;
        stage1[6].exist = true;
        stage1[6].open = false;

        // EvPlayer
        EvPlayer = { stage1[6].position.x, stage1[6].position.y };

        // ドア最後
        door = {};

        // 電気
        Elec = {};

        music::play(game_bgm, true);

        ++stage_state[1];
    case 2:
        ///// 通常時 /////

        // シーン切り替え
        if (door.end)
        {
            EvPlayer.y -= 10;
        }
        if (EvPlayer.y < -200)
        {
            nextScene = SCENE::RESULT;
            break;
        }

        // ポーズ  F
        if (TRG(0) & PAD_TRG4)
        {
            pause = pause ? false : true;
        }

        if (!pause)
        {

            player.Update({100,200});

            // マウスカーソル
#ifdef _DEBUG
#endif
            std::ostringstream oss;                                 // 文字列ストリーム
            POINT point;                                            // 位置用の変数を宣言する
            GetCursorPos(&point);                                   // スクリーン座標を取得する
            ScreenToClient(window::getHwnd(), &point);              // クライアント座標に変換する
            mousePos.x = (float)(point.x);
            mousePos.y = (float)(point.y);
            oss << "(x=" << point.x << " y=" << point.y << ")";
            SetWindowTextA(window::getHwnd(), oss.str().c_str());   // タイトルバーにを表示させる
            //debug::setString("PossibleStage:%d", PossibleStage);
            //debug::setString("toroko:%f", stage1[3].pos.x);
            debug::setString("mousePos.x:%f,mousePos.y:%f", mousePos.x, mousePos.y);
            debug::setString("stage1[3].pos.x:%f", stage1[3].pos.x);
            debug::setString("stage1[3].pos.y:%f", stage1[3].pos.y);

            // 扉アニメ
            if (stage1[6].open)
                anime(&stage1[6], 7, 10, false, 0);

            // クリア判定
            if (stage1[6].end && stage1[6].one && !door.close)
            {
                player.clear = true;
                door = stage1[6];
                door.state = 0;
                door.close = true;
            }

            if (player.clear)
            {
                player.pos.x = stage1[6].position.x + 51;    // ドアの位置に移動
                // 電気を戻す
                player.elec = true;
                for (int i = 0; i < STAGE0_MAX; ++i)
                {
                    stage1[i].elec = false;
                }

                // 扉しまる
                anime(&door, 7, 10, false, 0);
            }



            // マウスでの憑依操作
            if (mousePos.x > stage1[3].pos.x - 90 && mousePos.y > stage1[3].pos.y - 50 && mousePos.x < stage1[3].pos.x + 90 && mousePos.y - 50 < stage1[3].pos.y + 110)
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
                    if (Elec.moveVec.y > 0)
                    {
                        // 当たった
                        if (Elec.pos.x >= ElecPos.x && Elec.pos.y >= ElecPos.y)
                        {
                            player.elec = false;    // プレイヤーの電気消す
                            Elec.exist = false;
                            stage1[3].elec = true;
                        }
                    }
                    else
                    {
                        // 当たった
                        if (Elec.pos.x >= ElecPos.x)
                        {
                            player.elec = false;    // プレイヤーの電気消す
                            Elec.exist = false;
                            stage1[3].elec = true;
                        }
                    }
                }
                // 左下方向へ進む
                else
                {
                    if (Elec.moveVec.y > 0)
                    {
                        // 当たった
                        if (Elec.pos.x <= ElecPos.x && Elec.pos.y >= ElecPos.y)
                        {
                            player.elec = false;    // プレイヤーの電気消す
                            Elec.exist = false;
                            stage1[3].elec = true;
                        }
                    }
                    else
                    {
                        // 当たった
                        if (Elec.pos.x <= ElecPos.x)
                        {
                            player.elec = false;    // プレイヤーの電気消す
                            Elec.exist = false;
                            stage1[3].elec = true;
                        }
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
                    if (stage1[i].type == 1 && stage1[i].elec)
                    {
                        player.pos.x += speed1.x;
                    }

                    // 扉
                    if (stage1[i].type == 2)
                    {
                        stage1[i].open = true;
                        break;
                    }

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
            if (player.elec == true)
            {
                player.pos.x += player.speed.x;
            }
            else if (stage1[3].elec == true)
            {
                stage1[3].pos.x += speed1.x;
                stage1[3].position.x = stage1[3].pos.x - 86;
            }

            // 左右のめり込みチェック
            for (int i = 0; i < STAGE0_MAX; ++i)
            {
                if (player.elec == true) {
                    if (hitCheck(&player, &stage1[i]))
                    {
                        // 扉
                        if (stage1[i].type == 2)
                        {
                            stage1[i].open = true;
                            break;
                        }

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
}

/// <summary>
/// 描画処理
/// </summary>
void stage1_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(spr1, 0, 0);

    
#ifdef _DEBUG
    for (int i = 0; i < STAGE1_MAX; ++i)
    {
        primitive::rect(stage1[i].pos, stage1[i].hsize * 2, stage1[i].hsize, 0, { 1,0,0, 0 });
    }
#endif
    for (int y = 0; y < 2; ++y)
    {
        for (int x = 0; x < 3; ++x)
        {
            sprite_render(sprTerrain, x * 64, 600 + (y * 35), 1, 1, 64, 0, 64, 64);
        }
    }
    for (int y = 0; y < 2; ++y)
    {
        for (int x = 0; x < 24; ++x)
        {
            sprite_render(sprTerrain, 64 * x, 635 + (64 * (y + 1)), 1, 1, 64, 0, 64, 64);
        }
    }


    // 箱
    sprite_render(sprBox1, stage1[4].position.x, stage1[4].position.y);
    // トロッコ
    sprite_render(sprTrolley, stage1[3].position.x, stage1[3].position.y, 1, 1, stage1[3].elec * 178, 0, 177, 177);
   
    // エレベーター
    sprite_render(sprEV, stage1[6].position.x - 5, stage1[6].position.y - 650);

    // playerEv
    if (door.end)
        sprite_render(sprEvPlayer, EvPlayer.x - 5, EvPlayer.y);

    // 扉
    sprite_render(sprDoor, stage1[6].position.x, stage1[6].position.y, 1, 1, stage1[6].texPos.x, stage1[6].texPos.y, stage1[6].texSize.x, stage1[6].texSize.y);

    // 電気
    if (Elec.exist)
        sprite_render(sprElec, Elec.pos.x, Elec.pos.y, 0.5f, 0.5f, 0, 0, 128, 128, 64, 64);

    player.Render();

    // 扉
    sprite_render(sprDoor, door.position.x, door.position.y, 1, 1, door.texPos.x, 177, door.texSize.x, door.texSize.y);

    // ポーズ画面
    if (pause)
    {
        sprite_render(sprPause, 0, 0);
    }

#ifdef _DEBUG
    debug::setString("player%d", player.elec);
#endif
}
