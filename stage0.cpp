#include "all.h"

/*****�ϐ�*****/

obj2d stage0[STAGE0_MAX];

Sprite* sprStage0;

extern VECTOR2 mousePos;

void stage0_init()
{
    stage_state[0] = 0;
}

void stage0_deinit()
{
    safe_delete(sprStage0);
}

void stage0_update()
{
    switch (stage_state[0])
    {
    case 0:
        ///// �����ݒ� /////
        sprStage0 = sprite_load(L"./Data/Images/stage0.png");

        ++stage_state[0];
    case 1:
        ///// �p�����[�^�̐ݒ� /////

        stage0[0].pos = { 768,764 };
        stage0[0].hsize = { 768, 64};
        stage0[1].pos = { 585,625 };
        stage0[1].hsize = { 95, 75 };
        stage0[2].pos = { 1430,640 };
        stage0[2].hsize = { 60, 60 };

        ++stage_state[0];
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

        // �㉺�̂߂荞�݃`�F�b�N
        for (int i = 0; i < STAGE0_MAX; ++i)
        {
            if (hitCheck(&player, &stage0[i]))
            {
                // �߂荞�ݑ΍�		// �����蔻��
                float dist;
                if (player.speed.y >= 0)
                    dist = check(&player, &stage0[i], DIR::DOWN);
                else
                    dist = check(&player, &stage0[i], DIR::UP);
                player.pos.y += dist;
                player.speed.y = 0;
            }
        }

        // ���E�̂߂荞�݃`�F�b�N
        for (int i = 0; i < STAGE0_MAX; ++i)
        {
            if (hitCheck(&player, &stage0[i]))
            {
                // �߂荞�ݑ΍�		// �����蔻��
                float dist;
                if (player.speed.x >= 0)
                    dist = check(&player, &stage0[i], DIR::RIGHT);
                else
                    dist = check(&player, &stage0[i], DIR::LEFT);
                player.pos.x += dist;
                player.speed.x = 0;
            }
        } 



        break;
    }
}

void stage0_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(sprStage0, 0, 0);

    // �v���C���[
    primitive::rect(player.pos, player.hsize * 2, player.hsize, 0, { 0,0,1,1 });

    primitive::rect(stage0[0].pos, stage0[0].hsize * 2, stage0[0].hsize, 0, { 1,1,1,1 });
    primitive::rect(stage0[1].pos, stage0[1].hsize * 2, stage0[1].hsize, 0, { 1,0,0,1 });
    primitive::rect(stage0[2].pos, stage0[2].hsize * 2, stage0[2].hsize, 0, { 0,1,0,1 });
}

