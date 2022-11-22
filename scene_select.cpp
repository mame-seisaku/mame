#include "all.h"

/*****変数*****/
int select_state;

int selectStage;

int S_texPos_Y[10];

Sprite* sprSelect;
Sprite* sprLock;

Sprite* sprFrame;
Sprite* sprNum;

// extern宣言
extern VECTOR2 mousePos;

/// <summary>
/// 初期設定
/// </summary>
void select_init()
{
    select_state = 0;
}

/// <summary>
/// 終了処理
/// </summary>
void select_deinit()
{
    safe_delete(sprSelect);
    safe_delete(sprLock);
    safe_delete(sprFrame);
    safe_delete(sprMouse);
    safe_delete(sprNum);
}

/// <summary>
/// 更新処理
/// </summary>
void select_update()
{
    switch (select_state)
    {
    case 0:
        ///// 初期設定 /////
        sprSelect = sprite_load(L"./Data/Images/select.png");
        sprLock = sprite_load(L"./Data/Images/lock.png");
        sprFrame = sprite_load(L"./Data/Images/frame.png");
        sprMouse = sprite_load(L"./Data/Images/mouse.png");
        sprNum = sprite_load(L"./Data/Images/num.png");

        ++select_state;
    case 1:
        ///// パラメータの設定
#ifdef _DEBUG
          //PossibleStage = 4;
#endif // _DEBUG

        for (int i = 0; i < 10; ++i)
        {
            S_texPos_Y[i] = 400;
        }


        selectStage = 0;

        ++select_state;
    case 2:
        ///// 通常時 /////
        
        // マウスカーソル
        std::ostringstream oss;                                 // 文字列ストリーム
        POINT point;                                            // 位置用の変数を宣言する
        GetCursorPos(&point);                                   // スクリーン座標を取得する
        ScreenToClient(window::getHwnd(), &point);              // クライアント座標に変換する
        mousePos.x = point.x;
        mousePos.y = point.y;
#ifdef _DEBUG
        oss << "(x=" << point.x << " y=" << point.y << ")";
        SetWindowTextA(window::getHwnd(), oss.str().c_str());   // タイトルバーにを表示させる
        debug::setString("mousePos.x:%f,mousePos.y:%f", mousePos.x, mousePos.y);
        debug::setString("PossibleStage:%d", PossibleStage);
#endif



        // 画面切り替え
        //一列目

        for (int i = 0; i < 5; i++)
        {
            if (mousePos.x > 156 + (i * 256) && mousePos.y > 250 && mousePos.x < 356 + (i * 256) && mousePos.y < 450)
            {
                if (i > PossibleStage)continue;

                S_texPos_Y[i] = 0;

                mouseClick(i);
                break;
            }
            else
            {
                S_texPos_Y[i] = 400;
            }
            if (mousePos.x > 156 + (i * 256) && mousePos.y > 550 && mousePos.x < 356 + (i * 256) && mousePos.y < 750)
            {
                if (i + 5 > PossibleStage)continue;

                S_texPos_Y[i + 5] = 0;

                mouseClick(i+5);
                break;
            }
            else
            {
                S_texPos_Y[i + 5] = 400;
            }
        }

        if (TRG(0) & PAD_SELECT)
        {
            nextScene = SCENE::TITLE;
            break;
        }
        


        break;
    }
}

/// <summary>
/// 描画処理
/// </summary>
void select_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(sprSelect, 0, 0);

    for (int i = 0; i < 5; i++)
    {
        sprite_render(sprFrame, 256.0f + (i * 256.0f), 350.0f, 1.0f, 1.0f, 0, 0, 200.0f, 200.0f, 100.0f, 100.0f);
        sprite_render(sprFrame, 256.0f + (i * 256.0f), 650.0f, 1.0f, 1.0f, 0, 0, 200.0f, 200.0f, 100.0f, 100.0f);
        
        sprite_render(sprNum, 256.0f + (i * 256.0f), 350, 1, 1, i * 200, S_texPos_Y[i] + 0, 200, 200, 100, 100);
        sprite_render(sprNum, 256.0f + (i * 256.0f), 650, 1, 1, i * 200, S_texPos_Y[i + 5] + 200, 200, 200, 100, 100);
    }
    

    disp_key();

    sprite_render(sprMouse, mousePos.x, mousePos.y, 1, 1, 0, 0, 100, 100, 50, 50);
}

