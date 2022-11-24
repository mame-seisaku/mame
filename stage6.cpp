#if 1
#include "all.h"

/*****�ϐ�*****/

stage stage6[STAGE6_MAX];

VECTOR2 speed6;

extern Sprite* sprSyoukouki;    // ���~�@
extern Sprite* sprBox;          // box
extern Sprite* sprStage0;       // �w�i
extern Sprite* psrSyoukouki;    // ���~�@
extern Sprite* sprBoxMove;      //������
extern Sprite* sprSwitch;  // �X�C�b�`

void stage6_init()
{
    stage_state[6] = 0;
}

void stage6_deinit()
{
    player.Dinit();

    safe_delete(sprEV);
    safe_delete(sprEvPlayer);
    safe_delete(sprMouse);
    safe_delete(sprTerrain);
    safe_delete(sprPause);
    safe_delete(sprWhite);
    safe_delete(sprStage0);
    safe_delete(sprBox);
    safe_delete(sprSyoukouki);
    safe_delete(sprEV);
    safe_delete(sprBoxMove);
    safe_delete(sprSwitch);

    music::stop(game_bgm);
}

void stage6_update()
{
    switch (stage_state[6])
    {
    case 0:
        ///// �����ݒ� /////
        player.Init();

        sprStage0 = sprite_load(L"./Data/Images/04.png");
        sprBox = sprite_load(L"./Data/Images/box.png");
        sprSyoukouki = sprite_load(L"./Data/Images/syoukouki2.png");
        sprElec = sprite_load(L"./Data/Images/elec.png");
        sprDoor = sprite_load(L"./Data/Images/door.png");
        sprEV = sprite_load(L"./Data/Images/EV.png");
        sprEvPlayer = sprite_load(L"./Data/Images/p.png");
        sprMouse = sprite_load(L"./Data/Images/mouse.png");
        sprTerrain = sprite_load(L"./Data/Images/terrain.png");
        sprPause = sprite_load(L"./Data/Images/pause.png");
        sprWhite = sprite_load(L"./Data/Images/white.png");
        sprEV = sprite_load(L"./Data/Images/EV.png");
        sprBoxMove = sprite_load(L"./Data/Images/boxMove.png");
        sprSwitch = sprite_load(L"./Data/Images/switch.png");

        ++stage_state[6];
    case 1:
        ///// �p�����[�^�[�̐ݒ� /////

        // �|�[�Y
        pause = false;

        // �X�e�[�W
        for (int i = 0; i < STAGE6_MAX; ++i)
        {
            stage6[i] = {};
        }

        // EvPlayer
        //EvPlayer = { stage3[4].position.x, stage3[4].position.y + 100 };

        // type
        // 0 �� ��

         // ��
        stage6[0].pos = { 768,764 };
        stage6[0].hsize = { 768,64 };
        stage6[0].type = 0;
        stage6[0].exist = true;

        // �� 
        stage6[1].position = { 115,143 };
        stage6[1].pos = { 205,223 };
        stage6[1].hsize = { 80, 89 };
        stage6[1].texPos = {};
        stage6[1].texSize = { 178,177 };
        stage6[1].type = 2;
        stage6[1].exist = true;
        stage6[1].open = false;

        // �^�񒆂̃f�Jbox
        stage6[2].position = { 974,523 };
        stage6[2].pos = { 1063,612.5f };
        stage6[2].hsize = { 89, 88.5f };
        stage6[2].type = 7;
        stage6[2].exist = true;

        //���~�@
        stage6[3].position = { 1160,-40 };
        stage6[3].pos = { 1249,100 };
        stage6[3].hsize = { 89, 50 };
        stage6[3].type = 3;
        stage6[3].exist = true;

        //�@������
        stage6[4].pos = { 400,280 };
        stage6[4].position = { stage6[4].pos.x - 44,stage6[4].pos.y - 44 };
        stage6[4].texPos.x = 90;
        stage6[4].hsize = { 44,44 };
        stage6[4].type = 1;
        stage6[4].exist = true;

        // ��̏�
        stage6[5].pos = { 576,344 };
        stage6[5].hsize = { 576,32 };
        stage6[5].type = 0;
        stage6[5].exist = true;

        // �ז��ȕ�
        stage6[6].pos = { 224,550 };
        stage6[6].hsize = { 32,150 };
        stage6[6].type = 4;
        stage6[6].exist = true;
        stage6[6].color.w = 1;

        // �X�C�b�`
        stage6[7].pos = { 350,690 };
        stage6[7].hsize = { 20,10 };
        stage6[7].texPos = {0,64};
        stage6[7].type = 5;
        stage6[7].exist = false;

        // EvPlayer
        EvPlayer = { stage6[1].position.x, stage6[1].position.y + 100 };

        // �h�A�Ō�
        door = {};

        // �d�C
        Elec = {};

        speed6 = {};

        

        music::play(game_bgm, true);


        ++stage_state[6];
    case 2:
        ///// �ʏ펞 /////

        // �V�[���؂�ւ�
        if (door.end)
        {
            player.pos.y = EvPlayer.y - 45;
            EvPlayer.y -= STAGE_MOVE;
        }
        if (EvPlayer.y < -200)
        {
            if (PossibleStage < 7)PossibleStage = 7;
            nextScene = SCENE::RESULT;
            break;
        }

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
#ifdef _DEBUG
        oss << "(x=" << point.x << " y=" << point.y << ")";
        SetWindowTextA(window::getHwnd(), oss.str().c_str());   // �^�C�g���o�[�ɂ�\��������
        debug::setString("mousePos.x:%f,mousePos.y:%f", mousePos.x, mousePos.y);
#endif

        if (!pause)
        {
            player.Update({ 100,500 });

            // ���A�j��
            if (stage6[1].open)
                anime(&stage6[1], 7, 10, false, 0);

            // �N���A����
            if (stage6[1].end && stage6[1].one && !door.close)
            {
                player.clear = true;
                door = stage6[1];
                door.state = 0;
                door.close = true;
            }

            // �N���A����
            if (player.clear)
            {
                player.pos.x = stage6[1].position.x + 71;    // �h�A�̈ʒu�Ɉړ�
                // �d�C��߂�
                player.elec = true;
                for (int i = 0; i < STAGE6_MAX; ++i)
                {
                    stage6[i].elec = false;
                }

                // �����܂�
                anime(&door, 7, 10, false, 0);
            }

            // �}�E�X�ł̜߈ˑ���
#if 0 
            for (int i = 2; i < 5; ++i)
            {
                if (mousePos.x > stage6[i].pos.x - 90 && mousePos.y > stage6[i].pos.y - 50 && mousePos.x < stage6[i].pos.x + 90 && mousePos.y - 50 < stage6[i].pos.y + 110)
                {
                    // �d�C���΂�
                    if (TRG(0) & PAD_L3)
                    {
                        // �v���C���[�ɓd�C�������
                        if (!Elec.exist && player.elec)
                        {
                            SetElecMove();
                            Elec.type = i;
                        }
                    }
                    // �d�C���
                    if (TRG(0) & PAD_R3 && !player.elec)
                    {
                        for (int j = 2; j < 5; ++j)
                        {
                            if (i == j)continue;

                            stage6[j].elec = false;
                        }

                        Elec.exist = false;
                        stage6[i].elec = false;
                        player.elec = true;
                    }
                }
            }
#endif

            // �}�E�X�ł̜߈ˑ���
            //���~�@1
            if (mousePos.x > stage6[3].pos.x - 90 && mousePos.y > stage6[3].pos.y - 50 && mousePos.x < stage6[3].pos.x + 90 && mousePos.y < stage6[3].pos.y + 50)
            {
                if (TRG(0) & PAD_L3)
                {
                    if (!Elec.exist && player.elec)
                    {
                        SetElecMove();
                        Elec.type = 3;
                    }
                }
            }

            if (mousePos.x > stage6[4].pos.x - 42 && mousePos.y > stage6[4].pos.y - 42 && mousePos.x < stage6[4].pos.x + 42 && mousePos.y < stage6[4].pos.y + 42)
            {
                // �d�C���΂�
                if (TRG(0) & PAD_L3)
                {
                    // �v���C���[�ɓd�C�������
                    if (!Elec.exist && player.elec)
                    {
                        SetElecMove();
                        Elec.type = 4;
                    }
                }
            }

            if (TRG(0) & PAD_R3 && !player.elec)
            {
                stage6[3].elec = false;
                stage6[4].elec = false;
                player.elec = true;
            }

            // �d�C�̈ړ��ƁA��������������
            if (Elec.exist) // ���݂�����
            {
                // �ړ�
                Elec.pos.x += Elec.moveVec.x * 2;
                Elec.pos.y += Elec.moveVec.y * 2;


                // �E�������֐i��
                if (Elec.moveVec.x > 0)
                {
                    if (Elec.moveVec.y > 0)
                    {
                        // ��������
                        if (Elec.pos.x >= ElecPos.x && Elec.pos.y >= ElecPos.y)
                        {
                            player.elec = false;    // �v���C���[�̓d�C����
                            Elec.exist = false;
                            stage6[Elec.type].elec = true;
                        }
                    }
                    else
                    {
                        // ��������
                        if (Elec.pos.x >= ElecPos.x)
                        {
                            player.elec = false;    // �v���C���[�̓d�C����
                            Elec.exist = false;
                            stage6[Elec.type].elec = true;
                        }
                    }
                }
                // ���������֐i��
                else
                {
                    if (Elec.moveVec.y > 0)
                    {
                        // ��������
                        if (Elec.pos.x <= ElecPos.x && Elec.pos.y >= ElecPos.y)
                        {
                            player.elec = false;    // �v���C���[�̓d�C����
                            Elec.exist = false;
                            stage6[Elec.type].elec = true;
                        }
                    }
                    else
                    {
                        // ��������
                        if (Elec.pos.x <= ElecPos.x)
                        {
                            player.elec = false;    // �v���C���[�̓d�C����
                            Elec.exist = false;
                            stage6[Elec.type].elec = true;
                        }
                    }
                }
            }

            //�߈ˑ���
            if (STATE(0) & PAD_UP)
            {
                if (!(STATE(0) & PAD_DOWN))
                {
                    speed6.y = -PLAYER_MOVE;
                }
            }
            else if (STATE(0) & PAD_DOWN)
            {
                if (!(STATE(0) & PAD_UP))
                {
                    speed6.y = PLAYER_MOVE;
                }
            }
            else
            {
                if (stage6[3].elec) {
                    speed6.y = 0;
                }
            }
            if (STATE(0) & PAD_LEFT)
            {
                if (!(STATE(0) & PAD_RIGHT))
                {
                    speed6.x = -PLAYER_MOVE;
                }
            }
            else if (STATE(0) & PAD_RIGHT)
            {
                if (!(STATE(0) & PAD_LEFT))
                {
                    speed6.x = PLAYER_MOVE;
                }
            }
            else
            {
                speed6.x = 0;
            }

            // �ʒu�ɃX�s�[�h�𑫂�
            player.pos.y += player.speed.y;

            // �d��

            //���~�@1 �ړ�
            if (stage6[3].elec) {
                stage6[3].pos.y += speed6.y;
                stage6[3].position.y = stage6[3].pos.y - 140;
            }
           

            //�{�b�N�X�ړ�
            if (stage6[4].elec)
            {
         
                stage6[4].pos.y += speed6.y;
            }
            speed6.y += 1.0f;

            // �㉺�̂߂荞�݃`�F�b�N
            for (int i = 0; i < STAGE6_MAX; ++i)
            {
                if (hitCheck(&player, &stage6[i]))
                {
                    // ��
                    if (stage6[i].type == 2)
                    {
                        stage6[i].open = true;
                        continue;
                    }

                    // �߂荞�ݑ΍�		// �����蔻��
                    float dist;
                    if (player.speed.y >= 0)
                        dist = check(&player, &stage6[i], DIR::DOWN);
                    else
                        dist = check(&player, &stage6[i], DIR::UP);
                    player.pos.y += dist;
                    player.speed.y = 0;
                }
                if (hitCheck(&stage6[4], &stage6[i]))
                {
                    if (i == 4)continue;

                    if (stage6[i].type == 2)continue;
                    if (stage6[i].type == 3 && !stage6[i].exist)continue; //���~�@
                    if (stage6[i].type == 7 && !stage6[i].exist)continue; //��
                    if (stage6[i].type == 4 && !stage6[i].exist)continue; //��

                    if (stage6[i].type == 5)    // �X�C�b�`
                    {
                        stage6[i].texPos.x = 64;
                        stage6[6].exist = false;
                        continue;
                    }

                    // �߂荞�ݑ΍�		// �����蔻��
                    float dist;
                    if (speed6.y >= 0)
                        dist = check(&stage6[4], &stage6[i], DIR::DOWN);
                    else
                        dist = check(&stage6[4], &stage6[i], DIR::UP);
                    stage6[4].pos.y += dist;
                    speed6.y = 0;
                }
            }

            // �ʒu�ɃX�s�[�h�𑫂�         
            player.pos.x += player.speed.x;

            if (stage6[4].elec)
            {
                stage6[4].pos.x += speed6.x;
            }

            // ���E�̂߂荞�݃`�F�b�N
            for (int i = 0; i < STAGE6_MAX; ++i)
            {
                if (hitCheck(&player, &stage6[i]))
                {
                    // ��
                    if (stage6[i].type == 2)
                    {
                        stage6[i].open = true;
                        continue;
                    }

                    // �߂荞�ݑ΍�		// �����蔻��
                    float dist;
                    if (player.speed.x >= 0)
                        dist = check(&player, &stage6[i], DIR::RIGHT);
                    else
                        dist = check(&player, &stage6[i], DIR::LEFT);
                    player.pos.x += dist;
                    player.speed.x = 0;
                }

                if (hitCheck(&stage6[4], &stage6[i]))
                {
                    if (i == 4)continue;

                    if (stage6[i].type == 2)continue;   // ��
                    if (stage6[i].type == 3 && !stage6[i].exist)continue; //���~�@
                    if (stage6[i].type == 7 && !stage6[i].exist)continue; //��
                    if (stage6[i].type == 4 )continue; //��

                    if (stage6[i].type == 5)    // �X�C�b�`
                    {
                        stage6[i].texPos.x = 64;
                        stage6[6].exist = false;
                        continue;
                    }

                    // �߂荞�ݑ΍�		// �����蔻��
                    float dist;
                    if (speed6.x >= 0)
                        dist = check(&stage6[4], &stage6[i], DIR::RIGHT);
                    else
                        dist = check(&stage6[4], &stage6[i], DIR::LEFT);
                    stage6[4].pos.x += dist;
                    speed6.x = 0;
                }
            }

           //���@�摜�؂�ւ�
                stage6[4].texPos.x = stage6[4].elec ? 0 : 90;
            




        }
        else
        {
            if (TRG(0) & PAD_L3)
            {
                if (mousePos.x > 550 && mousePos.y > 400 && mousePos.x < 900 && mousePos.y < 460)
                {
                    nextScene = SCENE::RESTART;
                    break;
                }
                else if (mousePos.x > 540 && mousePos.y > 540 && mousePos.x < 910 && mousePos.y < 600)
                {
                    nextScene = SCENE::SELECT;
                    break;
                }
            }
        }

        UI = player.elec ? 0 : 105;

        break;
    }
}

