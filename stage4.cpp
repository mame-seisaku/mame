#include "all.h"

/*****変数*****/

stage stage4[STAGE4_MAX];

VECTOR2 speed4;

extern Sprite* sprSyoukouki;    // 昇降機
extern Sprite* sprBox;          // box
extern Sprite* sprStage0;       // 背景

void stage4_init()
{
    stage_state[4] = 0;
}

void stage4_deinit()
{
    player.Dinit();

    safe_delete(sprStage0);
    safe_delete(sprBox);
    safe_delete(sprUI);
    safe_delete(sprElec);
    safe_delete(sprDoor);
    safe_delete(sprEV);
    safe_delete(sprEvPlayer);
    safe_delete(sprMouse);
    safe_delete(sprTerrain);
    safe_delete(sprPause);
    safe_delete(sprWhite);
    safe_delete(sprHelp);


    music::stop(game_bgm);
}

void stage4_update()
{
    switch (stage_state[4])
    {
    case 0:
        ///// 初期設定 /////
        player.Init();

        sprStage0 = sprite_load(L"./Data/Images/04.png");
        sprBox = sprite_load(L"./Data/Images/boxMove.png");
        sprSyoukouki = sprite_load(L"./Data/Images/syoukouki2.png");
        sprUI = sprite_load(L"./Data/Images/UI.png");
        sprElec = sprite_load(L"./Data/Images/elec.png");
        sprDoor = sprite_load(L"./Data/Images/door.png");
        sprEV = sprite_load(L"./Data/Images/EV.png");
        sprEvPlayer = sprite_load(L"./Data/Images/p.png");
        sprMouse = sprite_load(L"./Data/Images/mouse.png");
        sprTerrain = sprite_load(L"./Data/Images/terrain.png");
        sprPause = sprite_load(L"./Data/Images/pause.png");
        sprWhite = sprite_load(L"./Data/Images/white.png");
        sprHelp = sprite_load(L"./Data/Images/help.png");

        ++stage_state[4];
    case 1:
        ///// パラメーターの設定 /////

        // ポーズ
        pause = false;

        // ステージ
        for (int i = 0; i < STAGE4_MAX; ++i)
        {
            stage4[i] = {};
        }

        // type
        // 0 壁
        // 1 
        // 2 扉
        // 3 昇降機 たて
        // 4 昇降機 よこ
        // 5 

        // 左床
        stage4[0].pos = { 100,764 };
        stage4[0].hsize = { 100,64 };
        stage4[0].type = 0;
        stage4[0].exist = true;

        // 扉 
        stage4[1].position = { 1315,280 };
        stage4[1].pos = { 1405,360 };
        stage4[1].hsize = { 80, 89 };
        stage4[1].texPos = {};
        stage4[1].texSize = { 178,177 };
        stage4[1].type = 2;
        stage4[1].exist = true;
        stage4[1].open = false;

        // 昇降機 左
        stage4[2].position = { 400,510 };
        stage4[2].pos = { stage4[2].position.x + 89,stage4[2].position.y + 140 };
        stage4[2].hsize = { 89, 50 };
        stage4[2].type = 3;
        stage4[2].exist = true;

        // 昇降機 真ん中
        stage4[3].position = { 1000,510 };
        stage4[3].pos = { stage4[3].position.x + 89,stage4[3].position.y + 140 };
        stage4[3].hsize = { 89, 50 };
        stage4[3].type = 4;
        stage4[3].exist = true;

        // 昇降機 右
        stage4[4].position = { 1090,150 };
        stage4[4].pos = { stage4[4].position.x + 89,stage4[4].position.y + 140 };
        stage4[4].hsize = { 89, 50 };
        stage4[4].type = 3;
        stage4[4].exist = true;

        // 左？壁
        //stage4[4].position = { 300,764 };
        stage4[5].pos = { 254,700 };
        stage4[5].hsize = { 60,64 };
        stage4[5].type = 0;
        stage4[5].exist = true;

        // 真ん中壁
        stage4[6].pos = { 710,598 };
        stage4[6].hsize = { 45,256 };
        stage4[6].type = 0;
        stage4[6].exist = true;

        // ドア下床
        stage4[7].pos = { 1405,481 };
        stage4[7].hsize = { 130,32 };
        stage4[7].type = 0;
        stage4[7].exist = true;

        // EvPlayer
        EvPlayer = { stage4[1].position.x, stage4[1].position.y + 100 };

        // ドア最後
        door = {};

        // 電気
        Elec = {};

        speed4 = {};

        music::play(game_bgm, true);


        ++stage_state[4];
    case 2:
        ///// 通常時 /////

        // シーン切り替え
        if (door.end)
        {
            player.pos.y = EvPlayer.y - 45;
            EvPlayer.y -= STAGE_MOVE;
        }
        if (EvPlayer.y < -200)
        {
            if (PossibleStage < 5)PossibleStage = 5;
            nextScene = SCENE::RESULT;
            break;
        }

        // ポーズ  F
        if (TRG(0) & PAD_TRG4)
        {
            pause = pause ? false : true;
        }
        if (mousePos.x > 1440 && mousePos.y > 0 && mousePos.x < 1536 && mousePos.y < 70)
        {
            if (TRG(0) & PAD_L3)pause = pause ? false : true;
        }

        // 死んだ判定
        if (player.pos.y > 1600)
        {
            player.pos.y = -100;
            nextScene = SCENE::RESTART;
            break;
        }

        // マウスカーソル
        std::ostringstream oss;                                 // 文字列ストリーム
        POINT point;                                            // 位置用の変数を宣言する
        GetCursorPos(&point);                                   // スクリーン座標を取得する
        ScreenToClient(window::getHwnd(), &point);              // クライアント座標に変換する
        mousePos.x = (float)(point.x);
        mousePos.y = (float)(point.y);
#ifdef _DEBUG
        oss << "(x=" << point.x << " y=" << point.y << ")";
        SetWindowTextA(window::getHwnd(), oss.str().c_str());   // タイトルバーにを表示させる
        debug::setString("mousePos.x:%f,mousePos.y:%f", mousePos.x, mousePos.y);
#endif

        if (!pause)
        {
            player.Update({ 100,600 });

            // 扉アニメ
            if (stage4[1].open)
                anime(&stage4[1], 7, 10, false, 0);

            // クリア判定
            if (stage4[1].end && stage4[1].one && !door.close)
            {
                player.clear = true;
                door = stage4[1];
                door.state = 0;
                door.close = true;
            }

            // クリア判定
            if (player.clear)
            {
                player.pos.x = stage4[1].position.x + 71;    // ドアの位置に移動
                // 電気を戻す
                player.elec = true;
                for (int i = 0; i < STAGE4_MAX; ++i)
                {
                    stage4[i].elec = false;
                }

                // 扉しまる
                anime(&door, 7, 10, false, 0);
            }

            if (mousePos.x > stage4[2].pos.x - 90 && mousePos.y > stage4[2].pos.y - 50 && mousePos.x < stage4[2].pos.x + 90 && mousePos.y - 50 < stage4[2].pos.y + 110 ||
                mousePos.x > stage4[3].pos.x - 90 && mousePos.y > stage4[3].pos.y - 50 && mousePos.x < stage4[3].pos.x + 90 && mousePos.y - 50 < stage4[3].pos.y + 110 ||
                mousePos.x > stage4[4].pos.x - 90 && mousePos.y > stage4[4].pos.y - 50 && mousePos.x < stage4[4].pos.x + 90 && mousePos.y - 50 < stage4[4].pos.y + 110)
            {
                MouseTexPos.x = 100;
            }
            else
            {
                MouseTexPos.x = 0;
            }


            // マウスでの憑依操作
            for (int i = 2; i < 5; ++i)
            {
                if (mousePos.x > stage4[i].pos.x - 90 && mousePos.y > stage4[i].pos.y - 50 && mousePos.x < stage4[i].pos.x + 90 && mousePos.y - 50 < stage4[i].pos.y + 110)
                {
                    // 電気を飛ばす
                    if (TRG(0) & PAD_L3)
                    {
                        // プレイヤーに電気があれば
                        if (!Elec.exist && player.elec)
                        {
                            SetElecMove();
                            Elec.type = i;
                        }
                    }
                    // 電気回収
                    if (TRG(0) & PAD_R3 && !player.elec)
                    {
                        for (int j = 2; j < 5; ++j)
                        {
                            if (i == j)continue;

                            stage4[j].elec = false;
                        }

                        Elec.exist = false;
                        stage4[i].elec = false;
                        player.elec = true;
                    }
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
                            stage4[Elec.type].elec = true;
                        }
                    }
                    else
                    {
                        // 当たった
                        if (Elec.pos.x >= ElecPos.x)
                        {
                            player.elec = false;    // プレイヤーの電気消す
                            Elec.exist = false;
                            stage4[Elec.type].elec = true;
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
                            stage4[Elec.type].elec = true;
                        }
                    }
                    else
                    {
                        // 当たった
                        if (Elec.pos.x <= ElecPos.x)
                        {
                            player.elec = false;    // プレイヤーの電気消す
                            Elec.exist = false;
                            stage4[Elec.type].elec = true;
                        }
                    }
                }
            }

            if (STATE(0) & PAD_UP)
            {
                if (!(STATE(0) & PAD_DOWN))
                {
                    speed4.y = -PLAYER_MOVE;
                }
            }
            else if (STATE(0) & PAD_DOWN)
            {
                if (!(STATE(0) & PAD_UP))
                {
                    speed4.y = PLAYER_MOVE;
                }
            }
            else
            {
                speed4.y = 0;
            }
            if (STATE(0) & PAD_LEFT)
            {
                if (!(STATE(0) & PAD_RIGHT))
                {
                    speed4.x = -PLAYER_MOVE;
                }
            }
            else if (STATE(0) & PAD_RIGHT)
            {
                if (!(STATE(0) & PAD_LEFT))
                {
                    speed4.x = PLAYER_MOVE;
                }
            }
            else
            {
                speed4.x = 0;
            }

            // 昇降機操作
            for (int i = 2; i < 5; ++i)
            {
                if (stage4[i].elec)
                {
                    if (i == 3)
                    {
                        stage4[i].pos.x += speed4.x;
                        stage4[i].position.x += speed4.x;

                        if (stage4[i].position.x < 750)
                        {
                            stage4[i].position.x = 750;
                            stage4[i].pos.x = stage4[i].position.x + 89;
                        }
                        if (stage4[i].position.x > 1100)
                        {
                            stage4[i].position.x = 1100;
                            stage4[i].pos.x = stage4[i].position.x + 89;
                        }

                        continue;
                    }

                    stage4[i].pos.y += speed4.y;
                    stage4[i].position.y += speed4.y;

                    if (i == 2)
                    {
                        if (stage4[i].position.y < 100)
                        {
                            stage4[i].position.y = 100;
                            stage4[i].pos.y = stage4[i].position.y + 140;
                        }
                        if (stage4[i].position.y > 600)
                        {
                            stage4[i].position.y = 600;
                            stage4[i].pos.y = stage4[i].position.y + 140;
                        }
                    }

                    if (i == 4)
                    {
                        if (stage4[i].position.y < 100)
                        {
                            stage4[i].position.y = 100;
                            stage4[i].pos.y = stage4[i].position.y + 140;
                        }
                        if (stage4[i].position.y > 430)
                        {
                            stage4[i].position.y = 430;
                            stage4[i].pos.y = stage4[i].position.y + 140;
                        }
                    }
                }
            }

            // 位置にスピードを足す
            player.pos.y += player.speed.y;

            // 上下のめり込みチェック
            for (int i = 0; i < STAGE4_MAX; ++i)
            {
                if (hitCheck(&player, &stage4[i]))
                {
                    // 扉
                    if (stage4[i].type == 2)
                    {
                        stage4[i].open = true;
                        continue;
                    }

                    // めり込み対策		// 当たり判定
                    float dist;
                    if (player.speed.y >= 0)
                        dist = check(&player, &stage4[i], DIR::DOWN);
                    else
                        dist = check(&player, &stage4[i], DIR::UP);
                    player.pos.y += dist;
                    player.speed.y = 0;
                }
            }

            // 位置にスピードを足す         
            player.pos.x += player.speed.x;

            // 左右のめり込みチェック
            for (int i = 0; i < STAGE4_MAX; ++i)
            {
                if (hitCheck(&player, &stage4[i]))
                {
                    // 扉
                    if (stage4[i].type == 2)
                    {
                        stage4[i].open = true;
                        continue;
                    }

                    // めり込み対策		// 当たり判定
                    float dist;
                    if (player.speed.x >= 0)
                        dist = check(&player, &stage4[i], DIR::RIGHT);
                    else
                        dist = check(&player, &stage4[i], DIR::LEFT);
                    player.pos.x += dist;
                    player.speed.x = 0;
                }
            }

        }
        else
        {
            if (TRG(0) & PAD_L3)
            {
                if (mousePos.x > 550 && mousePos.y > 400 && mousePos.x < 900 && mousePos.y < 460)
                {
                    nextScene = SCENE::RESTART;
                    break;
                }
                else if (mousePos.x > 540 && mousePos.y > 540 && mousePos.x < 910 && mousePos.y < 600)
                {
                    nextScene = SCENE::SELECT;
                    break;
                }
            }

            if (TRG(0) & PAD_START)
            {
                help = 10;
                nextScene = SCENE::ZUKAN;
                break;
            }
        }

        UI = player.elec ? 0 : 105;

        break;
    }
}

