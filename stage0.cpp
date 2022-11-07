#include "all.h"

/*****変数*****/



stage stage0[STAGE0_MAX];

Sprite* sprStage0;
Sprite* sprStage0Floor;
Sprite* sprBox;
Sprite* sprElec;
Sprite* sprDoor;

extern VECTOR2 mousePos;


void stage0_init()
{
    stage_state[0] = 0;
}

void stage0_deinit()
{
    player.Dinit();

    safe_delete(sprStage0);
    safe_delete(sprStage0Floor);
    safe_delete(sprBox);
    safe_delete(sprElec);
    safe_delete(sprDoor);
}

void stage0_update()
{
    switch (stage_state[0])
    {
    case 0:
        ///// 初期設定 /////
        player.Init();
        
        //sprStage0 = sprite_load(L"./Data/Images/stage0.png");
        sprStage0 = sprite_load(L"./Data/Images/04.png");
        sprStage0Floor = sprite_load(L"./Data/Images/03.png");
        sprBox = sprite_load(L"./Data/Images/box.png");
        sprElec = sprite_load(L"./Data/Images/elec.png");
        sprDoor = sprite_load(L"./Data/Images/door.png");

        ++stage_state[0];
    case 1:
        ///// パラメータの設定 /////

        // denkiyou
        ElecPos = {};

        for (int i = 0; i < STAGE0_MAX; ++i)
        {
            stage0[i] = {};
        }

        // 床
        stage0[0].position = { 0,700 };
        stage0[0].pos = { 768,764 };
        stage0[0].hsize = { 768, 64 };
        stage0[0].type = 3;
        stage0[0].exist = true;
        // 四角
        stage0[1].position = { 490,523 };
        stage0[1].pos = { 579,612.5f };
        stage0[1].hsize = { 89, 88.5f };
        stage0[1].type = 1;
        stage0[1].exist = true;
        // 扉
        stage0[2].position = { 1384,570 };
        stage0[2].pos = { 1430,640 };
        stage0[2].hsize = { 40, 60 };
        stage0[2].type = 2;
        stage0[2].exist = true;
        // 左壁
        stage0[3].pos = { 5,412 };
        stage0[3].hsize = { 5,412 };
        stage0[3].type = 0;
        stage0[3].exist = true;
        // アンチ
        stage0[4].position = { 70,630 };
        stage0[4].pos = { 105,640 };
        stage0[4].hsize = { 35,10 };
        stage0[4].type = 0;
        stage0[4].exist = true;

        // 電気
        Elec = {};

        ++stage_state[0];
    case 2:
        ///// 通常時 /////

        player.Update();

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
        debug::setString("PossibleStage:%d", PossibleStage);
        debug::setString("player.elec:%d", player.elec);
#endif
        // マウスでの憑依操作
        if (mousePos.x > 0 && mousePos.y > 700 && mousePos.x < 1536 && mousePos.y < 824)
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
                stage0[0].elec = false;
                player.elec = true;
            }
        }

        
        // 電気の移動と、当たったか判定
        if (Elec.exist) // 存在したら
        {
            // 移動
            Elec.pos.x += Elec.moveVec.x*2;
            Elec.pos.y += Elec.moveVec.y*2;

            // 右下方向へ進む
            if (Elec.moveVec.x > 0)
            {
                // 当たった
                if (Elec.pos.x >= ElecPos.x && Elec.pos.y >= ElecPos.y)
                {
                    player.elec = false;    // プレイヤーの電気消す
                    Elec.exist = false;
                    stage0[0].elec = true;
                }
            }
            // 左下方向へ進む
            else
            {
                // 当たった
                if (Elec.pos.x <= ElecPos.x && Elec.pos.y >= ElecPos.y)
                {
                    player.elec = false;    // プレイヤーの電気消す
                    Elec.exist = false;
                    stage0[0].elec = true;
                }
            }
           
        }

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
                // 扉
                if (stage0[i].type == 2)
                {
                    player.clear = true;
                    break;
                    // シーン切り替え
                    //nextScene = SCENE::RESULT;
                    //return;
                }

                // ベルトコンベア
                if (stage0[i].type == 3 && stage0[i].elec)
                {
                    player.pos.x += 10;
                }

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
                // 扉
                if (stage0[i].type == 2)
                {
                    player.clear = true;
                    break;
                    // シーン切り替え
                    //nextScene = SCENE::RESULT;
                    //return;
                }

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
            case 3:
                stage0[i].color = { 1,1,1,1 };
                break;
            }
        }

        // 床スクロール
        if (stage0[0].elec)
        {
            stage0[0].position.x += 10;
            stage0[1].position.x += 10;
            stage0[1].pos.x += 10;
            player.texPos.x = 84;
        }
        else
        {
            player.texPos.x = 0;
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

    // 地形描画
    for (int i = 0; i < STAGE0_MAX; ++i)
    {
        primitive::rect(stage0[i].pos, stage0[i].hsize * 2, stage0[i].hsize, 0, { stage0[i].color.x,stage0[i].color.y,stage0[i].color.z,stage0[i].color.w });
    }

    // 床
    sprite_render(sprStage0Floor, stage0[0].position.x, stage0[0].position.y);
    // 箱
    sprite_render(sprBox, stage0[1].position.x, stage0[1].position.y);
    // 扉
    sprite_render(sprDoor, stage0[2].position.x, stage0[2].position.y);

    // 電気
    if(Elec.exist)
        sprite_render(sprElec, Elec.pos.x, Elec.pos.y, 0.5f, 0.5f, 0, 0, 128, 128, 64, 64);


    // プレイヤー
    player.Render();
    //primitive::rect(player.pos, player.hsize * 2, player.hsize, 0, { 0,0,1,1 });
}

