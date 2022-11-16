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
void Player::Update(VECTOR2 Pos)
{
    switch (state)
    {
    case 0:
        ///// 初期設定 /////
        //sprPlayer = sprite_load(L"./Data/Images/player.png");
        sprPlayer = sprite_load(L"./Data/Images/player1.png");

        ++state;
    case 1:
        ///// パラメータの設定 /////
        pos = { Pos.x,Pos.y };
        //pos = { 100,200 };
        scale = { 1,1 };
        texPos = { 0,0 };
        texSize = { 84,100 };
        pivot = { 42,50 };
        angle = 0;
        hsize = { 42,50 };
        elec = true;
        clear = false;

        ++state;
    case 2:
        ///// 通常時 /////

        // 入力.移動処理
        if(!clear)
            Move();

        if (pos.x < 0 + pivot.x)pos.x = pivot.x;
        if (pos.x > 1536 - pivot.x)pos.x = 1536 - pivot.x;

        // 地面の判定
        //checkGround();

        player.texPos.x = player.elec ? 0 : 84;


        break;
    }
}

/// <summary>
/// 描画処理
/// </summary>
void Player::Render()
{
    sprite_render(sprPlayer, pos.x, pos.y, scale.x, scale.y, texPos.x, texPos.y, texSize.x, texSize.y, pivot.x, pivot.y, angle);
}

void Player::Move()
{
    // 入力移動
    if (elec)   // プレイヤーの電気があったら動ける
    {
        // ジャンプ
        if (STATE(0) & PAD_TRG1)pos.y-= 15;
    
        if (STATE(0) & PAD_LEFT)
        {
            if (!(STATE(0) & PAD_RIGHT))
            {
                speed.x = -PLAYER_MOVE;
            }
        }
        else if (STATE(0) & PAD_RIGHT)
        {
            if (!(STATE(0) & PAD_LEFT))
            {
                speed.x = PLAYER_MOVE;
            }
        }
        else
        {
            speed.x = 0;
        }
       
    }
    else
    {
        speed.x = 0;
    }

    

    // 重力操作
    speed.y += GRAVITY;

}

void Player::checkGround()
{
    if (pos.y > 600)
    {
        pos.y = 600;
        speed.y = 0;
    }
}

