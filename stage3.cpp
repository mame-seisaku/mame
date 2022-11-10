#include "all.h"
/*****�ϐ�*****/

stage stage3[STAGE3_MAX];

VECTOR2 speed3;

Sprite* spr3;
Sprite* sprSyoukouki3;


extern VECTOR2 mousePos;


void stage3_init()
{
	stage_state[0] = 0;
}

void stage3_deinit()
{
	safe_delete(spr3);
	safe_delete(sprSyoukouki3);

    music::stop(game_bgm);
}

void stage3_update()
{
    switch (stage_state[3])
    {
    case 0:
        ///// �����ݒ� /////
        player.Init();

        spr3 = sprite_load(L"./Data/Images/stage0.png");
        sprSyoukouki3 = sprite_load(L"./Data/Images/syoukouki2.png");

        ++stage_state[3];
    case 1:
        ///// �p�����[�^�̐ݒ� /////

        for (int i = 0; i < STAGE1_MAX; ++i)
        {
            stage3[i] = {};
        }

        // ��
        stage3[0].pos = { 768,764 };
        stage3[0].hsize = { 768, 64 };
        stage3[0].type = 0;
        stage3[0].exist = true;
        // ����
        stage3[1].pos = { 5,412 };
        stage3[1].hsize = { 5,412 };
        stage3[1].type = 0;
        stage3[1].exist = true;
        // �E��
        stage3[2].pos = { 1531,412 };
        stage3[2].hsize = { 15,412 };
        stage3[2].type = 0;
        stage3[2].exist = true;
        //�G���x�[�^
        stage3[3].position = { 890,510 };
        stage3[3].pos = { 979,650 };
        stage3[3].hsize = { 89, 50 };
        stage3[3].type = 0;
        stage3[3].exist = true;

        music::play(game_bgm, true);

        ++stage_state[3];
    case 2:
        ///// �ʏ펞 /////

        player.Update();

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

        // �}�E�X�ł̜߈ˑ���
        if (mousePos.x > stage3[3].pos.x - 89 && mousePos.y > stage3[3].pos.y - 50 && mousePos.x < stage3[3].pos.x + 89 && mousePos.y < stage3[3].pos.y + 50)
        {
            if (TRG(0) & PAD_L3)
            {
                stage3[3].elec = true;
                player.elec = false;
            }
        }
        if (TRG(0) & PAD_R3)
        {
            stage3[3].elec = false;
            player.elec = true;
        }

        if (STATE(0) & PAD_UP)
        {
            if (!(STATE(0) & PAD_DOWN))
            {
                speed3.y = -PLAYER_MOVE;
            }
        }
        else if (STATE(0) & PAD_DOWN)
        {
            if (!(STATE(0) & PAD_UP))
            {
                speed3.y = PLAYER_MOVE;
            }
        }
        else
        {
            speed3.y = 0;
        }

       
      
            player.pos.y += player.speed.y;
           /* stage3[3].position.y = stage3[3].pos.y-140;*/
        if (stage3[3].elec == true) {
            stage3[3].pos.y += speed3.y;
            stage3[3].position.y = stage3[3].pos.y-140;
        }

        // �㉺�̂߂荞�݃`�F�b�N
        for (int i = 0; i < STAGE0_MAX; ++i)
        {
            if (hitCheck(&player, &stage3[i]))
            {
                // �߂荞�ݑ΍�		// �����蔻��
                float dist;
                if (player.speed.y >= 0)
                    dist = check(&player, &stage3[i], DIR::DOWN);
                else
                    dist = check(&player, &stage3[i], DIR::UP);
                player.pos.y += dist;
                player.speed.y = 0;
            }
            if (hitCheck(&stage3[3], &stage3[0]))
            {
                float dist;
                if (speed3.y >= 0)
                    dist = check(&stage3[3], &stage3[0], DIR::DOWN);
                else
                    dist = check(&stage3[3], &stage3[0], DIR::UP);
                stage3[3].pos.y += dist;
                speed3.y = 0;
                stage3[3].position.y += dist;
            }  
        }

        //�� ���
        if (stage3[3].pos.y < 200) {
            stage3[3].pos.y = 200;
            stage3[3].position.y = 60;
        }

        //����؂�ւ�
            player.pos.x += player.speed.x;
        

        // ���E�̂߂荞�݃`�F�b�N
        for (int i = 0; i < STAGE0_MAX; ++i)
        {
            if (player.elec == true) {
                if (hitCheck(&player, &stage3[i]))
                {
                    // �߂荞�ݑ΍�		// �����蔻��
                    float dist;
                    if (player.speed.x >= 0)
                        dist = check(&player, &stage3[i], DIR::RIGHT);
                    else
                        dist = check(&player, &stage3[i], DIR::LEFT);
                    player.pos.x += dist;
                    player.speed.x = 0;
                }
            }
            if (player.elec == false) {
                if (hitCheck(&player, &stage3[i]))
                {
                    // �߂荞�ݑ΍�		// �����蔻��
                    float dist;
                    if (speed3.x >= 0)
                        dist = check(&player, &stage3[i], DIR::RIGHT);
                    else
                        dist = check(&player, &stage3[i], DIR::LEFT);
                    player.pos.x += dist;
                    speed3.x = 0;
                }
            }
        }





        break;
    }
}

void stage3_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(spr3, 0, 0);

    player.Render();

    for (int i = 0; i < STAGE1_MAX; ++i)
    {
        primitive::rect(stage3[i].pos, stage3[i].hsize * 2, stage3[i].hsize, 0, { 1,0,0,1 });
    }

    // �G���x�[�^
    sprite_render(sprSyoukouki3, stage3[3].position.x, stage3[3].position.y, 1, 1, stage3[3].elec * 178, 0, 177, 177);
}
