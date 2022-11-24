#include "all.h"
/*****変数*****/

stage stage3[STAGE3_MAX];

VECTOR2 speed3;

Sprite* spr3;
Sprite* sprSyoukouki; // 昇降機
extern Sprite* sprBox; 

extern VECTOR2 mousePos;
extern stage door;

extern Sprite* sprElec; // 電気
extern Sprite* sprDoor; // ドア


void stage3_init()
{
	stage_state[3] = 0;
}

void stage3_deinit()
{
    player.Dinit();

	safe_delete(spr3);
	safe_delete(sprSyoukouki);
    safe_delete(sprUI);
    safe_delete(sprEV);
    safe_delete(sprEvPlayer);
    safe_delete(sprMouse);
    safe_delete(sprBox);
    safe_delete(sprTerrain);
    safe_delete(sprPause);
    safe_delete(sprWhite);
    safe_delete(sprHelp);

    music::stop(game_bgm);
}

void stage3_update()
{
    switch (stage_state[3])
    {
    case 0:
        ///// 初期設定 /////
        player.Init();

        spr3 = sprite_load(L"./Data/Images/05.png");
        sprSyoukouki = sprite_load(L"./Data/Images/syoukouki2.png");

        sprBox = sprite_load(L"./Data/Images/box.png");

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

        ++stage_state[3];
    case 1:
        ///// パラメータの設定 /////

        // ポーズ
        pause = false;

        for (int i = 0; i < STAGE1_MAX; ++i)
        {
            stage3[i] = {};
        }

        // type 
        // 0 kabe
        // 2 扉

        // 床
        stage3[0].pos = { 768,764 };
        stage3[0].hsize = { 768, 64 };
        stage3[0].type = 0;
        stage3[0].exist = true;
        // 左壁
        //stage3[1].pos = { 5,412 };
        //stage3[1].hsize = { 5,412 };
        //stage3[1].type = 0;
        //stage3[1].exist = true;
        // 右壁
        stage3[2].pos = { 1531,412 };
        stage3[2].hsize = { 15,412 };
        stage3[2].type = 0;
        stage3[2].exist = true;
        //昇降機
        stage3[3].position = { 890,510 };
        stage3[3].pos = { 979,650 };
        stage3[3].hsize = { 89, 50 };
        stage3[3].type = 0;
        stage3[3].exist = true;

        // 扉
        stage3[4].position = { 1239,230 };
        stage3[4].pos = { 1330,320 };
        stage3[4].hsize = { 80, 89 };
        stage3[4].texPos = {};
        stage3[4].texSize = { 178,177 };
        stage3[4].type = 2;
        stage3[4].exist = true;
        stage3[4].open = false;

        // 高台
        stage3[5].pos = { 1340,550 };
        stage3[5].hsize = { 180, 150 };
        stage3[5].type = 0;
        stage3[5].exist = true;

        // 真ん中のデカbox
        stage3[6].position = { 480,523 };
        stage3[6].pos = { 569,612.5f };
        stage3[6].hsize = { 89, 88.5f };
        stage3[6].type = 7;
        stage3[6].exist = true;

        //昇降機2
        stage3[7].position = { 240,210 };
        stage3[7].pos = { 329,350 };
        stage3[7].hsize = { 89, 50 };
        stage3[7].type = 0;
        stage3[7].exist = true;

        // EvPlayer
        EvPlayer = { stage3[4].position.x, stage3[4].position.y + 100 };

        // ドア最後
        door = {};

        // 電気
        Elec = {};

        music::play(game_bgm, true);

        ++stage_state[3];
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
            if (PossibleStage < 4)PossibleStage = 4;
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

        // マウスカーソル
        std::ostringstream oss;                                 // 文字列ストリーム
        POINT point;                                            // 位置用の変数を宣言する
        GetCursorPos(&point);                                   // スクリーン座標を取得する
        ScreenToClient(window::getHwnd(), &point);              // クライアント座標に変換する
        mousePos.x = (float)(point.x);
        mousePos.y = (float)(point.y);

        if (!pause)
        {
            player.Update({100,200});

#ifdef _DEBUG
            oss << "(x=" << point.x << " y=" << point.y << ")";
            SetWindowTextA(window::getHwnd(), oss.str().c_str());   // タイトルバーにを表示させる
            debug::setString("PossibleStage:%d", PossibleStage);
            debug::setString("stage3[3].pos.x:%f", stage3[3].pos.x);
            debug::setString("stage3[3].pos.y:%f", stage3[3].pos.y);
            debug::setString("stage3[7].pos.x:%f", stage3[7].pos.x);
            debug::setString("stage3[7].pos.y:%f", stage3[7].pos.y);
#endif
            // 扉アニメ
            if (stage3[4].open)
                anime(&stage3[4], 7, 10, false, 0);

            // クリア判定
            if (stage3[4].end && stage3[4].one && !door.close)
            {
                player.clear = true;
                door = stage3[4];
                door.state = 0;
                door.close = true;
            }

            if (player.clear)
            {
                player.pos.x = stage3[4].position.x + 71;    // ドアの位置に移動
                // 電気を戻す
                player.elec = true;
                for (int i = 0; i < STAGE0_MAX; ++i)
                {
                    stage3[i].elec = false;
                }

                // 扉しまる
                anime(&door, 7, 10, false, 0);
            }

            if (mousePos.x > stage3[3].pos.x - 90 && mousePos.y > stage3[3].pos.y - 50 && mousePos.x < stage3[3].pos.x + 90 && mousePos.y < stage3[3].pos.y + 50||
                mousePos.x > stage3[7].pos.x - 90 && mousePos.y > stage3[7].pos.y - 50 && mousePos.x < stage3[7].pos.x + 90 && mousePos.y < stage3[7].pos.y + 50)
            {
                MouseTexPos.x = 100;
            }
            else
            {
                MouseTexPos.x = 0;
            }


            // マウスでの憑依操作
            //昇降機1
            if (mousePos.x > stage3[3].pos.x - 90 && mousePos.y > stage3[3].pos.y - 50 && mousePos.x < stage3[3].pos.x + 90 && mousePos.y < stage3[3].pos.y + 50)
            {
                if (TRG(0) & PAD_L3)
                {
                    if (!Elec.exist && player.elec)
                    {
                        SetElecMove();
                        Elec.type = 3;
                    }
                }
            }
            //昇降機2
            if (mousePos.x > stage3[7].pos.x - 90 && mousePos.y > stage3[7].pos.y - 50 && mousePos.x < stage3[7].pos.x + 90 && mousePos.y < stage3[7].pos.y + 50)
            {
                if (TRG(0) & PAD_L3)
                {
                    if (!Elec.exist && player.elec)
                    {
                        SetElecMove();
                        Elec.type = 7;
                    }
                }
            }
            if (TRG(0) & PAD_R3 && !player.elec)
            {
                stage3[3].elec = false;
                stage3[7].elec = false;
                player.elec = true;
            }


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
                            stage3[Elec.type].elec = true;
                           
                        }
                    }
                    else
                    {
                        // 当たった
                        if (Elec.pos.x >= ElecPos.x)
                        {
                            player.elec = false;    // プレイヤーの電気消す
                            Elec.exist = false;
                            stage3[Elec.type].elec = true;
                            
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
                            stage3[Elec.type].elec = true;
                            
                        }
                    }
                    else
                    {
                        // 当たった
                        if (Elec.pos.x <= ElecPos.x)
                        {
                            player.elec = false;    // プレイヤーの電気消す
                            Elec.exist = false;
                            stage3[Elec.type].elec = true;
                            
                        }
                    }
                }
            }


            if (STATE(0) & PAD_UP)
            {
                if (!(STATE(0) & PAD_DOWN))
                {
                    speed3.y = -PLAYER_MOVE;
                }
            }
            else if (STATE(0) & PAD_DOWN)
            {
                if (!(STATE(0) & PAD_UP))
                {
                    speed3.y = PLAYER_MOVE;
                }
            }
            else
            {
                speed3.y = 0;
            }



            player.pos.y += player.speed.y;
            /* stage3[3].position.y = stage3[3].pos.y-140;*/
            //昇降機1 移動
            if (stage3[3].elec == true) {
                stage3[3].pos.y += speed3.y;
                stage3[3].position.y = stage3[3].pos.y - 140;
            }
            //昇降機2 移動
            if (stage3[7].elec == true) {
                stage3[7].pos.y += speed3.y;
                stage3[7].position.y = stage3[7].pos.y - 140;
            }

            // 上下のめり込みチェック
            for (int i = 0; i < STAGE3_MAX; ++i)
            {
                if (hitCheck(&player, &stage3[i]))
                {
                    // 扉
                    if (stage3[i].type == 2)
                    {
                        stage3[i].open = true;
                        continue;
                    }


                    // めり込み対策		// 当たり判定
                    float dist;
                    if (player.speed.y >= 0)
                        dist = check(&player, &stage3[i], DIR::DOWN);
                    else
                        dist = check(&player, &stage3[i], DIR::UP);
                    player.pos.y += dist;
                    player.speed.y = 0;
                    
                }
                //昇降機1
                if (hitCheck(&stage3[3], &stage3[0]))
                {
                    float dist;
                    if (speed3.y >= 0)
                        dist = check(&stage3[3], &stage3[0], DIR::DOWN);
                    else
                        dist = check(&stage3[3], &stage3[0], DIR::UP);
                    stage3[3].pos.y += dist;
                    speed3.y = 0;
                    stage3[3].position.y += dist;
                }
                //昇降機2
                if (hitCheck(&stage3[7], &stage3[0]))
                {
                    float dist;
                    if (speed3.y >= 0)
                        dist = check(&stage3[7], &stage3[0], DIR::DOWN);
                    else
                        dist = check(&stage3[7], &stage3[0], DIR::UP);
                    stage3[7].pos.y += dist;
                    speed3.y = 0;
                    stage3[7].position.y += dist;
                }
               
            }

            //上 上限
            //昇降機1
            if (stage3[3].pos.y < 200) {
                stage3[3].pos.y = 200;
                stage3[3].position.y = 60;
            }
            //昇降機2
            if (stage3[7].pos.y < 200) {
                stage3[7].pos.y = 200;
                stage3[7].position.y = 60;
            }


            //操作切り替え
            player.pos.x += player.speed.x;


            // 左右のめり込みチェック
            for (int i = 0; i < STAGE3_MAX; ++i)
            {
                if (player.elec == true) {
                    if (hitCheck(&player, &stage3[i]))
                    {
                        // 扉
                        if (stage3[i].type == 2)
                        {
                            stage3[i].open = true;
                            continue;
                        }

                        // めり込み対策		// 当たり判定
                        float dist;
                        if (player.speed.x >= 0)
                            dist = check(&player, &stage3[i], DIR::RIGHT);
                        else
                            dist = check(&player, &stage3[i], DIR::LEFT);
                        player.pos.x += dist;
                        player.speed.x = 0;
                    }
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
                help = 9;
                nextScene = SCENE::ZUKAN;
                break;
            }
        }

        UI = player.elec ? 0 : 105;

        break;
    }
}

