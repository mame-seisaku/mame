#include "all.h"

/*****変数*****/

VECTOR2 speed2;

stage stage2[STAGE2_MAX];

stage door2;    // doa2

Sprite* sprStage2;  // 背景
Sprite* sprSwitch;  // スイッチ
Sprite* sprBoxMove; // 動かせる箱
Sprite* sprDoor2;   // 動くドア

extern stage door;
extern Sprite* sprElec; // 電気
extern Sprite* sprDoor; // ドア
extern Sprite* sprBox;  // 箱

void stage2_init()
{
    stage_state[2] = 0;
}

void stage2_deinit()
{
    player.Dinit();

    safe_delete(sprStage2);
    safe_delete(sprSwitch);
    safe_delete(sprBox);
    safe_delete(sprBoxMove);
    safe_delete(sprDoor2);
    safe_delete(sprEV);
    safe_delete(sprEvPlayer);
    safe_delete(sprMouse);

    safe_delete(sprElec);
    safe_delete(sprDoor);
    safe_delete(sprTerrain);
    safe_delete(sprPause);
    safe_delete(sprWhite);

    music::stop(game_bgm);
}

void stage2_update()
{
    switch (stage_state[2])
    {
    case 0:
        ///// 初期設定 /////
        player.Init();

        sprStage2 = sprite_load(L"./Data/Images/04.png");
        sprSwitch = sprite_load(L"./Data/Images/switch.png");
        sprBox = sprite_load(L"./Data/Images/box.png");
        sprBoxMove = sprite_load(L"./Data/Images/boxMove.png");
        sprDoor2 = sprite_load(L"./Data/Images/door2.png");
        sprEV = sprite_load(L"./Data/Images/EV.png");
        sprEvPlayer = sprite_load(L"./Data/Images/p.png");
        sprMouse = sprite_load(L"./Data/Images/mouse.png");

        sprElec = sprite_load(L"./Data/Images/elec.png");
        sprDoor = sprite_load(L"./Data/Images/door.png");
        sprTerrain = sprite_load(L"./Data/Images/terrain.png");
        sprPause = sprite_load(L"./Data/Images/pause.png");
        sprWhite = sprite_load(L"./Data/Images/white.png");

        ++stage_state[2];
    case 1:
        ///// パラメータの設定 /////

        // ポーズ
        pause = false;

        for (int i = 0; i < STAGE2_MAX; ++i)
        {
            stage2[i] = {};
        }

        // type
        // 1 動くbox
        // 2 扉
        // 3 動く床
        // 4 邪魔な壁
        // 5 赤スイッチ
        // 6 player2
        // 7 continue
        // 8 青スイッチ
        // 9

        // 床
        stage2[0].pos = { 768,764 };
        stage2[0].hsize = { 768,64 };
        stage2[0].type = 0;
        stage2[0].exist = true;

        // 扉
        stage2[1].position = { 1315,274 };
        stage2[1].pos = { 1405,360 };
        stage2[1].hsize = { 80, 89 };
        stage2[1].texPos = {};
        stage2[1].texSize = { 178,177 };
        stage2[1].type = 2;
        stage2[1].exist = true;
        stage2[1].open = false;

        // 右壁
        stage2[2].pos = { 1377,575 };
        stage2[2].hsize = { 154,130 };
        stage2[2].type = 7;
        stage2[2].exist = true;

        // 右のbox右
        stage2[3].pos = { 1170,654 };
        stage2[3].position = { stage2[3].pos.x - 44,stage2[3].pos.y - 44 };
        stage2[3].texPos.x = 180;
        stage2[3].hsize = { 44,44 };
        stage2[3].type = 1;
        stage2[3].exist = true;

        // 右のbox左
        stage2[4].pos = { 1076,654 };
        stage2[4].position = { stage2[4].pos.x - 44,stage2[4].pos.y - 44 };
        stage2[4].texPos.x = 180;
        stage2[4].hsize = { 44,44 };
        stage2[4].type = 1;
        stage2[4].exist = true;

        // 左のbox
        stage2[5].pos = { 230,652 };
        stage2[5].position = { stage2[5].pos.x - 44,stage2[5].pos.y - 44 };
        stage2[5].texPos.x = 90;
        stage2[5].hsize = { 44,44 };
        stage2[5].type = 1;
        stage2[5].exist = true;

        // 左上のbox
        stage2[6].pos = { 616,188 };
        stage2[6].position = { stage2[6].pos.x - 44,stage2[6].pos.y - 60 };
        stage2[6].texPos.x = 90;
        stage2[6].hsize = { 44,44 };
        stage2[6].type = 1;
        stage2[6].exist = true;

        // 右上のbox
        stage2[7].pos = { 935,188 };
        stage2[7].position = { stage2[7].pos.x - 44,stage2[7].pos.y - 54 };
        stage2[7].texPos.x = 90;
        stage2[7].hsize = { 44,44 };
        stage2[7].type = 1;
        stage2[7].exist = true;

        // 真ん中のデカbox
        stage2[8].position = { 530,523 };
        stage2[8].pos = { 619,612.5f };
        stage2[8].hsize = { 89, 88.5f };
        stage2[8].type = 7;
        stage2[8].exist = true;

        // 真ん中の床
        stage2[9].pos = { 800,260 };
        stage2[9].hsize = { 250,25 };
        stage2[9].type = 0;
        stage2[9].exist = true;

        // かけはし
        stage2[10].pos = { 410,260 };
        stage2[10].hsize = { 110,25 };
        stage2[10].type = 3;
        stage2[10].exist = false;
        stage2[10].color = { 1,0,0,1 };

        // 真ん中の床左
        stage2[11].pos = { 220,260 };
        stage2[11].hsize = { 50,25 };
        stage2[11].type = 9;
        stage2[11].exist = true;

        // 左上床
        stage2[12].pos = { 110,392 };
        stage2[12].hsize = { 120,30 };
        stage2[12].type = 9;
        stage2[12].exist = true;

        // 邪魔な壁
        stage2[13].pos = { 838,103 };
        stage2[13].hsize = { 32,100 };
        stage2[13].type = 4;
        stage2[13].exist = true;
        stage2[13].color.w = 1;

        // 赤スイッチ
        stage2[14].pos = { 830,686 };
        stage2[14].hsize = { 20,10 };
        stage2[14].type = 5;
        stage2[14].exist = true;

        // 青スイッチ
        stage2[15].pos = { 90,350 };
        stage2[15].hsize = { 20,10 };
        stage2[15].type = 8;
        stage2[15].exist = true;

        // たて
        //stage2[16].pos = { 200,320 };
        //stage2[16].hsize = { 25,80 };
        //stage2[16].type = 9;
        //stage2[16].exist = true;

        // 邪魔な壁
        stage2[17].pos = { 1028,103 };
        stage2[17].hsize = { 32,100 };
        stage2[17].type = 4;
        stage2[17].exist = true;
        stage2[17].color.w = 1;

        // EvPlayer
        EvPlayer = { stage2[1].position.x, stage2[1].position.y + 100 };

        // 動くドア
        door2 = {};
        door2.texSize = { 128,64 };

        // ドア最後
        door = {};

        // 電気
        Elec = {};

        // 
        speed2 = {};

        MouseTexPos = {};

        // BGM
        music::play(game_bgm, true);

        ++stage_state[2];
    case 2:
        ///// 通常時 /////

#ifdef _DEBUG
        debug::setString("player.pos.x:%f", player.pos.x);
        debug::setString("player.pos.y:%f", player.pos.y);
        debug::setString("player.speed.x:%f", player.speed.x);
        debug::setString("player.speed.y:%f", player.speed.y);
#endif // DEBUG


        // シーン切り替え
        if (door.end)
        {
            player.pos.y = EvPlayer.y - 45;
            EvPlayer.y -= STAGE_MOVE;
        }
        if (EvPlayer.y < -200)
        {
            if (PossibleStage < 3)PossibleStage = 3;
            nextScene = SCENE::RESULT;
            break;
        }

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
            // プレイヤー更新
            player.Update({100,500});

#ifdef _DEBUG
            oss << "(x=" << point.x << " y=" << point.y << ")";
            SetWindowTextA(window::getHwnd(), oss.str().c_str());   // タイトルバーにを表示させる
            debug::setString("mousePos.x:%f,mousePos.y:%f", mousePos.x, mousePos.y);
            debug::setString("stage2[6].pos.x:%f", stage2[5].pos.x);
            debug::setString("stage2[6].pos.y:%f", stage2[5].pos.y);
#endif
            
            for (int i = 5; i < 8; ++i)
            {
                if (stage2[i].pos.x - stage2[i].hsize.x < 0)stage2[i].pos.x = stage2[i].hsize.x;
            }

            //// マウスでの憑依操作
            //if (mousePos.x > stage2[16].pos.x - 50 && mousePos.y > stage2[16].pos.y - 42 && mousePos.x < stage2[16].pos.x + 50 && mousePos.y < stage2[16].pos.y + 42)
            //{
            //    // 電気を飛ばす
            //    if (TRG(0) & PAD_L3)
            //    {
            //        // プレイヤーに電気があれば
            //        if (!Elec.exist && player.elec)
            //        {
            //            SetElecMove();
            //            Elec.type = 16;
            //        }
            //    }
            //    // 電気回収
            //    if (TRG(0) & PAD_R3 && !player.elec)
            //    {
            //        Elec.exist = false;
            //        Elec.type = 16;
            //        stage2[16].elec = false;
            //        player.elec = true;
            //    }
            //}
            
            if (mousePos.x > stage2[5].pos.x - 42 && mousePos.y > stage2[5].pos.y - 42 && mousePos.x < stage2[5].pos.x + 42 && mousePos.y < stage2[5].pos.y + 42||
                mousePos.x > stage2[6].pos.x - 42 && mousePos.y > stage2[6].pos.y - 42 && mousePos.x < stage2[6].pos.x + 42 && mousePos.y < stage2[6].pos.y + 42||
                mousePos.x > stage2[7].pos.x - 42 && mousePos.y > stage2[7].pos.y - 42 && mousePos.x < stage2[7].pos.x + 42 && mousePos.y < stage2[7].pos.y + 42)
            {
                MouseTexPos.x = 100;
            }
            else
            {
                MouseTexPos.x = 0;
            }
            
            // 動くbox
            for (int i = 5; i < 8; ++i)
            {
                if (mousePos.x > stage2[i].pos.x - 42 && mousePos.y > stage2[i].pos.y - 42 && mousePos.x < stage2[i].pos.x + 42 && mousePos.y < stage2[i].pos.y + 42)
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
                        // 電気入ってるか
                        for (int j = 5; j < 8; ++j)
                        {
                            if (i == j)continue;

                            stage2[j].elec = false;
                        }

                        Elec.exist = false;
                        Elec.type = i;
                        stage2[i].elec = false;
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
                            stage2[Elec.type].elec = true;
                        }
                    }
                    else
                    {
                        // 当たった
                        if (Elec.pos.x >= ElecPos.x)
                        {
                            player.elec = false;    // プレイヤーの電気消す
                            Elec.exist = false;
                            stage2[Elec.type].elec = true;
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
                            stage2[Elec.type].elec = true;
                        }
                    }
                    else
                    {
                        // 当たった
                        if (Elec.pos.x <= ElecPos.x)
                        {
                            player.elec = false;    // プレイヤーの電気消す
                            Elec.exist = false;
                            stage2[Elec.type].elec = true;
                        }
                    }
                }
            }

            // 憑依物の移動
            if (STATE(0) & PAD_LEFT)
            {
                if (!(STATE(0) & PAD_RIGHT))
                {
                    speed2.x = -5;
                }
            }
            else if (STATE(0) & PAD_RIGHT)
            {
                if (!(STATE(0) & PAD_LEFT))
                {
                    speed2.x = 5;
                }
            }
            else
            {
                speed2.x = 0;
            }


            // かけはし
            if (door2.open)anime(&door2, 10, 10, false, 0);
            if (door2.end)stage2[10].exist = true;


            // 扉アニメ
            if (stage2[1].open)
                anime(&stage2[1], 7, 10, false, 0);

            // クリア判定
            if (stage2[1].end && stage2[1].one && !door.close)
            {
                player.clear = true;
                door = stage2[1];
                door.state = 0;
                door.close = true;
            }

            if (player.clear)
            {
                player.pos.x = stage2[1].position.x + 71;    // ドアの位置に移動
                // 電気を戻す
                player.elec = true;
                for (int i = 0; i < STAGE2_MAX; ++i)
                {
                    stage2[i].elec = false;
                }

                // 扉しまる
                anime(&door, 7, 10, false, 0);
            }

            // マウスでの憑依操作

            // 電気の移動と、当たったか判定

            // 位置にスピードを足す
            player.pos.y += player.speed.y;

            // 重力
            speed2.y += 1.0f;
            //if (speed2.y > 10.0f)speed2.y = 10.0f;
            
            for (int i = 5; i < 8; ++i)
            {
                stage2[i].pos.y += 12;
            }


            // 上下のめりこみチェック
            for (int i = 0; i < STAGE2_MAX; ++i)
            {
                for (int j = 5; j < 8; ++j)
                {
                    if (hitCheck(&stage2[j], &stage2[i]))
                    {
                        if (i == j)continue;
                        if (i >= 5 && i < 8)continue;

                        if (stage2[i].type == 2)continue;   // 扉
                        if (stage2[i].type == 3 && !stage2[i].exist)continue;   // かけはし
                        if (stage2[i].type == 4)continue;   // 青壁
                        if (stage2[i].type == 5)continue;   // 赤スイッチ
                        if (stage2[i].type == 7)continue;   // 関係ない
                        
                        if (stage2[i].type == 8)    // 青スイッチ
                        {
                            stage2[i].texPos.x = 64;
                            stage2[13].exist = false;
                            stage2[17].exist = false;
                            continue;
                        }

                        // めり込み対策		// 当たり判定
                        float dist;
                        if (speed2.y >= 0)
                            dist = check(&stage2[j], &stage2[i], DIR::DOWN);
                        else
                            dist = check(&stage2[j], &stage2[i], DIR::UP);
                        stage2[j].pos.y += dist;
                        speed2.y = 0;
                    }
                }

                if (hitCheck(&player, &stage2[i]))
                {
                    // 扉
                    if (stage2[i].type == 2)
                    {
                        stage2[i].open = true;
                        continue;
                    }

                    // kakehasi
                    if (stage2[i].type == 3)
                    {
                        if (!door2.open)continue;   // 
                    }

                    // スイッチ
                    if (stage2[i].type == 5)
                    {
                        if (i == 14)door2.open = true;
                        stage2[i].texPos.x = 64;
                        continue;
                    }

                    if (stage2[i].type == 9)// 関係ない
                    {
                        player.speed.y = -0.1;
                    }

                    // めり込み対策		// 当たり判定
                    float dist;
                    if (player.speed.y >= 0)
                        dist = check(&player, &stage2[i], DIR::DOWN);
                    else
                        dist = check(&player, &stage2[i], DIR::UP);
                    player.pos.y += dist;
                    player.speed.y = 0;
                }
            }

            // x
            for (int i = 5; i < 8; ++i)
            {
                if (stage2[i].elec)
                {
                    stage2[i].pos.x += speed2.x;
                }
            }

            // 位置にスピードを足す         
            player.pos.x += player.speed.x;

            // 左右のめり込みチェック
            for (int i = 0; i < STAGE2_MAX; ++i)
            {
                for (int j = 5; j < 8; ++j)
                {
                    if (hitCheck(&stage2[j], &stage2[i]))
                    {
                        if (i == j)continue;

                        if (stage2[i].type == 2)continue;   // 扉
                        if (stage2[i].type == 3 && !stage2[i].exist)continue;   // かけはし
                        if (stage2[i].type == 4 && !stage2[i].exist)continue;   // 青壁
                        if (stage2[i].type == 5)continue;   // 赤スイッチ
                        if (stage2[i].type == 8)    // 青スイッチ
                        {
                            stage2[i].texPos.x = 64;
                            stage2[13].exist = false;
                            stage2[17].exist = false;
                            continue;
                        }

                        // めり込み対策		// 当たり判定
                        float dist;
                        if (speed2.x >= 0)
                            dist = check(&stage2[j], &stage2[i], DIR::RIGHT);
                        else
                            dist = check(&stage2[j], &stage2[i], DIR::LEFT);
                        stage2[j].pos.x += dist;
                        speed2.x = 0;
                    }
                }

                if (hitCheck(&player, &stage2[i]))
                {
                    // 扉
                    if (stage2[i].type == 2)
                    {
                        stage2[i].open = true;
                        continue;
                    }

                    // kakehasi
                    if (stage2[i].type == 3)
                    {
                        if (!door2.open)continue;   // 
                    }

                    // スイッチ
                    if (stage2[i].type == 5)
                    {
                        if (i == 14)door2.open = true;
                        stage2[i].texPos.x = 64;
                        continue;
                    }

                    if (stage2[i].type == 9)continue;   // 関係ない

                    // めり込み対策		// 当たり判定
                    float dist;
                    if (player.speed.x >= 0)
                        dist = check(&player, &stage2[i], DIR::RIGHT);
                    else
                        dist = check(&player, &stage2[i], DIR::LEFT);
                    player.pos.x += dist;
                    player.speed.x = 0;
                }
            }

            for (int i = 5; i < 8; ++i)
            {
                stage2[i].texPos.x = stage2[i].elec ? 0 : 90;
            }


            if (!stage2[13].exist)++stage2[13].timer; // 点滅用タイマー
            if (stage2[13].timer / 10 == 1 && stage2[13].counter < 7)
            {
                stage2[13].color.w = stage2[13].color.w == 0 ? 1 : 0;
                stage2[17].color.w = stage2[17].color.w == 0 ? 1 : 0;

                ++stage2[13].counter;
                stage2[13].timer = 0;
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
        }

        break;
    }
}

