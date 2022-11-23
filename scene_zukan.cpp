#include "all.h"

int zukan_state;

int Z_color[10];

int Z_page;

Sprite* sprZukan;   // 図鑑

extern Sprite* sprStage0;       // 背景
extern Sprite* sprBelt;         // ベルト部分
extern Sprite* sprGear;         // ギア
extern Sprite* sprBox;          // デカ箱
extern Sprite* sprSyoukouki;    // 昇降機
extern Sprite* sprBoxMove;      // 動かせる箱
extern Sprite* sprSwitch;       // スイッチ
extern Sprite* sprTrolley;      // トロッコ
extern Sprite* sprDoor2;        // 動くドア


void zukan_init()
{
    zukan_state = 0;
}

void zukan_deinit()
{
    safe_delete(sprZukan);

    safe_delete(sprStage0);
    safe_delete(sprBelt);
    safe_delete(sprGear);
    safe_delete(sprBox);
    safe_delete(sprSyoukouki);  
    safe_delete(sprBoxMove);
    safe_delete(sprSwitch);
    safe_delete(sprTrolley);
    safe_delete(sprDoor2);

    // extern
    safe_delete(sprEvPlayer);   // evplayer
    safe_delete(sprEV);         // エレベーター
    safe_delete(sprPause);      // ポーズ
    safe_delete(sprWhite);      // ポーズ白
    safe_delete(sprTerrain);    // 地形
    safe_delete(sprUI);         // UI
    safe_delete(sprElec);       // 電気
    safe_delete(sprDoor);       // ドア
    safe_delete(sprMouse);      // マウスカーソル
}

void zukan_update()
{
    switch (zukan_state)
    {
    case 0:
        ///// 初期設定 //////
        sprZukan = sprite_load(L"./Data/Images/zukan.png");

        sprStage0 = sprite_load(L"./Data/Images/04.png");
        sprBelt = sprite_load(L"./Data/Images/Belt.png");
        sprGear = sprite_load(L"./Data/Images/gear.png");
        sprBox = sprite_load(L"./Data/Images/box.png");
        sprSyoukouki = sprite_load(L"./Data/Images/syoukouki2.png");
        sprBoxMove = sprite_load(L"./Data/Images/boxMove.png");
        sprSwitch = sprite_load(L"./Data/Images/switch.png");
        sprTrolley = sprite_load(L"./Data/Images/trolley.png");
        sprDoor2 = sprite_load(L"./Data/Images/door2.png");

        sprEvPlayer = sprite_load(L"./Data/Images/p.png");
        sprEV = sprite_load(L"./Data/Images/EV.png");
        sprPause = sprite_load(L"./Data/Images/pause.png");
        sprWhite = sprite_load(L"./Data/Images/white.png");
        sprTerrain = sprite_load(L"./Data/Images/terrain.png");
        sprUI = sprite_load(L"./Data/Images/UI.png");
        sprElec = sprite_load(L"./Data/Images/elec.png");
        sprDoor = sprite_load(L"./Data/Images/door.png");
        sprMouse = sprite_load(L"./Data/Images/mouse.png");

        ++zukan_state;
    case 1:
        ///// パラメーターの設定 /////

        for (int i = 0; i < 10; ++i)
        {
            Z_color[i] = 1;
        }

        // ページ
        Z_page = 0;

        ++zukan_state;
    case 2:
        ///// 通常時 /////

        if (TRG(0) & PAD_L3)
        {
            Z_page = Z_page == 0 ? 1 : 0;
        }

        if (TRG(0) & PAD_START)
        {
            nextScene = SCENE::TITLE;
            break;
        }

        switch (PossibleStage)
        {
        case 0:
            Z_color[0] = 0;
        case 1:
            Z_color[1] = 0;
        case 2:
            Z_color[2] = 0;
        case 3:
            Z_color[3] = 0;
        case 4:
            Z_color[4] = 0;
        case 5:
            Z_color[5] = 0;
        case 6:
            Z_color[6] = 0;
        case 7:
            Z_color[7] = 0;
        case 8:
            Z_color[8] = 0;
        case 9:
            Z_color[9] = 0;
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

        break;
    }
}

void zukan_render()
{
    GameLib::clear(1, 1, 1);

    GameLib::sprite_render(sprStage0, 0, 0);
    GameLib::sprite_render(sprZukan, 0, 0);

    switch (Z_page)
    {
    case 0:
        // ベルトコンベアー
        GameLib::sprite_render(sprGear, 765, 130, 1, 1, 0, 0, 120, 120, 0, 0, 0, Z_color[0], Z_color[0], Z_color[0]);
        GameLib::sprite_render(sprGear, 885, 130, 1, 1, 0, 0, 120, 120, 0, 0, 0, Z_color[0], Z_color[0], Z_color[0]);
        GameLib::sprite_render(sprGear, 1005, 130, 1, 1, 0, 0, 60, 120, 0, 0, 0, Z_color[0], Z_color[0], Z_color[0]);
        GameLib::sprite_render(sprBelt, 770, 120, 1, 1, 0, 0, 290, 124, 0, 0, 0, Z_color[0], Z_color[0], Z_color[0]);
        GameLib::sprite_render(sprBelt, 770, 260, 1, -1, 0, 0, 290, 124, 0, 0, 0, Z_color[0], Z_color[0], Z_color[0]);

        // ボックス
        GameLib::sprite_render(sprBox, 1200, 95, 1, 1, 0, 0, 178, 177, 0, 0, 0, Z_color[0], Z_color[0], Z_color[0]);

        // 地形
        GameLib::sprite_render(sprTerrain, 820, 400, 1, 1, 0, 0, 192, 64, 0, 0, 0, Z_color[0], Z_color[0], Z_color[0]);

        // どあ
        GameLib::sprite_render(sprDoor, 1200, 325, 1, 1, 0, 0, 177, 177, 0, 0, 0, Z_color[0], Z_color[0], Z_color[0]);

        // トロッコ
        GameLib::sprite_render(sprTrolley, 820, 530, 1, 1, 0, 0, 178, 177, 0, 0, 0, Z_color[1], Z_color[1], Z_color[1]);
        
        break;
    case 1:
        // movebox
        GameLib::sprite_render(sprBoxMove, 820, 160, 1, 1, 0, 0, 180, 90, 0, 0, 0, Z_color[2], Z_color[2], Z_color[2]);

        // スイッチ
        GameLib::sprite_render(sprSwitch, 1200, 160, 1, 1, 0, 0, 64, 64, 0, 0, 0, Z_color[2], Z_color[2], Z_color[2]);
        GameLib::sprite_render(sprSwitch, 1300, 160, 1, 1, 0, 64, 64, 64, 0, 0, 0, Z_color[2], Z_color[2], Z_color[2]);

        // 足場
        GameLib::sprite_render(sprDoor2, 850, 400, 1, 1, 1152, 0, 128, 64, 0, 0, 0, Z_color[2], Z_color[2], Z_color[2]);

        // 昇降機
        GameLib::sprite_render(sprSyoukouki, 1200, 300, 1, 1, 0, 0, 178, 177, 0, 0, 0, Z_color[3], Z_color[3], Z_color[3]);

        // 昇降機
        GameLib::sprite_render(sprSyoukouki, 830, 530, 1, 1, 0, 177, 178, 177, 0, 0, 0, Z_color[4], Z_color[4], Z_color[4]);


        break;
    }

    // マウスカーソル
    GameLib::sprite_render(sprMouse, mousePos.x, mousePos.y, 1, 1, MouseTexPos.x, MouseTexPos.y, 100, 100, 50, 50);

}
