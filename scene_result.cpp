#include "all.h"

/*****変数*****/
int result_state;

Sprite* sprResult;

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
        

        ++result_state;
    case 1:
        ///// パラメータの設定 /////
        ++result_state;
    case 2:
        ///// 通常時 /////

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
#endif

        // 画面切り替え

        if (TRG(0) & PAD_L3)
        {
            if (mousePos.x > 385 && mousePos.y > 585 && mousePos.x < 1175 && mousePos.y < 640)
            {
                nextScene = SCENE::TITLE;
                break;
            }
            if (mousePos.x > 385 && mousePos.y > 415 && mousePos.x < 1075 && mousePos.y < 520)
            {
                mouseClick(selectStage + 1);
                break;
            }
        }

        /*if (TRG(0) & PAD_SELECT)
        {
            nextScene = SCENE::TITLE;
            break;
        }

        if (STATE(0) & PAD_START)
        {
            mouseClick(selectStage + 1);
            break;
        }*/

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
}