void stage6_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(sprStage0, 0, 0);

    // �n�`�`��
#ifdef _DEBUG
    for (int i = 0; i < STAGE6_MAX; ++i)
    {
        primitive::rect(stage6[i].pos, stage6[i].hsize * 2, stage6[i].hsize, 0, { stage6[i].color.x,stage6[i].color.y,stage6[i].color.z,1 });
    }
#endif
    // ��
    for (int y = 0; y < 2; ++y)
    {
        for (int x = 0; x < 24; ++x)
        {
            sprite_render(sprTerrain, 64 * x, 635 + (64 * (y + 1)), 1, 1, 64, 0, 64, 64);
        }
    }

    for (int x = 0; x < 18; ++x)
    {
        sprite_render(sprTerrain, 64 * x, 312, 1, 1, 64, 0, 64, 64);
    }

    // �ז��ȕ�
    if (stage6[6].exist == true) {
        for (int y = 0; y < 5; ++y)
        {
            sprite_render(sprTerrain, 192, 379 + (64 * y), 1, 1, 128, 0, 64, 64, 0, 0, 0, 1, 1, 1, stage6[6].color.w);
        }
    }

    // �X�C�b�`
    sprite_render(sprSwitch, 318, 635, 1, 1, stage6[7].texPos.x, stage6[7].texPos.y, 64, 64);

    // ���~�@
    sprite_render(sprSyoukouki, stage6[3].position.x, stage6[3].position.y, 1, 1, stage6[3].elec * 178, 0, 177, 177);

    // �G���x�[�^�[
    sprite_render(sprEV, stage6[1].position.x - 5, stage6[1].position.y - 653);

    // ��
    sprite_render(sprDoor, stage6[1].position.x, stage6[1].position.y, 1, 1, stage6[1].texPos.x, stage6[1].texPos.y, stage6[1].texSize.x, stage6[1].texSize.y);

    // �d�C
    if (Elec.exist)
        sprite_render(sprElec, Elec.pos.x, Elec.pos.y, 1, 1, 0, 0, 128, 128, 64, 64);

    player.Render();

    // playerEv
    if (door.end)
        sprite_render(sprEvPlayer, EvPlayer.x + 35, EvPlayer.y);


    // ��
    sprite_render(sprDoor, door.position.x, door.position.y, 1, 1, door.texPos.x, 177, door.texSize.x, door.texSize.y);

    //������
    sprite_render(sprBoxMove, stage6[4].pos.x - 46, stage6[4].pos.y - 46, 1, 1, stage6[4].texPos.x, 0, 90, 90);

    // �f�J��
    sprite_render(sprBox, stage6[2].position.x, stage6[2].position.y);

    // UI
    sprite_render(sprUI, 30, 30, 1, 1, UI, 0, 105, 64);

    // �|�[�Y���
    if (pause)
    {
        sprite_render(sprWhite, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprPause, 0, 0);
    }

    sprite_render(sprMouse, mousePos.x, mousePos.y, 1, 1, 0, 0, 100, 100, 50, 50);
}

#endif