void stage4_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(sprStage0, 0, 0);

    // 地形描画
#ifdef _DEBUG
    for (int i = 0; i < STAGE4_MAX; ++i)
    {
        primitive::rect(stage4[i].pos, stage4[i].hsize * 2, stage4[i].hsize, 0, { stage4[i].color.x,stage4[i].color.y,stage4[i].color.z,1 });
    }
#endif
    sprite_render(sprTerrain, 192, 636, 1, 1, 64, 0, 64, 64);
    sprite_render(sprTerrain, 256, 636, 1, 1, 64, 0, 64, 64);
    for (int y = 0; y < 2; ++y)
    {
        for (int x = 0; x < 5; ++x)
        {
            sprite_render(sprTerrain, x * 64, 700 + (y * 64), 1, 1, 64, 0, 64, 64);
        }
    }
    // ドアした
    for (int y = 0; y < 2; ++y)
    {
        for (int x = 0; x < 5; ++x)
        {
            sprite_render(sprTerrain, 1275 + (x * 64), 449 + (y * 64), 1, 1, 64, 0, 64, 64);
        }
    }

    // box
    for (int y = 0; y < 6; ++y)
    {
        sprite_render(sprBox, 710, 384 + (y * 88), 1, 1, 180, 0, 90, 88, 45, 44);
    }

    // 昇降機
    sprite_render(sprSyoukouki, stage4[2].position.x, stage4[2].position.y, 1, 1, stage4[2].elec * 178, 0, 177, 177);
    sprite_render(sprSyoukouki, stage4[3].position.x, stage4[3].position.y, 1, 1, stage4[3].elec * 178, 177, 177, 177);
    sprite_render(sprSyoukouki, stage4[4].position.x, stage4[4].position.y, 1, 1, stage4[4].elec * 178, 0, 177, 177);

    // エレベーター
    sprite_render(sprEV, stage4[1].position.x - 5, stage4[1].position.y - 658);

    // 扉
    sprite_render(sprDoor, stage4[1].position.x, stage4[1].position.y, 1, 1, stage4[1].texPos.x, stage4[1].texPos.y, stage4[1].texSize.x, stage4[1].texSize.y);

    // 電気
    if (Elec.exist)
        sprite_render(sprElec, Elec.pos.x, Elec.pos.y, 1, 1, 0, 0, 128, 128, 64, 64);

    player.Render();

    // playerEv
    if (door.end)
        sprite_render(sprEvPlayer, EvPlayer.x + 35, EvPlayer.y);

    // 扉
    sprite_render(sprDoor, door.position.x, door.position.y, 1, 1, door.texPos.x, 177, door.texSize.x, door.texSize.y);

    // UI
    sprite_render(sprUI, 30, 30, 1, 1, UI, 0, 105, 64);

    // ポーズ画面
    if (pause)
    {
        sprite_render(sprWhite, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprPause, 0, 0);
    }
    sprite_render(sprHelp, 0, 0);

    sprite_render(sprMouse, mousePos.x, mousePos.y, 1, 1, MouseTexPos.x, MouseTexPos.y, 100, 100, 50, 50);
}
