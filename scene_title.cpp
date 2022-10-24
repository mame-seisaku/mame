#include "all.h"

/*******変数********/
int title_state;

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

        ++title_state;
    case 1:
        ///// パラメーターの設定 /////
        GameLib::setBlendMode(Blender::BS_ALPHA);

        ++title_state;
    case 2:
        ///// 通常時 /////

        // 画面切り替え
        if (TRG(0) & PAD_START)
        {
            nextScene = SCENE::SELECT;
            break;
        }

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
}