/// <summary>
/// 鍵かかってる画像描画
/// </summary>
void disp_key()
{
   /* for (int i = PossibleStage + 1; i < 6; ++i)
    {
        sprite_render(sprLock, (256.0f * i), 350.0f, 1.0f, 1.0f, 0, 0, 105.0f, 105.0f, 52.5f, 52.5f);
    }
    for (int i = (PossibleStage>5)?PossibleStage:6; i < 11; ++i)
    {
        sprite_render(sprLock, (256.0f * i)-1280, 650.0f, 1.0f, 1.0f, 0, 0, 105.0f, 105.0f, 52.5f, 52.5f);
    }*/


    //  if(i<5)
    //sprite_render(sprLock, 256.0f + (i * 256.0f), 350.0f, 1.0f, 1.0f, 0, 0, 105.0f, 105.0f, 52.5f, 52.5f);
    // if (i > 6)
    // sprite_render(sprLock, 256.0f + (i * 256.0f), 650.0f, 1.0f, 1.0f, 0, 0, 105.0f, 105.0f, 52.5f, 52.5f);

    //sprite_render(sprLock, 256.0f, 350.0f, 1.5f, 1.5f, 0, 0, 105.0f, 105.0f, 52.5f, 52.5f);
        
    switch (PossibleStage)
    {
        // 一列目
    case 0:
        sprite_render(sprLock, 512.0f, 350.0f, 1.5f, 1.5f, 0, 0, 105.0f, 105.0f, 52.5f, 52.5f);
    case 1:
        sprite_render(sprLock, 768.0f, 350.0f, 1.5f, 1.5f, 0, 0, 105.0f, 105.0f, 52.5f, 52.5f);
    case 2:
        sprite_render(sprLock, 1024.0f, 350.0f, 1.5f, 1.5f, 0, 0, 105.0f, 105.0f, 52.5f, 52.5f);
    case 3:
        sprite_render(sprLock, 1280.0f, 350.0f, 1.5f, 1.5f, 0, 0, 105.0f, 105.0f, 52.5f, 52.5f);
        // 二列目
    case 4:
        sprite_render(sprLock, 256.0f, 650.0f, 1.5f, 1.5f, 0, 0, 105.0f, 105.0f, 52.5f, 52.5f);
    case 5:
        sprite_render(sprLock, 512.0f, 650.0f, 1.5f, 1.5f, 0, 0, 105.0f, 105.0f, 52.5f, 52.5f);
    case 6:
        sprite_render(sprLock, 768.0f, 650.0f, 1.5f, 1.5f, 0, 0, 105.0f, 105.0f, 52.5f, 52.5f);
    case 7:
        sprite_render(sprLock, 1024.0f, 650.0f, 1.5f, 1.5f, 0, 0, 105.0f, 105.0f, 52.5f, 52.5f);
    case 8:
        sprite_render(sprLock, 1280.0f, 650.0f, 1.5f, 1.5f, 0, 0, 105.0f, 105.0f, 52.5f, 52.5f);
    }
}

/// <summary>
/// マウスクリック判定
/// </summary>
/// <param name="s">ステージ番号</param>
void mouseClick(int s)
{
    if (TRG(0) & PAD_L3)
    {
        selectStage = s;


        // シーン切り替え
        switch (s)
        {
        case 0:
            nextScene = SCENE::STAGE0;
            break;
        case 1:
            nextScene = SCENE::STAGE1;
            break;
        case 2:
            nextScene = SCENE::STAGE2;
            break;
        case 3:
            nextScene = SCENE::STAGE3;
            break;
        case 4:
            nextScene = SCENE::STAGE4;
            break;
        case 5:
            nextScene = SCENE::STAGE5;
            break;
        }
    }
}

void NotmouseClick(int s)
{
    selectStage = s;

    // シーン切り替え
    switch (s)
    {
    case 0:
        nextScene = SCENE::STAGE0;
        break;
    case 1:
        nextScene = SCENE::STAGE1;
        break;
    case 2:
        nextScene = SCENE::STAGE2;
        break;
    case 3:
        nextScene = SCENE::STAGE3;
        break;
    case 4:
        nextScene = SCENE::STAGE4;
        break;
    case 5:
        nextScene = SCENE::STAGE5;
        break;
    }
}