void stage3_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(spr3, 0, 0);

    // 地形描画
   /* for (int i = 0; i < STAGE1_MAX; ++i)
    {
        primitive::rect(stage3[i].pos, stage3[i].hsize * 2, stage3[i].hsize, 0, { 1,0,0,1 });
    }*/
    //床
    for (int y = 0; y < 2; ++y)
    {
        for (int x = 0; x < 24; ++x)
        {
            sprite_render(sprTerrain, x * 64, 700 + (y * 64), 1, 1, 64, 0, 64, 64);
        }
    }
    
    //高台
    for (int y = 0; y < 7; ++y)
    {
        for (int x = 0; x < 6; ++x)
        {
            sprite_render(sprTerrain, 1152 + (x * 64), 400 + (y * 64), 1, 1, 64, 0, 64, 64);
        }
    }


    // 昇降機
    sprite_render(sprSyoukouki, stage3[3].position.x, stage3[3].position.y, 1, 1, stage3[3].elec * 178, 0, 177, 177);
    // 昇降機2
    sprite_render(sprSyoukouki, stage3[7].position.x, stage3[7].position.y, 1, 1, stage3[7].elec * 178, 0, 177, 177);
    
    // エレベーター
    sprite_render(sprEV, stage3[4].position.x - 5, stage3[4].position.y - 653);

    
    // デカ箱
    sprite_render(sprBox, stage3[6].position.x, stage3[6].position.y);

    // 扉
    sprite_render(sprDoor, stage3[4].position.x, stage3[4].position.y, 1, 1, stage3[4].texPos.x, stage3[4].texPos.y, stage3[4].texSize.x, stage3[4].texSize.y);

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