void stage2_render()
{
    GameLib::clear(1, 1, 1);

    // 背景
    sprite_render(sprStage2, 0, 0);

    // 地形描画
#ifdef _DEBUG
    for (int i = 0; i < STAGE2_MAX; ++i)
    {
        primitive::rect(stage2[i].pos, stage2[i].hsize * 2, stage2[i].hsize, 0, { stage2[i].color.x,stage2[i].color.y,stage2[i].color.z,1 });
    }
#endif
    // 床
    for (int y = 0; y < 2; ++y)
    {
        for (int x = 0; x < 24; ++x)
        {
            sprite_render(sprTerrain, 64 * x, 635 + (64 * (y + 1)), 1, 1, 64, 0, 64, 64);
        }
    }
    // 右床集まり
    for (int y = 0; y < 4; ++y)
    {
        for (int x = 0; x < 5; ++x)
        {
            sprite_render(sprTerrain, 1216+(64*x), 379 + (64 * (y + 1)), 1, 1, 64, 0, 64, 64);
        }
    }
    // 真ん中床
    for (int x = 0; x < 8; ++x)
    {
        sprite_render(sprTerrain, 550 + (64 * x), 234, 1, 1, 64, 0, 64, 64);
    }
    //// 真ん中かけはし
    //for (int x = 0; x < 4; ++x)
    //{
    //    sprite_render(sprTerrain, 294 + (64 * x), 234, 1, 1, 128, 0, 64, 64, 0, 0, 0, 1, 1, 1, 0.3f);
    //}
    sprite_render(sprTerrain, 230, 234, 1, 1, 64, 0, 64, 64);
    sprite_render(sprTerrain, 166, 234, 1, 1, 64, 0, 64, 64);
    sprite_render(sprTerrain, 166, 298, 1, 1, 64, 0, 64, 64);
    // 真ん中左床
    for (int x = 0; x < 4; ++x)
    {
        sprite_render(sprTerrain, -26 + (64 * x), 362, 1, 1, 0, 0, 64, 64);
    }
    // 邪魔な壁
    for (int y = 0; y < 4; ++y)
    {
        sprite_render(sprTerrain, 806, -22 + (64 * y), 1, 1, 128, 0, 64, 64, 0, 0, 0, 1, 1, 1, stage2[13].color.w);
        sprite_render(sprTerrain, 998, -22 + (64 * y), 1, 1, 128, 0, 64, 64, 0, 0, 0, 1, 1, 1, stage2[17].color.w);
    }

    // スイッチ
    sprite_render(sprSwitch, 800, 635, 1, 1, stage2[14].texPos.x, 0, 64, 64);
    sprite_render(sprSwitch, 60, 298, 1, 1, stage2[15].texPos.x, 64, 64, 64);

    // 動く箱
    for (int i = 3; i < 8; ++i)
    {
        sprite_render(sprBoxMove, stage2[i].pos.x-46, stage2[i].pos.y-46, 1, 1, stage2[i].texPos.x, 0, 90, 90);
    }
    
    // デカ箱
    sprite_render(sprBox, stage2[8].position.x, stage2[8].position.y);

    // 動く扉
    sprite_render(sprDoor2, 290, 235, 1, 1, door2.texPos.x, 0, 128, 64);
    sprite_render(sprDoor2, 550, 235, -1, 1, door2.texPos.x, 0, 128, 64);

    // エレベーター
    sprite_render(sprEV, stage2[1].position.x - 5, stage2[1].position.y - 653);

    // 扉
    sprite_render(sprDoor, stage2[1].position.x, stage2[1].position.y, 1, 1, stage2[1].texPos.x, stage2[1].texPos.y, stage2[1].texSize.x, stage2[1].texSize.y);

    // 電気
    if (Elec.exist)
        sprite_render(sprElec, Elec.pos.x, Elec.pos.y, 1, 1, 0, 0, 128, 128, 64, 64);

    // player2
    //sprite_render(sprPlayer2, stage2[16].pos.x, stage2[16].pos.y, 1, 1, 0, 0, stage2[16].texSize.x, stage2[16].texSize.y, stage2[16].pivot.x, stage2[16].pivot.y);

    player.Render();
    //primitive::rect(player.pos, player.hsize * 2, player.hsize, 0, { 0,0,1,1 });

    // playerEv
    if (door.end)
        sprite_render(sprEvPlayer, EvPlayer.x + 35, EvPlayer.y);

    // 扉
    sprite_render(sprDoor, door.position.x, door.position.y, 1, 1, door.texPos.x, 177, door.texSize.x, door.texSize.y);

    // ポーズ画面
    if (pause)
    {
        sprite_render(sprWhite, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprPause, 0, 0);
    }

    // マウスカーソル
    sprite_render(sprMouse, mousePos.x, mousePos.y, 1, 1, MouseTexPos.x, MouseTexPos.y, 100, 100, 50, 50);
}
