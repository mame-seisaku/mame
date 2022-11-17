#include "all.h"

/*******変数********/
int title_state;

VECTOR2 mousePos;   // マウスカーソルの位置

Sprite* sprTitle;


/// <summary>
/// タイトルの初期設定
/// </summary>
void title_init()
{
    title_state = 0;
}

/// <summary>
/// タイトルの終了処理
/// </summary>
void title_deinit()
{
    safe_delete(sprTitle);
    safe_delete(sprMouse);
}

/// <summary>
/// タイトルの更新処理
/// </summary>
void title_update()
{
    switch (title_state)
    {
    case 0:
        ///// 初期設定 /////
        sprTitle = sprite_load(L"./Data/Images/title.png");
        sprMouse = sprite_load(L"./Data/Images/mouse.png");

        ++title_state;
    case 1:
        ///// パラメーターの設定 /////
        GameLib::setBlendMode(Blender::BS_ALPHA);

        mousePos = {};

        ++title_state;
    case 2:
        ///// 通常時 /////


        // 画面切り替え
        if (TRG(0) & PAD_L3)
        {
            // スタート
            if (mousePos.x > 615 && mousePos.y > 420 && mousePos.x < 825 && mousePos.y < 495)
            {
                nextScene = SCENE::SELECT;
                break;
            }
            // チュートリアル
            if (mousePos.x > 500 && mousePos.y > 600 && mousePos.x < 970 && mousePos.y < 670)
            {
                nextScene = SCENE::TUTORIAL;
                break;
            }
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
        debug::setString("PossibleStage:%d", PossibleStage);
#endif

        break;
    }
}

/// <summary>
/// タイトルの描画処理
/// </summary>
void title_render()
{
    GameLib::clear(0, 0, 0);

    sprite_render(sprTitle, 0, 0);

    sprite_render(sprMouse, mousePos.x, mousePos.y, 1, 1, 0, 0, 100, 100, 50, 50);
}
