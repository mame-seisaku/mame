#include "all.h"

/*****変数*****/

stage stage5[STAGE5_MAX];

VECTOR2 speed5;

extern float Gangle; // ギア

extern Sprite* sprSyoukouki;    // 昇降機
extern Sprite* sprBox;          // box
extern Sprite* sprStage0;       // 背景
extern Sprite* sprBelt;         // ベルト部分
extern Sprite* sprGear;         // ギア

void stage5_init()
{
    stage_state[5] = 0;
}

void stage5_deinit()
{
    player.Dinit();

    safe_delete(sprSyoukouki);
    safe_delete(sprBox);
    safe_delete(sprStage0);
    safe_delete(sprBelt);
    safe_delete(sprGear);

    safe_delete(sprUI);
    safe_delete(sprElec);
    safe_delete(sprDoor);
    safe_delete(sprEV);
    safe_delete(sprEvPlayer);
    safe_delete(sprMouse);
    safe_delete(sprTerrain);
    safe_delete(sprPause);
    safe_delete(sprWhite);


    music::stop(game_bgm);
}

void stage5_update()
{
    switch (stage_state[5])
    {
    case 0:
        ///// 初期設定 /////
        player.Init();

        sprSyoukouki = sprite_load(L"./Data/Images/syoukouki2.png");
        sprStage0 = sprite_load(L"./Data/Images/04.png");
        sprBox = sprite_load(L"./Data/Images/boxMove.png");
        sprBelt = sprite_load(L"./Data/Images/Belt.png");
        sprGear = sprite_load(L"./Data/Images/gear.png");

        sprUI = sprite_load(L"./Data/Images/UI.png");
        sprElec = sprite_load(L"./Data/Images/elec.png");
        sprDoor = sprite_load(L"./Data/Images/door.png");
        sprEV = sprite_load(L"./Data/Images/EV.png");
        sprEvPlayer = sprite_load(L"./Data/Images/p.png");
        sprMouse = sprite_load(L"./Data/Images/mouse.png");
        sprTerrain = sprite_load(L"./Data/Images/terrain.png");
        sprPause = sprite_load(L"./Data/Images/pause.png");
        sprWhite = sprite_load(L"./Data/Images/white.png");

        ++stage_state[5];
    case 1:
        ///// パラメーターの設定 /////

        // ポーズ
        pause = false;

        // ステージ
        for (int i = 0; i < STAGE5_MAX; ++i)
        {
            stage5[i] = {};
        }

        // type
        // 0 壁
        // 1 ベルトコンベアー
        // 2 扉
        // 3 昇降機 たて
        // 4 昇降機 よこ
        
        // ベルトコンベア
        stage5[0].position = { 0,0 };
        stage5[0].pos = { 768,764 };
        stage5[0].hsize = { 768, 64 };
        stage5[0].type = 1;
        stage5[0].exist = true;

        // 扉 
        stage5[1].position = { 50,460 };
        stage5[1].pos = { stage5[1].position.x + 90,stage5[1].position.y + 80 };
        stage5[1].hsize = { 80, 89 };
        stage5[1].texPos = {};
        stage5[1].texSize = { 178,177 };
        stage5[1].type = 2;
        stage5[1].exist = true;
        stage5[1].open = false;

        // 左下ゆか
        stage5[2].pos = { 160,728 };
        stage5[2].hsize = { 160,96 };
        stage5[2].type = 0;
        stage5[2].exist = true;

        // 真ん中壁よこ
        stage5[3].pos = { 720,310 };
        stage5[3].hsize = { 380,32 };
        stage5[3].type = 0;
        stage5[3].exist = true;

        // 真ん中壁たて
        stage5[4].pos = { 385,180 };
        stage5[4].hsize = { 45,180 };
        stage5[4].type = 0;
        stage5[4].exist = true;


        // EvPlayer
        //EvPlayer = { stage3[4].position.x, stage3[4].position.y + 100 };

        // ドア最後
        door = {};

        // 電気
        Elec = {};

        Gangle = 0;

        music::play(game_bgm, true);


        ++stage_state[5];
    case 2:
        ///// 通常時 /////

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
#ifdef _DEBUG
        oss << "(x=" << point.x << " y=" << point.y << ")";
        SetWindowTextA(window::getHwnd(), oss.str().c_str());   // タイトルバーにを表示させる
        debug::setString("mousePos.x:%f,mousePos.y:%f", mousePos.x, mousePos.y);
#endif
        

        if (!pause)
        {
            player.Update({ 100,500 });


            // ギア回転
            Gangle += ToRadian(10);
            stage5[0].position.x += 10;
            // 範囲外
            if (stage5[0].position.x > 0)
            {        
                stage5[0].position.x = -1536;
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

        UI = player.elec ? 0 : 105;

        break;
    }
}

void stage5_render()
{
    GameLib::clear(1, 1, 1);

    // 背景
    sprite_render(sprStage0, 0, 0);

    // 地形
#ifdef _DEBUG
    for (int i = 0; i < STAGE5_MAX; ++i)
    {
        primitive::rect(stage5[i].pos, stage5[i].hsize * 2, stage5[i].hsize, 0, { stage5[i].color.x,stage5[i].color.y,stage5[i].color.z,1 });
    }
#endif // _DEBUG

    // べるとこんべあ　
    for (int i = 0; i < 13; ++i)
    {
        sprite_render(sprGear, 60 + i * 120, 765, 1, 1, 240, 0, 120, 120, 60, 60, Gangle);
    }
    sprite_render(sprBelt, stage5[0].position.x, 700 - 5);
    sprite_render(sprBelt, stage5[0].position.x + 1530, 700 - 5);
    sprite_render(sprBelt, -stage5[0].position.x, 700 + 124 + 10, 1, -1);
    sprite_render(sprBelt, -stage5[0].position.x - 1530, 700 + 124 + 10, 1, -1);

    // 左床
    for (int x = 0; x < 5; ++x)
    {
        sprite_render(sprTerrain, x * 64, 632, 1, 1, 64, 0, 64, 64);
    }
    

    // エレベーター
    sprite_render(sprEV, stage5[1].position.x - 5, stage5[1].position.y - 658);

    // 扉
    sprite_render(sprDoor, stage5[1].position.x, stage5[1].position.y, 1, 1, stage5[1].texPos.x, stage5[1].texPos.y, stage5[1].texSize.x, stage5[1].texSize.y);

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

    sprite_render(sprMouse, mousePos.x, mousePos.y, 1, 1, 0, 0, 100, 100, 50, 50);
}
