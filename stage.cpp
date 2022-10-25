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


/// <summary>
/// 壁との当たり判定
/// </summary>
/// <param name="rc1"></param>
/// <param name="rc2"></param>
/// <returns></returns>
bool hitCheck(obj2d* rc1, obj2d* rc2)
{
    const float rc1Left = rc1->pos.x - rc1->hsize.x;
    const float rc1Right = rc1->pos.x + rc1->hsize.x;
    const float rc1Top = rc1->pos.y - rc1->hsize.y;
    const float rc1Bottom = rc1->pos.y + rc1->hsize.y;

    const float rc2Left = rc2->pos.x-rc2->hsize.x;
    const float rc2Right = rc2->pos.x + rc2->hsize.x;
    const float rc2Top = rc2->pos.y - rc2->hsize.y;
    const float rc2Bottom = rc2->pos.y + rc2->hsize.y;

    if (rc1Left >= rc2Right)return false;
    if (rc1Right <= rc2Left)return false;
    if (rc1Top >= rc2Bottom)return false;
    if (rc1Bottom <= rc2Top)return false;

    return true;
}

// 改定中

/// <summary>
/// 壁とのめり込み判定
/// </summary>
/// <param name="rc1"></param>
/// <param name="rc2"></param>
/// <param name="dir"></param>
/// <returns></returns>
float check(obj2d* rc1, obj2d* rc2, int dir)
{
    switch (dir)
    {
    case DIR::UP:
    {
        const float rc1Top = rc1->pos.y - rc1->hsize.y;
        const float rc2Bottom = rc2->pos.y + rc2->hsize.y;

        return rc2Bottom - rc1Top;
    }
    break;

    case DIR::DOWN:
    {
        const float rc1Bottom = rc1->pos.y + rc1->hsize.y;
        const float rc2Top = rc2->pos.y - rc2->hsize.y;

        return rc2Top - rc1Bottom;
    }
    break;

    case DIR::LEFT:
    {
        const float rc1Left = rc1->pos.x - rc1->hsize.x;
        const float rc2Right = rc2->pos.x + rc2->hsize.x;

        return rc2Right - rc1Left;
    }
    break;

    case DIR::RIGHT:
    {
        const float rc1Right = rc1->pos.x + rc1->hsize.x;
        const float rc2Left = rc2->pos.x - rc2->hsize.x;

        return rc2Left - rc1Right;
    }
    break;
    }
}