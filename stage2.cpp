#include "all.h"

/*****�ϐ�*****/

VECTOR2 speed2;

stage stage2[STAGE2_MAX];

stage door2;    // doa2

Sprite* sprStage2;  // �w�i
Sprite* sprSwitch;  // �X�C�b�`
Sprite* sprBoxMove; // �������锠
Sprite* sprDoor2;   // �����h�A

extern stage door;
extern Sprite* sprElec; // �d�C
extern Sprite* sprDoor; // �h�A
extern Sprite* sprBox;  // ��

void stage2_init()
{
    stage_state[2] = 0;
}

void stage2_deinit()
{
    player.Dinit();

    safe_delete(sprStage2);
    safe_delete(sprSwitch);
    safe_delete(sprBox);
    safe_delete(sprBoxMove);
    safe_delete(sprDoor2);
    safe_delete(sprEV);
    safe_delete(sprEvPlayer);
    safe_delete(sprMouse);

    safe_delete(sprElec);
    safe_delete(sprDoor);
    safe_delete(sprTerrain);
    safe_delete(sprPause);
    safe_delete(sprWhite);

    music::stop(game_bgm);
}

void stage2_update()
{
    switch (stage_state[2])
    {
    case 0:
        ///// �����ݒ� /////
        player.Init();

        sprStage2 = sprite_load(L"./Data/Images/04.png");
        sprSwitch = sprite_load(L"./Data/Images/switch.png");
        sprBox = sprite_load(L"./Data/Images/box.png");
        sprBoxMove = sprite_load(L"./Data/Images/boxMove.png");
        sprDoor2 = sprite_load(L"./Data/Images/door2.png");
        sprEV = sprite_load(L"./Data/Images/EV.png");
        sprEvPlayer = sprite_load(L"./Data/Images/p.png");
        sprMouse = sprite_load(L"./Data/Images/mouse.png");

        sprElec = sprite_load(L"./Data/Images/elec.png");
        sprDoor = sprite_load(L"./Data/Images/door.png");
        sprTerrain = sprite_load(L"./Data/Images/terrain.png");
        sprPause = sprite_load(L"./Data/Images/pause.png");
        sprWhite = sprite_load(L"./Data/Images/white.png");

        ++stage_state[2];
    case 1:
        ///// �p�����[�^�̐ݒ� /////

        // �|�[�Y
        pause = false;

        for (int i = 0; i < STAGE2_MAX; ++i)
        {
            stage2[i] = {};
        }

        // type
        // 1 ����box
        // 2 ��
        // 3 ������
        // 4 �ז��ȕ�
        // 5 �ԃX�C�b�`
        // 6 player2
        // 7 continue
        // 8 �X�C�b�`
        // 9

        // ��
        stage2[0].pos = { 768,764 };
        stage2[0].hsize = { 768,64 };
        stage2[0].type = 0;
        stage2[0].exist = true;

        // ��
        stage2[1].position = { 1315,274 };
        stage2[1].pos = { 1405,360 };
        stage2[1].hsize = { 80, 89 };
        stage2[1].texPos = {};
        stage2[1].texSize = { 178,177 };
        stage2[1].type = 2;
        stage2[1].exist = true;
        stage2[1].open = false;

        // �E��
        stage2[2].pos = { 1377,575 };
        stage2[2].hsize = { 154,130 };
        stage2[2].type = 7;
        stage2[2].exist = true;

        // �E��box�E
        stage2[3].pos = { 1170,654 };
        stage2[3].position = { stage2[3].pos.x - 44,stage2[3].pos.y - 44 };
        stage2[3].texPos.x = 180;
        stage2[3].hsize = { 44,44 };
        stage2[3].type = 1;
        stage2[3].exist = true;

        // �E��box��
        stage2[4].pos = { 1076,654 };
        stage2[4].position = { stage2[4].pos.x - 44,stage2[4].pos.y - 44 };
        stage2[4].texPos.x = 180;
        stage2[4].hsize = { 44,44 };
        stage2[4].type = 1;
        stage2[4].exist = true;

        // ����box
        stage2[5].pos = { 230,652 };
        stage2[5].position = { stage2[5].pos.x - 44,stage2[5].pos.y - 44 };
        stage2[5].texPos.x = 90;
        stage2[5].hsize = { 44,44 };
        stage2[5].type = 1;
        stage2[5].exist = true;

        // �����box
        stage2[6].pos = { 616,188 };
        stage2[6].position = { stage2[6].pos.x - 44,stage2[6].pos.y - 60 };
        stage2[6].texPos.x = 90;
        stage2[6].hsize = { 44,44 };
        stage2[6].type = 1;
        stage2[6].exist = true;

        // �E���box
        stage2[7].pos = { 935,188 };
        stage2[7].position = { stage2[7].pos.x - 44,stage2[7].pos.y - 54 };
        stage2[7].texPos.x = 90;
        stage2[7].hsize = { 44,44 };
        stage2[7].type = 1;
        stage2[7].exist = true;

        // �^�񒆂̃f�Jbox
        stage2[8].position = { 530,523 };
        stage2[8].pos = { 619,612.5f };
        stage2[8].hsize = { 89, 88.5f };
        stage2[8].type = 7;
        stage2[8].exist = true;

        // �^�񒆂̏�
        stage2[9].pos = { 800,260 };
        stage2[9].hsize = { 250,25 };
        stage2[9].type = 0;
        stage2[9].exist = true;

        // �����͂�
        stage2[10].pos = { 410,260 };
        stage2[10].hsize = { 110,25 };
        stage2[10].type = 3;
        stage2[10].exist = false;
        stage2[10].color = { 1,0,0,1 };

        // �^�񒆂̏���
        stage2[11].pos = { 220,260 };
        stage2[11].hsize = { 50,25 };
        stage2[11].type = 9;
        stage2[11].exist = true;

        // ���㏰
        stage2[12].pos = { 110,392 };
        stage2[12].hsize = { 120,30 };
        stage2[12].type = 9;
        stage2[12].exist = true;

        // �ז��ȕ�
        stage2[13].pos = { 838,103 };
        stage2[13].hsize = { 32,100 };
        stage2[13].type = 4;
        stage2[13].exist = true;
        stage2[13].color.w = 1;

        // �ԃX�C�b�`
        stage2[14].pos = { 830,686 };
        stage2[14].hsize = { 20,10 };
        stage2[14].type = 5;
        stage2[14].exist = true;

        // �X�C�b�`
        stage2[15].pos = { 90,350 };
        stage2[15].hsize = { 20,10 };
        stage2[15].type = 8;
        stage2[15].exist = true;

        // ����
        //stage2[16].pos = { 200,320 };
        //stage2[16].hsize = { 25,80 };
        //stage2[16].type = 9;
        //stage2[16].exist = true;

        // �ז��ȕ�
        stage2[17].pos = { 1028,103 };
        stage2[17].hsize = { 32,100 };
        stage2[17].type = 4;
        stage2[17].exist = true;
        stage2[17].color.w = 1;

        // EvPlayer
        EvPlayer = { stage2[1].position.x, stage2[1].position.y + 100 };

        // �����h�A
        door2 = {};
        door2.texSize = { 128,64 };

        // �h�A�Ō�
        door = {};

        // �d�C
        Elec = {};

        // 
        speed2 = {};

        MouseTexPos = {};

        // BGM
        music::play(game_bgm, true);

        ++stage_state[2];
    case 2:
        ///// �ʏ펞 /////

#ifdef _DEBUG
        debug::setString("player.pos.x:%f", player.pos.x);
        debug::setString("player.pos.y:%f", player.pos.y);
        debug::setString("player.speed.x:%f", player.speed.x);
        debug::setString("player.speed.y:%f", player.speed.y);
#endif // DEBUG


        // �V�[���؂�ւ�
        if (door.end)
        {
            player.pos.y = EvPlayer.y - 45;
            EvPlayer.y -= STAGE_MOVE;
        }
        if (EvPlayer.y < -200)
        {
            if (PossibleStage < 3)PossibleStage = 3;
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
        
        if (!pause)
        {
            // �v���C���[�X�V
            player.Update({100,500});

#ifdef _DEBUG
            oss << "(x=" << point.x << " y=" << point.y << ")";
            SetWindowTextA(window::getHwnd(), oss.str().c_str());   // �^�C�g���o�[�ɂ�\��������
            debug::setString("mousePos.x:%f,mousePos.y:%f", mousePos.x, mousePos.y);
            debug::setString("stage2[6].pos.x:%f", stage2[5].pos.x);
            debug::setString("stage2[6].pos.y:%f", stage2[5].pos.y);
#endif
            
            for (int i = 5; i < 8; ++i)
            {
                if (stage2[i].pos.x - stage2[i].hsize.x < 0)stage2[i].pos.x = stage2[i].hsize.x;
            }

            //// �}�E�X�ł̜߈ˑ���
            //if (mousePos.x > stage2[16].pos.x - 50 && mousePos.y > stage2[16].pos.y - 42 && mousePos.x < stage2[16].pos.x + 50 && mousePos.y < stage2[16].pos.y + 42)
            //{
            //    // �d�C���΂�
            //    if (TRG(0) & PAD_L3)
            //    {
            //        // �v���C���[�ɓd�C�������
            //        if (!Elec.exist && player.elec)
            //        {
            //            SetElecMove();
            //            Elec.type = 16;
            //        }
            //    }
            //    // �d�C���
            //    if (TRG(0) & PAD_R3 && !player.elec)
            //    {
            //        Elec.exist = false;
            //        Elec.type = 16;
            //        stage2[16].elec = false;
            //        player.elec = true;
            //    }
            //}
            
            if (mousePos.x > stage2[5].pos.x - 42 && mousePos.y > stage2[5].pos.y - 42 && mousePos.x < stage2[5].pos.x + 42 && mousePos.y < stage2[5].pos.y + 42||
                mousePos.x > stage2[6].pos.x - 42 && mousePos.y > stage2[6].pos.y - 42 && mousePos.x < stage2[6].pos.x + 42 && mousePos.y < stage2[6].pos.y + 42||
                mousePos.x > stage2[7].pos.x - 42 && mousePos.y > stage2[7].pos.y - 42 && mousePos.x < stage2[7].pos.x + 42 && mousePos.y < stage2[7].pos.y + 42)
            {
                MouseTexPos.x = 100;
            }
            else
            {
                MouseTexPos.x = 0;
            }
            
            // ����box
            for (int i = 5; i < 8; ++i)
            {
                if (mousePos.x > stage2[i].pos.x - 42 && mousePos.y > stage2[i].pos.y - 42 && mousePos.x < stage2[i].pos.x + 42 && mousePos.y < stage2[i].pos.y + 42)
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
                        // �d�C�����Ă邩
                        for (int j = 5; j < 8; ++j)
                        {
                            if (i == j)continue;

                            stage2[j].elec = false;
                        }

                        Elec.exist = false;
                        Elec.type = i;
                        stage2[i].elec = false;
                        player.elec = true;
                    }
                }
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
                            stage2[Elec.type].elec = true;
                        }
                    }
                    else
                    {
                        // ��������
                        if (Elec.pos.x >= ElecPos.x)
                        {
                            player.elec = false;    // �v���C���[�̓d�C����
                            Elec.exist = false;
                            stage2[Elec.type].elec = true;
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
                            stage2[Elec.type].elec = true;
                        }
                    }
                    else
                    {
                        // ��������
                        if (Elec.pos.x <= ElecPos.x)
                        {
                            player.elec = false;    // �v���C���[�̓d�C����
                            Elec.exist = false;
                            stage2[Elec.type].elec = true;
                        }
                    }
                }
            }

            // �߈˕��̈ړ�
            if (STATE(0) & PAD_LEFT)
            {
                if (!(STATE(0) & PAD_RIGHT))
                {
                    speed2.x = -5;
                }
            }
            else if (STATE(0) & PAD_RIGHT)
            {
                if (!(STATE(0) & PAD_LEFT))
                {
                    speed2.x = 5;
                }
            }
            else
            {
                speed2.x = 0;
            }


            // �����͂�
            if (door2.open)anime(&door2, 10, 10, false, 0);
            if (door2.end)stage2[10].exist = true;


            // ���A�j��
            if (stage2[1].open)
                anime(&stage2[1], 7, 10, false, 0);

            // �N���A����
            if (stage2[1].end && stage2[1].one && !door.close)
            {
                player.clear = true;
                door = stage2[1];
                door.state = 0;
                door.close = true;
            }

            if (player.clear)
            {
                player.pos.x = stage2[1].position.x + 71;    // �h�A�̈ʒu�Ɉړ�
                // �d�C��߂�
                player.elec = true;
                for (int i = 0; i < STAGE2_MAX; ++i)
                {
                    stage2[i].elec = false;
                }

                // �����܂�
                anime(&door, 7, 10, false, 0);
            }

            // �}�E�X�ł̜߈ˑ���

            // �d�C�̈ړ��ƁA��������������

            // �ʒu�ɃX�s�[�h�𑫂�
            player.pos.y += player.speed.y;

            // �d��
            speed2.y += 1.0f;
            //if (speed2.y > 10.0f)speed2.y = 10.0f;
            
            for (int i = 5; i < 8; ++i)
            {
                stage2[i].pos.y += 12;
            }


            // �㉺�̂߂肱�݃`�F�b�N
            for (int i = 0; i < STAGE2_MAX; ++i)
            {
                for (int j = 5; j < 8; ++j)
                {
                    if (hitCheck(&stage2[j], &stage2[i]))
                    {
                        if (i == j)continue;
                        if (i >= 5 && i < 8)continue;

                        if (stage2[i].type == 2)continue;   // ��
                        if (stage2[i].type == 3 && !stage2[i].exist)continue;   // �����͂�
                        if (stage2[i].type == 4)continue;   // ��
                        if (stage2[i].type == 5)continue;   // �ԃX�C�b�`
                        if (stage2[i].type == 7)continue;   // �֌W�Ȃ�
                        
                        if (stage2[i].type == 8)    // �X�C�b�`
                        {
                            stage2[i].texPos.x = 64;
                            stage2[13].exist = false;
                            stage2[17].exist = false;
                            continue;
                        }

                        // �߂荞�ݑ΍�		// �����蔻��
                        float dist;
                        if (speed2.y >= 0)
                            dist = check(&stage2[j], &stage2[i], DIR::DOWN);
                        else
                            dist = check(&stage2[j], &stage2[i], DIR::UP);
                        stage2[j].pos.y += dist;
                        speed2.y = 0;
                    }
                }

                if (hitCheck(&player, &stage2[i]))
                {
                    // ��
                    if (stage2[i].type == 2)
                    {
                        stage2[i].open = true;
                        continue;
                    }

                    // kakehasi
                    if (stage2[i].type == 3)
                    {
                        if (!door2.open)continue;   // 
                    }

                    // �X�C�b�`
                    if (stage2[i].type == 5)
                    {
                        if (i == 14)door2.open = true;
                        stage2[i].texPos.x = 64;
                        continue;
                    }

                    if (stage2[i].type == 9)// �֌W�Ȃ�
                    {
                        player.speed.y = -0.1;
                    }

                    // �߂荞�ݑ΍�		// �����蔻��
                    float dist;
                    if (player.speed.y >= 0)
                        dist = check(&player, &stage2[i], DIR::DOWN);
                    else
                        dist = check(&player, &stage2[i], DIR::UP);
                    player.pos.y += dist;
                    player.speed.y = 0;
                }
            }

            // x
            for (int i = 5; i < 8; ++i)
            {
                if (stage2[i].elec)
                {
                    stage2[i].pos.x += speed2.x;
                }
            }

            // �ʒu�ɃX�s�[�h�𑫂�         
            player.pos.x += player.speed.x;

            // ���E�̂߂荞�݃`�F�b�N
            for (int i = 0; i < STAGE2_MAX; ++i)
            {
                for (int j = 5; j < 8; ++j)
                {
                    if (hitCheck(&stage2[j], &stage2[i]))
                    {
                        if (i == j)continue;

                        if (stage2[i].type == 2)continue;   // ��
                        if (stage2[i].type == 3 && !stage2[i].exist)continue;   // �����͂�
                        if (stage2[i].type == 4 && !stage2[i].exist)continue;   // ��
                        if (stage2[i].type == 5)continue;   // �ԃX�C�b�`
                        if (stage2[i].type == 8)    // �X�C�b�`
                        {
                            stage2[i].texPos.x = 64;
                            stage2[13].exist = false;
                            stage2[17].exist = false;
                            continue;
                        }

                        // �߂荞�ݑ΍�		// �����蔻��
                        float dist;
                        if (speed2.x >= 0)
                            dist = check(&stage2[j], &stage2[i], DIR::RIGHT);
                        else
                            dist = check(&stage2[j], &stage2[i], DIR::LEFT);
                        stage2[j].pos.x += dist;
                        speed2.x = 0;
                    }
                }

                if (hitCheck(&player, &stage2[i]))
                {
                    // ��
                    if (stage2[i].type == 2)
                    {
                        stage2[i].open = true;
                        continue;
                    }

                    // kakehasi
                    if (stage2[i].type == 3)
                    {
                        if (!door2.open)continue;   // 
                    }

                    // �X�C�b�`
                    if (stage2[i].type == 5)
                    {
                        if (i == 14)door2.open = true;
                        stage2[i].texPos.x = 64;
                        continue;
                    }

                    if (stage2[i].type == 9)continue;   // �֌W�Ȃ�

                    // �߂荞�ݑ΍�		// �����蔻��
                    float dist;
                    if (player.speed.x >= 0)
                        dist = check(&player, &stage2[i], DIR::RIGHT);
                    else
                        dist = check(&player, &stage2[i], DIR::LEFT);
                    player.pos.x += dist;
                    player.speed.x = 0;
                }
            }

            for (int i = 5; i < 8; ++i)
            {
                stage2[i].texPos.x = stage2[i].elec ? 0 : 90;
            }


            if (!stage2[13].exist)++stage2[13].timer; // �_�ŗp�^�C�}�[
            if (stage2[13].timer / 10 == 1 && stage2[13].counter < 7)
            {
                stage2[13].color.w = stage2[13].color.w == 0 ? 1 : 0;
                stage2[17].color.w = stage2[17].color.w == 0 ? 1 : 0;

                ++stage2[13].counter;
                stage2[13].timer = 0;
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

        break;
    }
}

