#include "all.h"

/*******変数********/
int title_state;
int title_timer;

int moziState;
int wordState;

int TtexPos[TITLE_MAX];

int JudgeTutorial;

VECTOR2 mousePos;   // マウスカーソルの位置
obj2d Titile_A;

Sprite* sprTitle;
Sprite* sprTtitleAnime;

extern int Tstate;

/// <summary>
/// タイトルの初期設定
/// </summary>
void title_init()
{
    title_state = 0;
    title_timer = 0;
    moziState = 0;
    wordState = 0;
}

/// <summary>
/// タイトルの終了処理
/// </summary>
void title_deinit()
{
    safe_delete(sprTitle);
    safe_delete(sprMouse);
    safe_delete(sprTtitleAnime);

    safe_delete(sprTerrain);

    music::stop(title_bgm);
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
        sprTerrain = sprite_load(L"./Data/Images/terrain.png");
        sprTtitleAnime = sprite_load(L"./Data/Images/titleAnime.png");

        ++title_state;
    case 1:
        ///// パラメーターの設定 /////
        GameLib::setBlendMode(Blender::BS_ALPHA);

        mousePos = {};

        for (int i = 0; i < TITLE_MAX; ++i)
        {
            TtexPos[i] = 64;
        }

        Titile_A = {};
        Titile_A.pos = { 0,0 };
        Titile_A.texPos = {  };
        Titile_A.texSize = { 1536,824 };

        wordState0();

        music::play(title_bgm, true);

        ++title_state;
    case 2:
        ///// 通常時 /////

        if (TRG(0) & PAD_START)
        {
            nextScene = SCENE::ZUKAN;
            break;
        }

        // 画面切り替え
        if (TRG(0) & PAD_L3)
        {
            // スタート
            if (mousePos.x > 615 && mousePos.y > 420 && mousePos.x < 825 && mousePos.y < 495)
            {
                if (JudgeTutorial == 0)
                {
                    Tstate = 0;
                    nextScene = SCENE::TUTORIAL;
                    break;
                }
                else
                {
                    nextScene = SCENE::SELECT;
                    break;
                }
            }
            // チュートリアル
            if (mousePos.x > 500 && mousePos.y > 600 && mousePos.x < 970 && mousePos.y < 670)
            {
                Tstate = 1;
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
        debug::setString("title_timer:%d", title_timer);
        debug::setString("JudgeTutorial:%d", JudgeTutorial);
#endif

#ifdef _DEBUG
        switch (wordState)
        {
        case 0:
            wordState0();            
            wordState = 5;
            break;
        case 1:
            wordState1();            
            wordState = 5;
            break;
        case 2:
            wordState2();
            wordState = 5;
            break;
        case 5:
            break;
        }

        if (title_timer / 60 == 1)
        {
            if (moziState == 0)wordState = 1;
            if (moziState == 1)wordState = 2;
            if (moziState == 2)wordState = 0;
            title_timer = 0;
        }
#endif

        anime(&Titile_A, 9, 10, true, 1);

        break;
    }
    ++title_timer;
}

/// <summary>
/// タイトルの描画処理
/// </summary>
void title_render()
{
    GameLib::clear(0, 0, 0);

    sprite_render(sprTitle, 0, 0);

    //sprite_render(sprTtitleAnime, Titile_A.pos.x, Titile_A.pos.y, 1, 1, Titile_A.texPos.x, Titile_A.texPos.y, 1536, 824);

#ifdef _DEBUG
//    int Count = 0;
//    for (int y = 1; y <= 13; ++y)
//    {
//        for (int x = 1; x <= 24; ++x)
//        {
//            sprite_render(sprTerrain, -64 + (x * 64), -72 + (y * 64), 1, 1, TtexPos[Count], 0, 64, 64);
//            ++Count;
//        }
//    }
#endif

    sprite_render(sprMouse, mousePos.x, mousePos.y, 1, 1, 0, 0, 100, 100, 50, 50);
}

void wordState0()
{
    for (int i = 0; i < TITLE_MAX; ++i)
    {
        TtexPos[i] = 64;
    }

    // m
    TtexPos[28] = 0;
    TtexPos[32] = 0;
    TtexPos[52] = 0;
    TtexPos[53] = 0;
    TtexPos[55] = 0;
    TtexPos[56] = 0;
    TtexPos[76] = 0;
    TtexPos[78] = 0;
    TtexPos[80] = 0;
    TtexPos[100] = 0;
    TtexPos[102] = 0;
    TtexPos[104] = 0;
    TtexPos[124] = 0;
    TtexPos[128] = 0;

    // y
    TtexPos[34] = 0;
    TtexPos[38] = 0;
    TtexPos[59] = 0;
    TtexPos[61] = 0;
    TtexPos[84] = 0;
    TtexPos[108] = 0;
    TtexPos[132] = 0;

    // s
    TtexPos[40] = 0;
    TtexPos[41] = 0;
    TtexPos[42] = 0;
    TtexPos[43] = 0;
    TtexPos[44] = 0;
    TtexPos[64] = 0;
    TtexPos[88] = 0;
    TtexPos[89] = 0;
    TtexPos[90] = 0;
    TtexPos[91] = 0;
    TtexPos[92] = 0;
    TtexPos[116] = 0;
    TtexPos[136] = 0;
    TtexPos[137] = 0;
    TtexPos[138] = 0;
    TtexPos[139] = 0;
    TtexPos[140] = 0;

    // t
    TtexPos[169] = 0;
    TtexPos[170] = 0;
    TtexPos[171] = 0;
    TtexPos[172] = 0;
    TtexPos[173] = 0;
    TtexPos[195] = 0;
    TtexPos[219] = 0;
    TtexPos[243] = 0;
    TtexPos[267] = 0;

    // e
    TtexPos[175] = 0;
    TtexPos[176] = 0;
    TtexPos[177] = 0;
    TtexPos[178] = 0;
    TtexPos[199] = 0;
    TtexPos[223] = 0;
    TtexPos[224] = 0;
    TtexPos[225] = 0;
    TtexPos[226] = 0;
    TtexPos[247] = 0;
    TtexPos[271] = 0;
    TtexPos[272] = 0;
    TtexPos[273] = 0;
    TtexPos[274] = 0;

    // r
    TtexPos[181] = 0;
    TtexPos[182] = 0;
    TtexPos[183] = 0;
    TtexPos[184] = 0;
    TtexPos[205] = 0;
    TtexPos[208] = 0;
    TtexPos[229] = 0;
    TtexPos[230] = 0;
    TtexPos[231] = 0;
    TtexPos[232] = 0;
    TtexPos[253] = 0;
    TtexPos[255] = 0;
    TtexPos[277] = 0;
    TtexPos[280] = 0;

    // y
    TtexPos[186] = 0;
    TtexPos[190] = 0;
    TtexPos[211] = 0;
    TtexPos[213] = 0;
    TtexPos[236] = 0;
    TtexPos[260] = 0;
    TtexPos[284] = 0;

    moziState = wordState;
}

void wordState1()
{
    for (int i = 0; i < TITLE_MAX; ++i)
    {
        TtexPos[i] = 64;
    }

    // o
    TtexPos[103] = 0;
    TtexPos[104] = 0;
    TtexPos[105] = 0;
    TtexPos[106] = 0;
    TtexPos[127] = 0;
    TtexPos[130] = 0;
    TtexPos[151] = 0;
    TtexPos[154] = 0;
    TtexPos[175] = 0;
    TtexPos[178] = 0;
    TtexPos[199] = 0;
    TtexPos[200] = 0;
    TtexPos[201] = 0;
    TtexPos[202] = 0;

    // f
    TtexPos[109] = 0;
    TtexPos[110] = 0;
    TtexPos[111] = 0;
    TtexPos[112] = 0;
    TtexPos[133] = 0;
    TtexPos[157] = 0;
    TtexPos[158] = 0;
    TtexPos[159] = 0;
    TtexPos[160] = 0;
    TtexPos[181] = 0;
    TtexPos[205] = 0;

    moziState = wordState;
}

void wordState2()
{
    for (int i = 0; i < TITLE_MAX; ++i)
    {
        TtexPos[i] = 64;
    }

    // e
    TtexPos[99] = 0;
    TtexPos[100] = 0;
    TtexPos[101] = 0;
    TtexPos[102] = 0;
    TtexPos[123] = 0;
    TtexPos[147] = 0;
    TtexPos[148] = 0;
    TtexPos[149] = 0;
    TtexPos[150] = 0;

    // l


    moziState = wordState;
}