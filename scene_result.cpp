#include "all.h"

/*****変数*****/
int result_state;

float R_texPos_y[3];

Sprite* sprResult;
Sprite* sprIcon;

/// <summary>
/// 初期設定
/// </summary>
void result_init()
{
    result_state = 0;
}

/// <summary>
/// 終了処理
/// </summary>
void result_deinit()
{
    safe_delete(sprResult);
    safe_delete(sprMouse);
    safe_delete(sprIcon);

    music::stop(result_bgm);
}

/// <summary>
/// 更新処理
/// </summary>
void result_update()
{
    switch (result_state)
    {
    case 0:
        ///// 初期化 /////
        sprResult = sprite_load(L"./Data/Images/result.png");
        sprMouse = sprite_load(L"./Data/Images/mouse.png");
        sprIcon = sprite_load(L"./Data/Images/icon.png");

        ++result_state;
    case 1:
        ///// パラメータの設定 /////

        R_texPos_y[0] = 0;
        R_texPos_y[1] = 0;
        R_texPos_y[2] = 0;

        music::play(result_bgm, true);

        ++result_state;
    case 2:
        ///// 通常時 /////

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
#endif

        // 画面切り替え
        if (mousePos.x > 240 && mousePos.y > 384 && mousePos.x < 496 && mousePos.y < 640)
        {
            R_texPos_y[0] = 256;
            if (TRG(0) & PAD_L3)
            {
                mouseClick(selectStage);
                break;
            }
        }
        else
            R_texPos_y[0] = 0;
        if (mousePos.x > 640 && mousePos.y > 384 && mousePos.x < 896 && mousePos.y < 640)
        {
            R_texPos_y[1] = 256;
            if (TRG(0) & PAD_L3)
            {
                nextScene = SCENE::SELECT;
                break;
            }
        }
        else
            R_texPos_y[1] = 0;
        if (mousePos.x > 1040 && mousePos.y > 384 && mousePos.x < 1296 && mousePos.y < 640)
        {
            R_texPos_y[2] = 256;
            if (TRG(0) & PAD_L3)
            {
                mouseClick(selectStage + 1);
                break;
            }
        }
        else
            R_texPos_y[2] = 0;

        if (mousePos.x > 240 && mousePos.y > 384 && mousePos.x < 496 && mousePos.y < 640||
            mousePos.x > 640 && mousePos.y > 384 && mousePos.x < 896 && mousePos.y < 640||
            mousePos.x > 1040 && mousePos.y > 384 && mousePos.x < 1296 && mousePos.y < 640
            )
        {
            MouseTexPos.x = 100;
        }
        else
        {
            MouseTexPos.x = 0;
        }


        break;
    }
}

/// <summary>
/// 描画処理
/// </summary>
void result_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(sprResult, 0, 0);

    sprite_render(sprIcon, 368, 512, 1, 1, 0, R_texPos_y[0], 256, 256, 128, 128);
    sprite_render(sprIcon, 768, 512, 1, 1, 256, R_texPos_y[1], 256, 256, 128, 128);
    sprite_render(sprIcon, 1168, 512, 1, 1, 512, R_texPos_y[2], 256, 256, 128, 128);

    sprite_render(sprMouse, mousePos.x, mousePos.y, 1, 1, 0, 0, 100, 100, 50, 50);
}
