#include "all.h"
/*****変数*****/

stage stage3[STAGE3_MAX];

VECTOR2 speed3;

Sprite* spr3;
Sprite* sprSyoukouki3;


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
	safe_delete(sprSyoukouki3);
    safe_delete(sprEV);
    safe_delete(sprEvPlayer);
    safe_delete(sprMouse);

    safe_delete(sprTerrain);

    safe_delete(sprPause);

    music::stop(game_bgm);
}

void stage3_update()
{
    switch (stage_state[3])
    {
    case 0:
        ///// 初期設定 /////
        player.Init();

        spr3 = sprite_load(L"./Data/Images/04.png");
        sprSyoukouki3 = sprite_load(L"./Data/Images/syoukouki2.png");

        sprElec = sprite_load(L"./Data/Images/elec.png");
        sprDoor = sprite_load(L"./Data/Images/door.png");
        sprEV = sprite_load(L"./Data/Images/EV.png");
        sprEvPlayer = sprite_load(L"./Data/Images/p.png");
        sprMouse = sprite_load(L"./Data/Images/mouse.png");

        sprTerrain = sprite_load(L"./Data/Images/terrain.png");

        sprPause = sprite_load(L"./Data/Images/pause.png");

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
        //エレベータ
        stage3[3].position = { 890,510 };
        stage3[3].pos = { 979,650 };
        stage3[3].hsize = { 89, 50 };
        stage3[3].type = 0;
        stage3[3].exist = true;

        // 扉
        stage3[4].position = { 1239,530 };
        stage3[4].pos = { 1330,620 };
        stage3[4].hsize = { 80, 89 };
        stage3[4].texPos = {};
        stage3[4].texSize = { 178,177 };
        stage3[4].type = 2;
        stage3[4].exist = true;
        stage3[4].open = false;

        // EvPlayer
        EvPlayer = { stage3[4].position.x, stage3[4].position.y };

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
            EvPlayer.y -= 10;
        }
        if (EvPlayer.y < -200)
        {
            PossibleStage = 4;
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
            std::ostringstream oss;                                 // 文字列ストリーム
            POINT point;                                            // 位置用の変数を宣言する
            GetCursorPos(&point);                                   // スクリーン座標を取得する
            ScreenToClient(window::getHwnd(), &point);              // クライアント座標に変換する
            mousePos.x = (float)(point.x);
            mousePos.y = (float)(point.y);
            oss << "(x=" << point.x << " y=" << point.y << ")";
            SetWindowTextA(window::getHwnd(), oss.str().c_str());   // タイトルバーにを表示させる
            debug::setString("PossibleStage:%d", PossibleStage);
            debug::setString("stage3[3].pos.x:%f", stage3[3].pos.x);
            debug::setString("stage3[3].pos.y:%f", stage3[3].pos.y);
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
                player.pos.x = stage3[4].position.x + 51;    // ドアの位置に移動
                // 電気を戻す
                player.elec = true;
                for (int i = 0; i < STAGE0_MAX; ++i)
                {
                    stage3[i].elec = false;
                }

                // 扉しまる
                anime(&door, 7, 10, false, 0);
            }


            // マウスでの憑依操作
            if (mousePos.x > stage3[3].pos.x - 90 && mousePos.y > stage3[3].pos.y - 50 && mousePos.x < stage3[3].pos.x + 90 && mousePos.y < stage3[3].pos.y + 50)
            {
                if (TRG(0) & PAD_L3)
                {
                    if (!Elec.exist && player.elec)
                    {
                        SetElecMove();
                        Elec.type = stage3[3].type;
                    }
                }
            }
            if (TRG(0) & PAD_R3 && !player.elec)
            {
                stage3[3].elec = false;
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
                            stage3[3].elec = true;
                        }
                    }
                    else
                    {
                        // 当たった
                        if (Elec.pos.x >= ElecPos.x)
                        {
                            player.elec = false;    // プレイヤーの電気消す
                            Elec.exist = false;
                            stage3[3].elec = true;
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
                            stage3[3].elec = true;
                        }
                    }
                    else
                    {
                        // 当たった
                        if (Elec.pos.x <= ElecPos.x)
                        {
                            player.elec = false;    // プレイヤーの電気消す
                            Elec.exist = false;
                            stage3[3].elec = true;
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
            if (stage3[3].elec == true) {
                stage3[3].pos.y += speed3.y;
                stage3[3].position.y = stage3[3].pos.y - 140;
            }

            // 上下のめり込みチェック
            for (int i = 0; i < STAGE0_MAX; ++i)
            {
                if (hitCheck(&player, &stage3[i]))
                {
                    // 扉
                    if (stage3[i].type == 2)
                    {
                        stage3[i].open = true;
                        break;
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
            }

            //上 上限
            if (stage3[3].pos.y < 200) {
                stage3[3].pos.y = 200;
                stage3[3].position.y = 60;
            }

            //操作切り替え
            player.pos.x += player.speed.x;


            // 左右のめり込みチェック
            for (int i = 0; i < STAGE0_MAX; ++i)
            {
                if (player.elec == true) {
                    if (hitCheck(&player, &stage3[i]))
                    {
                        // 扉
                        if (stage3[i].type == 2)
                        {
                            stage3[i].open = true;
                            break;
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
            break;
        }
    }
}

void stage3_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(spr3, 0, 0);

    // 地形描画
    for (int i = 0; i < STAGE1_MAX; ++i)
    {
        primitive::rect(stage3[i].pos, stage3[i].hsize * 2, stage3[i].hsize, 0, { 1,0,0,1 });
    }
    for (int y = 0; y < 2; ++y)
    {
        for (int x = 0; x < 24; ++x)
        {
            sprite_render(sprTerrain, x * 64, 700 + (y * 64), 1, 1, 64, 0, 64, 64);
        }
    }

    // エレベータ
    sprite_render(sprSyoukouki3, stage3[3].position.x, stage3[3].position.y, 1, 1, stage3[3].elec * 178, 0, 177, 177);

    // エレベーター
    sprite_render(sprEV, stage3[4].position.x - 5, stage3[4].position.y - 650);

    // playerEv
    if (door.end)
        sprite_render(sprEvPlayer, EvPlayer.x - 5, EvPlayer.y);

    // 扉
    sprite_render(sprDoor, stage3[4].position.x, stage3[4].position.y, 1, 1, stage3[4].texPos.x, stage3[4].texPos.y, stage3[4].texSize.x, stage3[4].texSize.y);

    // 電気
    if (Elec.exist)
        sprite_render(sprElec, Elec.pos.x, Elec.pos.y, 0.5f, 0.5f, 0, 0, 128, 128, 64, 64);

    player.Render();

    // 扉
    sprite_render(sprDoor, door.position.x, door.position.y, 1, 1, door.texPos.x, 177, door.texSize.x, door.texSize.y);

    sprite_render(sprMouse, mousePos.x, mousePos.y, 1, 1, 0, 0, 100, 100, 50, 50);

    // ポーズ画面
    if (pause)
    {
        sprite_render(sprPause, 0, 0);
    }
}
