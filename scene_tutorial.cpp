#include "all.h"

/*****変数*****/
int tutorial_state;
int Tstate;

bool T_p;

obj2d T_pos;
obj2d T_jump;
VECTOR2 T_texPos[3];

stage tutorialS[TUTORIAL_MAX];

Sprite* sprJump;
Sprite* sprB;
Sprite* sprTutorial;
Sprite* sprTWord;
Sprite* sprWord;
Sprite* sprTutorialP;   // チュートリアルプレイヤー
Sprite* sprKeyW;    // ADキー

extern Sprite* sprBoxMove; // 動かせる箱

extern VECTOR2 mousePos;
extern stage door;
extern Sprite* sprElec; // 電気
extern Sprite* sprDoor; // ドア

/// <summary>
/// 初期設定
/// </summary>
void tutorial_init()
{
    tutorial_state = 0;
    //Tstate = 0;
}

/// <summary>
/// 終了処理
/// </summary>
void tutorial_deinit()
{
    player.Dinit();

    safe_delete(sprTutorial);
    safe_delete(sprTWord);
    safe_delete(sprWord);
    safe_delete(sprB);

    safe_delete(sprEvPlayer);
    safe_delete(sprJump);
    safe_delete(sprBoxMove);
    safe_delete(sprKeyW);
    safe_delete(sprTutorialP);
    safe_delete(sprElec);
    safe_delete(sprDoor);
    safe_delete(sprEV);
    safe_delete(sprMouse);
    safe_delete(sprTerrain);
    safe_delete(sprPause);

    music::stop(game_bgm);
}

