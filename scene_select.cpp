#include "all.h"

/*****変数*****/
int select_state;

Sprite* sprSelect;
Sprite* sprLock;

void select_init()
{
    select_state = 0;
}

void select_deinit()
{
    safe_delete(sprSelect);
    safe_delete(sprLock);
}

void select_update()
{
    switch (select_state)
    {
    case 0:
        ///// 初期設定 /////
        sprSelect = sprite_load(L"./Data/Images/select.png");
        sprLock = sprite_load(L"./Data/Images/lock.png");

        ++select_state;
    case 1:
        ///// パラメータの設定
        ++select_state;
    case 2:
        ///// 通常時 /////
        
        // 画面切り替え
        if (TRG(0) & PAD_SELECT)
        {
            nextScene = SCENE::TITLE;
            break;
        }
        if (TRG(0) & PAD_START)
        {
            nextScene = SCENE::GAME;
            break;
        }

        // マウスカーソル
#ifdef _DEBUG
        std::ostringstream oss;                                 // 文字列ストリーム
        POINT point;                                            // 位置用の変数を宣言する
        GetCursorPos(&point);                                   // スクリーン座標を取得する
        ScreenToClient(window::getHwnd(), &point);              // クライアント座標に変換する
        oss << "(x=" << point.x << " y=" << point.y << ")";
        SetWindowTextA(window::getHwnd(), oss.str().c_str());   // タイトルバーにを表示させる
#endif

        break;
    }
}

void select_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(sprSelect, 0, 0);


    sprite_render(sprLock, 175.0f, 335.0f, 1.0f, 1.0f, 0, 0);//, 105.0f, 105.0f, 52.5f, 52.5f);
}
