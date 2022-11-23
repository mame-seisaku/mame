#include "all.h"

/*****�ϐ�*****/

stage stage6[STAGE6_MAX];

VECTOR2 speed6;

extern Sprite* sprSyoukouki;    // ���~�@
extern Sprite* sprBox;          // box
extern Sprite* sprStage0;       // �w�i

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
    safe_delete(sprHelp);

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
        sprBox = sprite_load(L"./Data/Images/boxMove.png");
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
        sprHelp = sprite_load(L"./Data/Images/help.png");

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
        stage6[1].position = { 1315,530 };
        stage6[1].pos = { 1405,610 };
        stage6[1].hsize = { 80, 89 };
        stage6[1].texPos = {};
        stage6[1].texSize = { 178,177 };
        stage6[1].type = 2;
        stage6[1].exist = true;
        stage6[1].open = false;


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
        if (mousePos.x > 1440 && mousePos.y > 0 && mousePos.x < 1536 && mousePos.y < 70)
        {
            if (TRG(0) & PAD_L3)pause = pause ? false : true;
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
        debug::setString("selectStage:%d", selectStage);
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
                speed6.y = 0;
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
            }

            // �ʒu�ɃX�s�[�h�𑫂�         
            player.pos.x += player.speed.x;

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
            }






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
        sprite_render(sprTerrain, 64 * x, 412, 1, 1, 64, 0, 64, 64);
    }

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

    // UI
    sprite_render(sprUI, 30, 30, 1, 1, UI, 0, 105, 64);

    // �|�[�Y���
    if (pause)
    {
        sprite_render(sprWhite, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprPause, 0, 0);
    }
    sprite_render(sprHelp, 0, 0);

    sprite_render(sprMouse, mousePos.x, mousePos.y, 1, 1, 0, 0, 100, 100, 50, 50);
}