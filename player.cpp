#include "all.h"

/// <summary>
/// 初期設定
/// </summary>
void Player::Init()
{
    state = 0;
    timer = 0;
}

/// <summary>
/// 終了処理
/// </summary>
void Player::Dinit()
{
    safe_delete(sprPlayer);
}

/// <summary>
/// 更新処理
/// </summary>
void Player::Update()
{
    switch (state)
    {
    case 0:
        ///// 初期設定 /////
        sprPlayer = sprite_load(L"./Data/Images/player.png");

        ++state;
    case 1:
        ///// パラメータの設定 /////
        pos = { 100,200 };
        scale = { 1,1 };
        texPos = { 0,0 };
        texSize = { 84,84 };
        pivot = { 0,0 };
        angle = 0;
        hsize = { 42,42 };

        ++state;
    case 2:
        ///// 通常時 /////

        // 入力.移動処理
        Move();

        // 地面の判定
        //checkGround();

        break;
    }
}

/// <summary>
/// 描画処理
/// </summary>
void Player::Render()
{
    //sprite_render(sprPlayer, pos.x, pos.y, scale.x, scale.y, texPos.x, texPos.y, texSize.x, texSize.y, pivot.x, pivot.y, angle);
}

void Player::Move()
{
    // 入力移動
    if (STATE(0) & PAD_LEFT)
    {
        if (!(STATE(0) & PAD_RIGHT))
        {
            player.speed.x = -PLAYER_MOVE;
        }
    }
    else if (STATE(0) & PAD_RIGHT)
    {
        if (!(STATE(0) & PAD_LEFT))
        {
            player.speed.x = PLAYER_MOVE;
        }
    }
    else
    {
        player.speed.x = 0;
    }

    // 重力操作
    player.speed.y += GRAVITY;

    // ジャンプ
    if (STATE(0) & PAD_UP)pos.y -= 10;
}

void Player::checkGround()
{
    if (pos.y > 600)
    {
        pos.y = 600;
        speed.y = 0;
    }
}

