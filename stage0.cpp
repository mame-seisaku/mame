#include "all.h"

/*****�ϐ�*****/

stage stage0[STAGE0_MAX];

Sprite* sprStage0;
Sprite* sprStage0Floor;
Sprite* sprBox;

extern VECTOR2 mousePos;

void stage0_init()
{
    stage_state[0] = 0;
}

void stage0_deinit()
{
    player.Dinit();

    safe_delete(sprStage0);
    safe_delete(sprStage0Floor);
    safe_delete(sprBox);
}

void stage0_update()
{
    switch (stage_state[0])
    {
    case 0:
        ///// �����ݒ� /////
        player.Init();
        
        //sprStage0 = sprite_load(L"./Data/Images/stage0.png");
        sprStage0 = sprite_load(L"./Data/Images/04.png");
        sprStage0Floor = sprite_load(L"./Data/Images/03.png");
        sprBox = sprite_load(L"./Data/Images/box.png");

        ++stage_state[0];
    case 1:
        ///// �p�����[�^�̐ݒ� /////

        for (int i = 0; i < STAGE0_MAX; ++i)
        {
            stage0[i] = {};
        }

        // ��
        stage0[0].position = { 0,700 };
        stage0[0].pos = { 768,764 };
        stage0[0].hsize = { 768, 64 };
        stage0[0].type = 3;
        stage0[0].exist = true;
        // �l�p
        stage0[1].position = { 490,523 };
        stage0[1].pos = { 579,612.5f };
        stage0[1].hsize = { 89, 88.5f };
        stage0[1].type = 1;
        stage0[1].exist = true;
        // ��
        stage0[2].pos = { 1430,640 };
        stage0[2].hsize = { 60, 60 };
        stage0[2].type = 2;
        stage0[2].exist = true;
        // ����
        stage0[3].pos = { 5,412 };
        stage0[3].hsize = { 5,412 };
        stage0[3].type = 0;
        stage0[3].exist = true;
        // �A���`
        stage0[4].position = { 70,630 };
        stage0[4].pos = { 105,640 };
        stage0[4].hsize = { 35,10 };
        stage0[4].type = 0;
        stage0[4].exist = true;

        ++stage_state[0];
    case 2:
        ///// �ʏ펞 /////

        player.Update();

        // �}�E�X�J�[�\��
        std::ostringstream oss;                                 // ������X�g���[��
        POINT point;                                            // �ʒu�p�̕ϐ���錾����
        GetCursorPos(&point);                                   // �X�N���[�����W���擾����
        ScreenToClient(window::getHwnd(), &point);              // �N���C�A���g���W�ɕϊ�����
        mousePos.x = (float)(point.x);
        mousePos.y = (float)(point.y);
#ifdef _DEBUG
        oss << "(x=" << point.x << " y=" << point.y << ")";
        SetWindowTextA(window::getHwnd(), oss.str().c_str());   // �^�C�g���o�[�ɂ�\��������
        debug::setString("PossibleStage:%d", PossibleStage);
#endif
        // �}�E�X�ł̜߈ˑ���
        if (mousePos.x > 0 && mousePos.y > 700 && mousePos.x < 1536 && mousePos.y < 824)
        {
            if (TRG(0) & PAD_L3)
            {
                stage0[0].elec = true;
                player.elec = false;
            }
            if (TRG(0) & PAD_R3)
            {
                stage0[0].elec = false;
                player.elec = true;
            }
        }



        // �ʒu�ɃX�s�[�h�𑫂�
        //if (player.moveFlag)
        //{
        player.pos.y += player.speed.y;
        //}
        //else
        //{
        //    player.speed.y = 0;
        //}

        // �㉺�̂߂荞�݃`�F�b�N
        for (int i = 0; i < STAGE0_MAX; ++i)
        {
            if (hitCheck(&player, &stage0[i]))
            {
                // ��
                if (stage0[i].type == 2)
                {
                    // �V�[���؂�ւ�
                    nextScene = SCENE::RESULT;
                    return;
                }

                // �x���g�R���x�A
                if (stage0[i].type == 3 && stage0[i].elec)
                {
                    player.pos.x += 10;
                }

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

        // �ʒu�ɃX�s�[�h�𑫂�
        //if (player.moveFlag)
        //{
        player.pos.x += player.speed.x;
        //}
        //else
        //{
        //    player.speed.x = 0;
        //}

        // ���E�̂߂荞�݃`�F�b�N
        for (int i = 0; i < STAGE0_MAX; ++i)
        {
            if (hitCheck(&player, &stage0[i]))
            {
                // ��
                if (stage0[i].type == 2)
                {
                    // �V�[���؂�ւ�
                    nextScene = SCENE::RESULT;
                    return;
                }

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


        // �l�p�̐F�ݒ�
        for (int i = 0; i < STAGE0_MAX; ++i)
        {
            switch (stage0[i].type)
            {
            case 0:
                stage0[i].color = { 1,1,1,1 };
                break;
            case 1:
                stage0[i].color = { 1,0,0,1 };
                break;
            case 2:
                stage0[i].color = { 0,1,0,1 };
                break;
            case 3:
                stage0[i].color = { 1,1,1,1 };
                break;
            }
        }

        // ���X�N���[��
        if (stage0[0].elec)
        {
            stage0[0].position.x += 10;
            stage0[1].position.x += 10;
            stage0[1].pos.x += 10;
            player.texPos.x = 84;
        }
        else
        {
            player.texPos.x = 0;
        }
        // �͈͊O
        if (stage0[0].position.x > 0)
        {
            stage0[0].position.x = -1536;
        }

        break;
    }
}

void stage0_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(sprStage0, 0, 0);

    // �v���C���[
    player.Render();
    //primitive::rect(player.pos, player.hsize * 2, player.hsize, 0, { 0,0,1,1 });

    // �n�`�`��
    for (int i = 0; i < STAGE0_MAX; ++i)
    {
        primitive::rect(stage0[i].pos, stage0[i].hsize * 2, stage0[i].hsize, 0, { stage0[i].color.x,stage0[i].color.y,stage0[i].color.z,stage0[i].color.w });
    }

    // ��
    sprite_render(sprStage0Floor, stage0[0].position.x, stage0[0].position.y);
    // ��
    sprite_render(sprBox, stage0[1].position.x, stage0[1].position.y);

}