void stage2_render()
{
    GameLib::clear(1, 1, 1);

    // �w�i
    sprite_render(sprStage2, 0, 0);

    // �n�`�`��
#ifdef _DEBUG
    for (int i = 0; i < STAGE2_MAX; ++i)
    {
        primitive::rect(stage2[i].pos, stage2[i].hsize * 2, stage2[i].hsize, 0, { stage2[i].color.x,stage2[i].color.y,stage2[i].color.z,1 });
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
    // �E���W�܂�
    for (int y = 0; y < 4; ++y)
    {
        for (int x = 0; x < 5; ++x)
        {
            sprite_render(sprTerrain, 1216+(64*x), 379 + (64 * (y + 1)), 1, 1, 64, 0, 64, 64);
        }
    }
    // �^�񒆏�
    for (int x = 0; x < 8; ++x)
    {
        sprite_render(sprTerrain, 550 + (64 * x), 234, 1, 1, 64, 0, 64, 64);
    }
    //// �^�񒆂����͂�
    //for (int x = 0; x < 4; ++x)
    //{
    //    sprite_render(sprTerrain, 294 + (64 * x), 234, 1, 1, 128, 0, 64, 64, 0, 0, 0, 1, 1, 1, 0.3f);
    //}
    sprite_render(sprTerrain, 230, 234, 1, 1, 64, 0, 64, 64);
    sprite_render(sprTerrain, 166, 234, 1, 1, 64, 0, 64, 64);
    sprite_render(sprTerrain, 166, 298, 1, 1, 64, 0, 64, 64);
    // �^�񒆍���
    for (int x = 0; x < 4; ++x)
    {
        sprite_render(sprTerrain, -26 + (64 * x), 362, 1, 1, 0, 0, 64, 64);
    }
    // �ז��ȕ�
    for (int y = 0; y < 4; ++y)
    {
        sprite_render(sprTerrain, 806, -22 + (64 * y), 1, 1, 128, 0, 64, 64, 0, 0, 0, 1, 1, 1, stage2[13].color.w);
        sprite_render(sprTerrain, 998, -22 + (64 * y), 1, 1, 128, 0, 64, 64, 0, 0, 0, 1, 1, 1, stage2[17].color.w);
    }

    // �X�C�b�`
    sprite_render(sprSwitch, 800, 635, 1, 1, stage2[14].texPos.x, 0, 64, 64);
    sprite_render(sprSwitch, 60, 298, 1, 1, stage2[15].texPos.x, 64, 64, 64);

    // ������
    for (int i = 3; i < 8; ++i)
    {
        sprite_render(sprBoxMove, stage2[i].pos.x-46, stage2[i].pos.y-46, 1, 1, stage2[i].texPos.x, 0, 90, 90);
    }
    
    // �f�J��
    sprite_render(sprBox, stage2[8].position.x, stage2[8].position.y);

    // ������
    sprite_render(sprDoor2, 290, 235, 1, 1, door2.texPos.x, 0, 128, 64);
    sprite_render(sprDoor2, 550, 235, -1, 1, door2.texPos.x, 0, 128, 64);

    // �G���x�[�^�[
    sprite_render(sprEV, stage2[1].position.x - 5, stage2[1].position.y - 653);

    // ��
    sprite_render(sprDoor, stage2[1].position.x, stage2[1].position.y, 1, 1, stage2[1].texPos.x, stage2[1].texPos.y, stage2[1].texSize.x, stage2[1].texSize.y);

    // �d�C
    if (Elec.exist)
        sprite_render(sprElec, Elec.pos.x, Elec.pos.y, 1, 1, 0, 0, 128, 128, 64, 64);

    // player2
    //sprite_render(sprPlayer2, stage2[16].pos.x, stage2[16].pos.y, 1, 1, 0, 0, stage2[16].texSize.x, stage2[16].texSize.y, stage2[16].pivot.x, stage2[16].pivot.y);

    player.Render();
    //primitive::rect(player.pos, player.hsize * 2, player.hsize, 0, { 0,0,1,1 });

    // playerEv
    if (door.end)
        sprite_render(sprEvPlayer, EvPlayer.x + 35, EvPlayer.y);

    // ��
    sprite_render(sprDoor, door.position.x, door.position.y, 1, 1, door.texPos.x, 177, door.texSize.x, door.texSize.y);

    // �|�[�Y���
    if (pause)
    {
        sprite_render(sprWhite, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprPause, 0, 0);
    }

    // �}�E�X�J�[�\��
    sprite_render(sprMouse, mousePos.x, mousePos.y, 1, 1, MouseTexPos.x, MouseTexPos.y, 100, 100, 50, 50);
}
