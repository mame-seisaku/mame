#include "all.h"

/*****�ϐ�*****/

stage stage1[STAGE1_MAX];

VECTOR2 operation[STAGE1_MAX];

Sprite* spr2;

extern VECTOR2 mousePos;


/// <summary>
/// �����ݒ�
/// </summary>
void stage1_init()
{
    stage_state[1] = 0;
}

/// <summary>
/// �I������
/// </summary>
void stage1_deinit()
{
    safe_delete(spr2);
}

/// <summary>
/// �X�V����
/// </summary>
void stage1_update()
{
    switch (stage_state[1])
    {
    case 0:
        ///// �����ݒ� /////
        spr2 = sprite_load(L"./Data/Images/stage0.png");

        ++stage_state[1];
    case 1:
        ///// �p�����[�^�̐ݒ� /////

        for (int i = 0; i < STAGE1_MAX; ++i)
        {
            stage1[i] = {};
        }

        // ��
        stage1[0].pos = { 768,764 };
        stage1[0].hsize = { 768, 64 };
        stage1[0].exist = true;
        // ����
        stage1[1].pos = { 5,412 };
        stage1[1].hsize = { 5,412 };
        stage1[1].exist = true;
        // �E��
        stage1[2].pos = { 1531,412 };
        stage1[2].hsize = { 15,412 };
        stage1[2].exist = true;
        //�I�u�W�F
        stage1[3].pos = { 768,678 };
        stage1[3].hsize = { 50, 22 };
        stage1[3].exist = true;


        ++stage_state[1];
    case 2:
        ///// �ʏ펞 /////

                // �}�E�X�J�[�\��
#ifdef _DEBUG
        std::ostringstream oss;                                 // ������X�g���[��
        POINT point;                                            // �ʒu�p�̕ϐ���錾����
        GetCursorPos(&point);                                   // �X�N���[�����W���擾����
        ScreenToClient(window::getHwnd(), &point);              // �N���C�A���g���W�ɕϊ�����
        mousePos.x = (float)(point.x);
        mousePos.y = (float)(point.y);
        oss << "(x=" << point.x << " y=" << point.y << ")";
        SetWindowTextA(window::getHwnd(), oss.str().c_str());   // �^�C�g���o�[�ɂ�\��������
        debug::setString("PossibleStage:%d", PossibleStage);
#endif

        player.pos.y += player.speed.y;

        // �㉺�̂߂荞�݃`�F�b�N
        for (int i = 0; i < STAGE0_MAX; ++i)
        {
            if (hitCheck(&player, &stage1[i]))
            {
                // �߂荞�ݑ΍�		// �����蔻��
                float dist;
                if (player.speed.y >= 0)
                    dist = check(&player, &stage1[i], DIR::DOWN);
                else
                    dist = check(&player, &stage1[i], DIR::UP);
                player.pos.y += dist;
                player.speed.y = 0;
            }
        }

        player.pos.x += player.speed.x;

        // ���E�̂߂荞�݃`�F�b�N
        for (int i = 0; i < STAGE0_MAX; ++i)
        {
            if (hitCheck(&player, &stage1[i]))
            {
                // �߂荞�ݑ΍�		// �����蔻��
                float dist;
                if (player.speed.x >= 0)
                    dist = check(&player, &stage1[i], DIR::RIGHT);
                else
                    dist = check(&player, &stage1[i], DIR::LEFT);
                player.pos.x += dist;
                player.speed.x = 0;
            }
        }
        if (TRG(0) & PAD_R3)
        {
            if (mousePos.x > 718 && mousePos.y > 656 && mousePos.x < 818 && mousePos.y < 700)
            {
            }
        }

                stage1[3].pos.x = player.pos.x;
        operation[0] = player.pos;

        break;
    }
}

/// <summary>
/// �`�揈��
/// </summary>
void stage1_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(spr2, 0, 0);

    primitive::rect(operation[0], player.hsize * 2, player.hsize, 0, { 0,0,1,1 });
    
    for (int i = 0; i < STAGE1_MAX; ++i)
    {
        primitive::rect(stage1[i].pos, stage1[i].hsize * 2, stage1[i].hsize, 0, { 1,0,0,1 });
    }

}