/// <summary>
/// 更新処理
/// </summary>
void tutorial_update()
{
    switch (tutorial_state)
    {
    case 0:
        ///// 初期化 /////
        player.Init();

        sprTutorial = sprite_load(L"./Data/Images/05.png");

        sprJump = sprite_load(L"./Data/Images/jump.png");
        sprBoxMove = sprite_load(L"./Data/Images/boxMove.png");
        sprKeyW = sprite_load(L"./Data/Images/ad.png");
        sprTutorialP = sprite_load(L"./Data/Images/player1.png");
        sprB = sprite_load(L"./Data/Images/B.png");
        sprTWord = sprite_load(L"./Data/Images/Tword.png");
        sprWord = sprite_load(L"./Data/Images/word.png");
        sprElec = sprite_load(L"./Data/Images/elec.png");
        sprDoor = sprite_load(L"./Data/Images/door.png");
        sprEV = sprite_load(L"./Data/Images/EV.png");
        sprEvPlayer = sprite_load(L"./Data/Images/p.png");
        sprMouse = sprite_load(L"./Data/Images/mouse.png");
        sprTerrain = sprite_load(L"./Data/Images/terrain.png");
        sprPause = sprite_load(L"./Data/Images/pause.png");

        ++tutorial_state;
    case 1:
        ///// パラメータの設定
        
        // ポーズ
        pause = false;

        // 電気用
        ElecPos = {};

        for (int i = 0; i < TUTORIAL_MAX; ++i)
        {
            tutorialS[i] = {};
        }

        // type
        // 0 床
        // 1 扉
        // 2 movebox

        // 床
        tutorialS[0].position = { 0,0 };
        tutorialS[0].pos = { 768,764 };
        tutorialS[0].hsize = { 768, 64 };
        tutorialS[0].type = 0;
        tutorialS[0].exist = true;

        // 扉
        tutorialS[1].position = { 1239,530 };
        tutorialS[1].pos = { 1330,620 };
        tutorialS[1].hsize = { 80, 89 };
        tutorialS[1].texPos = {};
        tutorialS[1].texSize = { 178,177 };
        tutorialS[1].type = 1;
        tutorialS[1].exist = true;
        tutorialS[1].open = false;

        // movebox
        tutorialS[2].position = { 800, 610 };
        tutorialS[2].pos = { tutorialS[2].position.x + 44,tutorialS[2].position.y + 44 };
        tutorialS[2].texPos.x = 90;
        tutorialS[2].hsize = { 44,44 };
        tutorialS[2].type = 2;
        tutorialS[2].exist = true;
                

        // ドア最後
        door = {};

        // 電気
        Elec = {};

        // EvPlayer
        EvPlayer = { tutorialS[1].position.x, tutorialS[1].position.y + 100 };

        // マウスカーソル
        MouseTexPos = {};


        // プレイヤー
        T_pos = {};
        T_pos.pos = { 250, 270 };
        T_pos.texSize = { 84,100 };
        T_p = true;

        // ジャンプ
        T_jump = {};
        T_jump.pos = { 900 ,190 };
        T_jump.texSize = { 84,170 };

        // 文字
        T_texPos[0] = {};
        T_texPos[1] = { 16,0 };
        T_texPos[2] = { 0,16 };
        


        // BGM
        music::play(game_bgm, true);

        ++tutorial_state;
    case 2:
        ///// 通常時 /////

        if (door.end)
        {
            player.pos.y = EvPlayer.y - 45;
            EvPlayer.y -= STAGE_MOVE;
        }
        if (EvPlayer.y < -200)
        {
            nextScene = SCENE::SELECT;
            break;
        }

        switch (Tstate)
        {
        case 0:
            JudgeTutorial = 1;
            if (TRG(0) & PAD_L3)Tstate += 1;
            break;
        case 1:
            // チュートリアルを選んだ
            if (TRG(0) & PAD_L3)Tstate += 1;
            break;
        case 2:
            if (TRG(0) & PAD_L3)Tstate += 1;
            break;
        case 3:
            if (TRG(0) & PAD_L3)Tstate += 1;
            break;
        case 4:
            if (TRG(0) & PAD_L3)Tstate += 1;
            break;
        case 5:
            if (TRG(0) & PAD_L3)Tstate += 1;
            break;
        case 6: // プレイヤー操作
            if (TRG(0) & PAD_L3)Tstate += 1;
            if (T_p)
            {
                T_texPos[0].x = 48;
                T_texPos[1].x = 16;
                T_pos.pos.x += 5;
            }
            else
            {
                T_texPos[0].x = 0;
                T_texPos[1].x = 64;
                T_pos.pos.x -= 5;
            }

            if (T_pos.pos.x > 400)T_p = false;
            if (T_pos.pos.x < 100)T_p = true;

            if (T_jump.anime == 0 || T_jump.anime == 1 || T_jump.anime == 2)
            {
                T_texPos[2].x = 48;
            }
            else
            {
                T_texPos[2].x = 0;
            }

            anime(&T_pos, 6, 10, true, 1);
            anime(&T_jump, 19, 2, true, 1);

            break;
        case 7:
            if (TRG(0) & PAD_L3)Tstate += 1;
            break;
        case 8:
            if (TRG(0) & PAD_L3)Tstate += 1;
            if (mousePos.x > 600 && mousePos.y > 276 && mousePos.x < 690 && mousePos.y < 366||
                mousePos.x > 800 && mousePos.y > 276 && mousePos.x < 890 && mousePos.y < 366)
            {
                MouseTexPos.x = 100;
            }
            else
            {
                MouseTexPos.x = 0;
            }

            break;
        case 9:
            if (TRG(0) & PAD_L3)Tstate += 1;
            if (mousePos.x > 600 && mousePos.y > 276 && mousePos.x < 690 && mousePos.y < 366 ||
                mousePos.x > 800 && mousePos.y > 276 && mousePos.x < 890 && mousePos.y < 366)
            {
                MouseTexPos.x = 100;
            }
            else
            {
                MouseTexPos.x = 0;
            }

            break;
        case 10:
            if (TRG(0) & PAD_L3)Tstate += 1;
            if (mousePos.x > 600 && mousePos.y > 276 && mousePos.x < 690 && mousePos.y < 366 ||
                mousePos.x > 800 && mousePos.y > 276 && mousePos.x < 890 && mousePos.y < 366)
            {
                MouseTexPos.x = 100;
            }
            else
            {
                MouseTexPos.x = 0;
            }
            break;
        case 11:
            if (TRG(0) & PAD_L3)Tstate += 1;
            if (mousePos.x > 600 && mousePos.y > 276 && mousePos.x < 690 && mousePos.y < 366 ||
                mousePos.x > 800 && mousePos.y > 276 && mousePos.x < 890 && mousePos.y < 366)
            {
                MouseTexPos.x = 100;
            }
            else
            {
                MouseTexPos.x = 0;
            }
            break;
        case 12:

            if (mousePos.x > 800 && mousePos.y > 610 && mousePos.x < 890 && mousePos.y < 700)
            {
                // 電気を飛ばす
                if (TRG(0) & PAD_L3)
                {
                    // プレイヤーに電気があれば
                    if (!Elec.exist && player.elec)
                    {
                        SetElecMove();
                    }
                }

                MouseTexPos.x = 100;
            }
            else
            {
                MouseTexPos.x = 0;
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
                            tutorialS[2].elec = true;
                            Tstate = 13;
                        }
                    }
                    else
                    {
                        // 当たった
                        if (Elec.pos.x >= ElecPos.x)
                        {
                            player.elec = false;    // プレイヤーの電気消す
                            Elec.exist = false;
                            tutorialS[2].elec = true;
                            Tstate = 13;
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
                            tutorialS[2].elec = true;
                            Tstate = 13;
                        }
                    }
                    else
                    {
                        // 当たった
                        if (Elec.pos.x <= ElecPos.x)
                        {
                            player.elec = false;    // プレイヤーの電気消す
                            Elec.exist = false;
                            tutorialS[2].elec = true;
                            Tstate = 13;
                        }
                    }
                }
            }
            break;
        case 13:
            if (TRG(0) & PAD_L3)Tstate += 1;
            break;
        case 14:
            if (TRG(0) & PAD_L3)Tstate += 1;
            break;
        case 15:
            if (TRG(0) & PAD_L3)Tstate += 1;
            break;
        case 16:
            if (mousePos.x > 800 && mousePos.y > 610 && mousePos.x < 890 && mousePos.y < 700)
            {
                // 電気回収
                if (TRG(0) & PAD_R3 && !player.elec)
                {
                    Elec.exist = false;
                    tutorialS[2].elec = false;
                    player.elec = true;
                    Tstate = 17;
                }

                MouseTexPos.x = 100;
            }
            else
            {
                MouseTexPos.x = 0;
            }
            break;
        case 17:
            if (TRG(0) & PAD_L3)Tstate += 1;
            break;
        case 18:
            if (TRG(0) & PAD_L3)Tstate += 1;
            break;
        case 19:
            if (TRG(0) & PAD_L3)Tstate += 1;
            break;
        case 20:
            if (TRG(0) & PAD_L3)Tstate += 1;
            break;
        case 21:
            if (mousePos.x > 800 && mousePos.y > 610 && mousePos.x < 890 && mousePos.y < 700)
            {

                // 電気を飛ばす
                if (TRG(0) & PAD_L3)
                {
                    // プレイヤーに電気があれば
                    if (!Elec.exist && player.elec)
                    {
                        SetElecMove();
                    }
                }
                // 電気回収
                if (TRG(0) & PAD_R3 && !player.elec)
                {
                    Elec.exist = false;
                    tutorialS[2].elec = false;
                    player.elec = true;
                }

                MouseTexPos.x = 100;
            }
            else
            {
                MouseTexPos.x = 0;
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
                            tutorialS[2].elec = true;
                        }
                    }
                    else
                    {
                        // 当たった
                        if (Elec.pos.x >= ElecPos.x)
                        {
                            player.elec = false;    // プレイヤーの電気消す
                            Elec.exist = false;
                            tutorialS[2].elec = true;
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
                            tutorialS[2].elec = true;
                        }
                    }
                    else
                    {
                        // 当たった
                        if (Elec.pos.x <= ElecPos.x)
                        {
                            player.elec = false;    // プレイヤーの電気消す
                            Elec.exist = false;
                            tutorialS[2].elec = true;
                        }
                    }
                }
            }
            break;
        }

        // 画面切り替え
        if (TRG(0) & PAD_SELECT)
        {
            nextScene = SCENE::TITLE;
            break;
        }
        // 強制チュートリアル終了

        if (!pause)
        {
            player.Update({ 100,200 });

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
#endif
            
            // 扉アニメ
            if (tutorialS[1].open)
                anime(&tutorialS[1], 7, 10, false, 0);

            // クリア判定
            if (tutorialS[1].end && tutorialS[1].one && !door.close)
            {
                player.clear = true;
                door = tutorialS[1];
                door.state = 0;
                door.close = true;
            }

            if (player.clear)
            {
                player.pos.x = tutorialS[1].position.x + 71;    // ドアの位置に移動
                // 電気を戻す
                player.elec = true;
                for (int i = 0; i < TUTORIAL_MAX; ++i)
                {
                    tutorialS[i].elec = false;
                }

                Elec.exist = false;
                player.elec = true;

                // 扉しまる
                anime(&door, 7, 10, false, 0);
            }


            // 位置にスピードを足す
            player.pos.y += player.speed.y;

            // 上下のめり込みチェック
            for (int i = 0; i < TUTORIAL_MAX; ++i)
            {
                if (hitCheck(&player, &tutorialS[i]))
                {
                    if (tutorialS[i].type == 1)
                    {
                        if(Tstate==21)
                            tutorialS[i].open = true;
                        continue;
                    }

                    // めり込み対策		// 当たり判定
                    float dist;
                    if (player.speed.y >= 0)
                        dist = check(&player, &tutorialS[i], DIR::DOWN);
                    else
                        dist = check(&player, &tutorialS[i], DIR::UP);
                    player.pos.y += dist;
                    player.speed.y = 0;
                }
            }

            // 位置にスピードを足す
            player.pos.x += player.speed.x;

            // 左右のめりこみチェック
            for (int i = 0; i < TUTORIAL_MAX; ++i)
            {
                if (hitCheck(&player, &tutorialS[i]))
                {
                    if (tutorialS[i].type == 1)
                    {
                        if (Tstate == 21)
                            tutorialS[i].open = true;
                        continue;
                    }

                    // めり込み対策		// 当たり判定
                    float dist;
                    if (player.speed.x >= 0)
                        dist = check(&player, &tutorialS[i], DIR::RIGHT);
                    else
                        dist = check(&player, &tutorialS[i], DIR::LEFT);
                    player.pos.x += dist;
                    player.speed.x = 0;
                }
            }
        }

        tutorialS[2].texPos.x = tutorialS[2].elec ? 0 : 90;

        break;
    }
}

