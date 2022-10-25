#include "all.h"

/// <summary>
/// �����ݒ�
/// </summary>
void Player::Init()
{
    state = 0;
    timer = 0;
}

/// <summary>
/// �I������
/// </summary>
void Player::Dinit()
{
    safe_delete(sprPlayer);
}

/// <summary>
/// �X�V����
/// </summary>
void Player::Update()
{
    switch (state)
    {
    case 0:
        ///// �����ݒ� /////
        sprPlayer = sprite_load(L"./Data/Images/player.png");

        ++state;
    case 1:
        ///// �p�����[�^�̐ݒ� /////
        pos = { 100,200 };
        scale = { 1,1 };
        texPos = { 0,0 };
        texSize = { 84,84 };
        pivot = { 0,0 };
        angle = 0;
        hsize = { 42,42 };

        ++state;
    case 2:
        ///// �ʏ펞 /////

        // ����.�ړ�����
        Move();

        // �n�ʂ̔���
        //checkGround();

        break;
    }
}

/// <summary>
/// �`�揈��
/// </summary>
void Player::Render()
{
    //sprite_render(sprPlayer, pos.x, pos.y, scale.x, scale.y, texPos.x, texPos.y, texSize.x, texSize.y, pivot.x, pivot.y, angle);
}

void Player::Move()
{
    // ���͈ړ�
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

    // �d�͑���
    player.speed.y += GRAVITY;

    // �W�����v
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

