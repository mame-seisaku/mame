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
        texSize = { 128,128 };
        pivot = { 64,64 };
        angle = 0;

        ++state;
    case 2:
        ///// �ʏ펞 /////

        // ����.�ړ�����
        Move();

        // �n�ʂ̔���
        checkGround();

        break;
    }
}

/// <summary>
/// �`�揈��
/// </summary>
void Player::Render()
{
    sprite_render(sprPlayer, pos.x, pos.y, scale.x, scale.y, texPos.x, texPos.y, texSize.x, texSize.y, pivot.x, pivot.y, angle);
}

void Player::Move()
{
    if (STATE(0) & PAD_UP)pos.y -= 10;
    if (STATE(0) & PAD_DOWN)pos.y += 10;
    if (STATE(0) & PAD_LEFT)pos.x -= 10;
    if (STATE(0) & PAD_RIGHT)pos.x += 10;

    // �d��
    speed.y += GRAVITY;

    pos += speed;
}

void Player::checkGround()
{
    if (pos.y > 600)
    {
        pos.y = 600;
        speed.y = 0;
    }
}