/// <summary>
/// 描画処理
/// </summary>
void tutorial_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(sprTutorial, 0, 0);

    // 地形描画
#ifdef _DEBUG
    for (int i = 0; i < TUTORIAL_MAX; ++i)
    {
        primitive::rect(tutorialS[i].pos, tutorialS[i].hsize * 2, tutorialS[i].hsize, 0, { tutorialS[i].color.x,tutorialS[i].color.y,tutorialS[i].color.z,1 });
    }
#endif

    for (int y = 0; y < 2; ++y)
    {
        for (int x = 0; x < 24; ++x)
        {
            sprite_render(sprTerrain, 64 * x, 640 + (64 * (y + 1)), 1, 1, 64, 0, 64, 64);
        }
    }

    // エレベーター
    sprite_render(sprEV, tutorialS[1].position.x - 5, tutorialS[1].position.y - 653);

    // 扉
    sprite_render(sprDoor, tutorialS[1].position.x, tutorialS[1].position.y, 1, 1, tutorialS[1].texPos.x, tutorialS[1].texPos.y, tutorialS[1].texSize.x, tutorialS[1].texSize.y);

    // 電気
    if (Elec.exist)
        sprite_render(sprElec, Elec.pos.x, Elec.pos.y, 1, 1, 0, 0, 128, 128, 64, 64);

    player.Render();

    // playerEv
    if (door.end)
        sprite_render(sprEvPlayer, EvPlayer.x + 35, EvPlayer.y);

    // 扉
    sprite_render(sprDoor, door.position.x, door.position.y, 1, 1, door.texPos.x, 177, door.texSize.x, door.texSize.y);

    // movebox
    sprite_render(sprBoxMove, tutorialS[2].position.x, tutorialS[2].position.y, 1, 1, tutorialS[2].texPos.x, 0, 90, 90);               // 動く箱

    // word 
    switch (Tstate)
    {
    case 0: // 今チュートリアル飛ばそうとしたね？
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 0, 1, 1, 1499.9f, 0, 1536, 724);
        break;
    case 1: // こんにちは
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 0, 1, 1, 0, 0, 1536, 724);
        break;
    case 2: // チュートリアルです
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 0, 1, 1, 2999.8f, 0, 1536, 724);
        break;
    case 3: // この荒れ果てた世界で電力を使えるのがあなただけ
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 0, 1, 1, 4499.7f, 0, 1536, 724);
        break;
    case 4: // 自分自身の電気を世界に分け与えここから脱出しよう
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 0, 1, 1, 5999.6f, 0, 1536, 724);
        break;
    case 5: // プレイヤーの操作説明をするよ
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 0, 1, 1, 7499.5f, 0, 1536, 724);

        sprite_render(sprTutorialP, 768, 270, 1, 1, 0, 0, 84, 100, 42, 50);                              // プレイヤー
        break;
    case 6: // ADキーで横に移動、スペースでジャンプ可能
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 0, 1, 1, 8999.4f, 0, 1536, 724);

        sprite_render(sprTerrain, 1421, 366, 1, 1, 64, 0, 64, 64);              // 地形   
        for (int i = 0; i < 22; ++i)
        {
            sprite_render(sprTerrain, 51 + (64 * i), 366, 1, 1, 64, 0, 64, 64); // 地形
        }
        sprite_render(sprTutorialP, T_pos.pos.x, 270, 1, 1, T_pos.texPos.x, T_pos.texPos.y, 84, 100);    // 横に動くプレイヤー
        sprite_render(sprJump, T_jump.pos.x,T_jump.pos.y, 1, 1, T_jump.texPos.x, 0, 84, 170);                              // 縦に動くプレイヤー
        sprite_render(sprKeyW, 200, 150, 4, 4, T_texPos[0].x, T_texPos[0].y, 16, 16);   // A
        sprite_render(sprKeyW, 300, 150, 4, 4, T_texPos[1].x, T_texPos[1].y, 16, 16);   // D
        sprite_render(sprKeyW, 620, 150, 4, 4, T_texPos[2].x, T_texPos[2].y, 32, 16);   // space

        break;
    case 7: // それでは電気を分け与えるとこらから始めるよ
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 0, 1, 1, 10499.3f, 0, 1536, 724);
        break;
    case 8: // 操作は単純。マウスを動かしランプが光るところを探そう
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 0, 1, 1, 11999.2f, 0, 1536, 724);

        sprite_render(sprTerrain, 1421, 366, 1, 1, 64, 0, 64, 64);              // 地形   
        for (int i = 0; i < 22; ++i)
        {
            sprite_render(sprTerrain, 51 + (64 * i), 366, 1, 1, 64, 0, 64, 64); // 地形
        }
        sprite_render(sprBoxMove, 600, 276, 1, 1, 90, 0, 90, 90);               // 動く箱
        sprite_render(sprBoxMove, 800, 276, 1, 1, 90, 0, 90, 90);               // 動く箱
        sprite_render(sprMouse, 200,200, 1, 1, 0, 0, 100, 100);                 // マウスカーソル
        sprite_render(sprMouse, 300,200, 1, 1, 100, 0, 100, 100);               // マウスカーソル
        break;
    case 9: // ランプが光っているときに左クリックで電気を分け与えることが出来る
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 0, 1, 1, 13499.1f, 0, 1536, 724);

        sprite_render(sprTerrain, 1421, 366, 1, 1, 64, 0, 64, 64);              // 地形   
        for (int i = 0; i < 22; ++i)
        {
            sprite_render(sprTerrain, 51 + (64 * i), 366, 1, 1, 64, 0, 64, 64); // 地形
        }
        sprite_render(sprBoxMove, 600, 276, 1, 1, 90, 0, 90, 90);               // 動く箱
        sprite_render(sprBoxMove, 800, 276, 1, 1, 90, 0, 90, 90);               // 動く箱
        sprite_render(sprMouse, 200, 200, 1, 1, 0, 0, 100, 100);                 // マウスカーソル
        sprite_render(sprMouse, 300, 200, 1, 1, 100, 0, 100, 100);               // マウスカーソル
        break;
    case 10: // 電気を分け与えるとそのオブジェクトを動かすことが出来ます 
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 20, 1, 1, 0, 724, 1536, 724);

        sprite_render(sprTerrain, 1421, 366, 1, 1, 64, 0, 64, 64);              // 地形   
        for (int i = 0; i < 22; ++i)
        {
            sprite_render(sprTerrain, 51 + (64 * i), 366, 1, 1, 64, 0, 64, 64); // 地形
        }
        sprite_render(sprBoxMove, 600, 276, 1, 1, 90, 0, 90, 90);               // 動く箱
        sprite_render(sprBoxMove, 800, 276, 1, 1, 90, 0, 90, 90);               // 動く箱
        sprite_render(sprMouse, 200, 200, 1, 1, 0, 0, 100, 100);                 // マウスカーソル
        sprite_render(sprMouse, 300, 200, 1, 1, 100, 0, 100, 100);               // マウスカーソル
        break;
    case 11: // それでは早速やってみましょう
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 20, 1, 1, 1499.9f, 724, 1536, 724);

        sprite_render(sprTerrain, 1421, 366, 1, 1, 64, 0, 64, 64);              // 地形   
        for (int i = 0; i < 22; ++i)
        {
            sprite_render(sprTerrain, 51 + (64 * i), 366, 1, 1, 64, 0, 64, 64); // 地形
        }
        sprite_render(sprBoxMove, 600, 276, 1, 1, 90, 0, 90, 90);               // 動く箱
        sprite_render(sprBoxMove, 800, 276, 1, 1, 90, 0, 90, 90);               // 動く箱
        sprite_render(sprMouse, 200, 200, 1, 1, 0, 0, 100, 100);                 // マウスカーソル
        sprite_render(sprMouse, 300, 200, 1, 1, 100, 0, 100, 100);               // マウスカーソル
        break;
    case 12:
        break;
    case 13: // よくできました。あなたはかしこい
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 20, 1, 1, 2999.8f, 724, 1536, 724);
        break;
    case 14: // 自分自身に電気がない状態では動けないので気を付けるように
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 20, 1, 1, 4499.7f, 724, 1536, 724);
        break;
    case 15: // 右クリックで電気を回収することが出来ます
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 20, 1, 1, 5999.6f, 724, 1536, 724);
        break;
    case 16:
        break;
    case 17: // よくできました。あなたは天才です
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 20, 1, 1, 7499.5f, 724, 1536, 724);
        break;
    case 18: // もうシステムは理解できましたね？
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 20, 1, 1, 8999.4f, 724, 1536, 724);
        break;
    case 19: // あとはひたすら扉を目指すだけです
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 20, 1, 1, 10499.3f, 724, 1536, 724);

        sprite_render(sprTerrain, 1421, 366, 1, 1, 64, 0, 64, 64);              // 地形   
        for (int i = 0; i < 22; ++i)
        {
            sprite_render(sprTerrain, 51 + (64 * i), 366, 1, 1, 64, 0, 64, 64); // 地形
        }
        sprite_render(sprDoor, 700, 197, 1, 1, 0, 0, tutorialS[1].texSize.x, tutorialS[1].texSize.y);
        break;
    case 20: // good luck have fun
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 20, 1, 1, 11999.2f, 724, 1536, 724);

        sprite_render(sprTerrain, 1421, 366, 1, 1, 64, 0, 64, 64);              // 地形   
        for (int i = 0; i < 22; ++i)
        {
            sprite_render(sprTerrain, 51 + (64 * i), 366, 1, 1, 64, 0, 64, 64); // 地形
        }
        sprite_render(sprDoor, 700, 197, 1, 1, 0, 0, tutorialS[1].texSize.x, tutorialS[1].texSize.y);
        break;
    }



    // マウスカーソル
    sprite_render(sprMouse, mousePos.x, mousePos.y, 1, 1, MouseTexPos.x, MouseTexPos.y, 100, 100, 50, 50);

    // ポーズ画面
    if (pause)
    {
        sprite_render(sprPause, 0, 0);
    }
}
