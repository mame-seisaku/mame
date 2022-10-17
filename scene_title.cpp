#include "all.h"

/*******変数********/
int title_state;


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
        ++title_state;
    case 1:
        ///// パラメーターの設定 /////
        GameLib::setBlendMode(Blender::BS_ALPHA);

        ++title_state;
    case 2:
        ///// 通常時 /////
        break;
    }
}

/// <summary>
/// タイトルの描画処理
/// </summary>
void title_render()
{
    GameLib::clear(0, 0, 0);
}
