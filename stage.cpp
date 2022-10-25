#include "all.h"

int stage_state[STAGE_MAX];
    
// init deinit がきれいな形で呼ばれてないから
// stage終了毎に呼ぶ必要があるかも

/// <summary>
/// 初期設定
/// </summary>
void stage_init()
{
    stage0_init();
    stage1_init();
}

/// <summary>
/// 終了処理
/// </summary>
void stage_deinit()
{
    stage0_deinit();
    stage1_deinit();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="s">ステージ番号</param>
void stage_update(int s)
{
    switch (s)
    {
    case 0:
        stage0_update();
        break;
    case 1:
        stage1_update();
        break;
    }
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="s">ステージ番号</param>
void stage_render(int s)
{
    switch (s)
    {
    case 0:
        stage0_render();
        break;
    case 1:
        stage1_render();
        break;
    }
}
