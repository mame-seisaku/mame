#include "all.h"

void stage4_init()
{
    stage_state[4] = 0;
}

void stage4_deinit()
{
    player.Dinit();

    music::stop(game_bgm);
}

void stage4_update()
{
    switch (stage_state[4])
    {
    case 0:
        ///// �����ݒ� /////
        player.Init();

        ++stage_state[4];
    case 1:
        ///// �p�����[�^�[�̐ݒ� /////
        ++stage_state[4];
    case 2:
        ///// �ʏ펞 /////

        // �|�[�Y  F
        if (TRG(0) & PAD_TRG4)
        {
            pause = pause ? false : true;
        }

        // �}�E�X�J�[�\��
        std::ostringstream oss;                                 // ������X�g���[��
        POINT point;                                            // �ʒu�p�̕ϐ���錾����
        GetCursorPos(&point);                                   // �X�N���[�����W���擾����
        ScreenToClient(window::getHwnd(), &point);              // �N���C�A���g���W�ɕϊ�����
        mousePos.x = (float)(point.x);
        mousePos.y = (float)(point.y);

        if (!pause)
        {
            player.Update({ 100,500 });
        }

        break;
    }
}

void stage4_render()
{
    GameLib::clear(1, 1, 1);
}
