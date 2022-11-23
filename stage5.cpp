#include "all.h"

/*****�ϐ�*****/

stage stage5[STAGE5_MAX];

extern stage door2;    // doa2

VECTOR2 speed5;

extern float Gangle; // �M�A

extern Sprite* sprSyoukouki;    // ���~�@
extern Sprite* sprBox;          // box
extern Sprite* sprStage0;       // �w�i
extern Sprite* sprBelt;         // �x���g����
extern Sprite* sprGear;         // �M�A
extern Sprite* sprBoxMove;      // �������锠
extern Sprite* sprDoor2;        // �����h�A
extern Sprite* sprTrolley;      // �g���b�R
extern Sprite* sprSwitch;       // �X�C�b�`

void stage5_init()
{
    stage_state[5] = 0;
}

void stage5_deinit()
{
    player.Dinit();

    safe_delete(sprSyoukouki);
    safe_delete(sprBox);
    safe_delete(sprStage0);
    safe_delete(sprBelt);
    safe_delete(sprGear);
    safe_delete(sprBoxMove);
    safe_delete(sprDoor2);
    safe_delete(sprTrolley);
    safe_delete(sprSwitch);

    safe_delete(sprUI);
    safe_delete(sprElec);
    safe_delete(sprDoor);
    safe_delete(sprEV);
    safe_delete(sprEvPlayer);
    safe_delete(sprMouse);
    safe_delete(sprTerrain);
    safe_delete(sprPause);
    safe_delete(sprWhite);


    music::stop(game_bgm);
}

void stage5_update()
{
    switch (stage_state[5])
    {
    case 0:
        ///// �����ݒ� /////
        player.Init();

        sprSyoukouki = sprite_load(L"./Data/Images/syoukouki2.png");
        sprStage0 = sprite_load(L"./Data/Images/04.png");
        sprBox = sprite_load(L"./Data/Images/boxMove.png");
        sprBelt = sprite_load(L"./Data/Images/Belt.png");
        sprGear = sprite_load(L"./Data/Images/gear.png");
        sprBoxMove = sprite_load(L"./Data/Images/boxMove.png");
        sprDoor2 = sprite_load(L"./Data/Images/door2.png");
        sprTrolley = sprite_load(L"./Data/Images/trolley.png");
        sprSwitch = sprite_load(L"./Data/Images/switch.png");

        sprUI = sprite_load(L"./Data/Images/UI.png");
        sprElec = sprite_load(L"./Data/Images/elec.png");
        sprDoor = sprite_load(L"./Data/Images/door.png");
        sprEV = sprite_load(L"./Data/Images/EV.png");
        sprEvPlayer = sprite_load(L"./Data/Images/p.png");
        sprMouse = sprite_load(L"./Data/Images/mouse.png");
        sprTerrain = sprite_load(L"./Data/Images/terrain.png");
        sprPause = sprite_load(L"./Data/Images/pause.png");
        sprWhite = sprite_load(L"./Data/Images/white.png");

        ++stage_state[5];
    case 1:
        ///// �p�����[�^�[�̐ݒ� /////

        // �|�[�Y
        pause = false;

        // �X�e�[�W
        for (int i = 0; i < STAGE5_MAX; ++i)
        {
            stage5[i] = {};
        }

        // type
        // 0 ��
        // 1 �x���g�R���x�A�[
        // 2 ��
        // 3 ���~�@ ����
        // 4 ���~�@ �悱
        // 5 �����h�A
        // 6 �����
        // 7 �X�C�b�`
        
        // �x���g�R���x�A
        stage5[0].position = { 0,0 };
        stage5[0].pos = { 768,764 };
        stage5[0].hsize = { 768, 64 };
        stage5[0].type = 1;
        stage5[0].exist = true;

        // �� 
        stage5[1].position = { 50,460 };
        stage5[1].pos = { stage5[1].position.x + 90,stage5[1].position.y + 80 };
        stage5[1].hsize = { 80, 89 };
        stage5[1].texPos = {};
        stage5[1].texSize = { 178,177 };
        stage5[1].type = 2;
        stage5[1].exist = true;
        stage5[1].open = false;

        // �����䂩
        stage5[2].pos = { 160,728 };
        stage5[2].hsize = { 160,96 };
        stage5[2].type = 0;
        stage5[2].exist = true;

        // �^�񒆕ǂ悱
        stage5[3].pos = { 720,310 };
        stage5[3].hsize = { 380,32 };
        stage5[3].type = 0;
        stage5[3].exist = true;

        // �^�񒆕ǂ���
        stage5[4].pos = { 385,180 };
        stage5[4].hsize = { 45,180 };
        stage5[4].type = 0;
        stage5[4].exist = true;

        // �����h�A
        stage5[5].pos = { 1222,303 };
        stage5[5].hsize = { 128,25 };
        stage5[5].type = 5;
        stage5[5].exist = true;
        stage5[5].color = { 1,0,0,1 };

        // �E��
        stage5[6].pos = { 1443,310 };
        stage5[6].hsize = { 93,32 };
        stage5[6].type = 0;
        stage5[6].exist = true;

        // ���~�@ ��
        stage5[7].position = { 400,530 };
        stage5[7].pos = { stage5[7].position.x + 89,stage5[7].position.y + 140 };
        stage5[7].hsize = { 89, 50 };
        stage5[7].type = 4;
        stage5[7].exist = true;

        // ���~�@ �^��
        stage5[8].position = { 700,400 };
        stage5[8].pos = { stage5[8].position.x + 89,stage5[8].position.y + 140 };
        stage5[8].hsize = { 89, 50 };
        stage5[8].type = 4;
        stage5[8].exist = true;

        // ���~�@ �E
        stage5[9].position = { 1200,540 };
        stage5[9].pos = { stage5[9].position.x + 89,stage5[9].position.y + 140 };
        stage5[9].hsize = { 89, 50 };
        stage5[9].type = 3;
        stage5[9].exist = true;

        //�g���b�R
        stage5[10].position = { 600,100 };
        stage5[10].pos = { stage5[10].position.x + 87,stage5[10].position.y + 124 };
        stage5[10].hsize = { 90, 50 };
        stage5[10].type = 0;
        stage5[10].exist = true;

        // �E���ĕ�
        stage5[11].pos = { 1066,170 };
        stage5[11].hsize = { 32,170 };
        stage5[11].type = 6;
        stage5[11].exist = true;

        // �X�C�b�`
        stage5[12].pos = { 1445,270 };
        stage5[12].hsize = { 20,10 };
        stage5[12].type = 7;
        stage5[12].exist = true;

        // EvPlayer
        EvPlayer = { stage5[1].position.x, stage5[1].position.y + 100 };

        // �����h�A
        door2 = {};
        door2.texSize = { 128,64 };

        // �h�A�Ō�
        door = {};

        // �d�C
        Elec = {};

        Gangle = 0;

        music::play(game_bgm, true);


        ++stage_state[5];
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
            if (PossibleStage < 6)PossibleStage = 6;
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
            player.Update({ 535,160 });

            // �M�A��]
            Gangle += ToRadian(10);
            stage5[0].position.x += 10;
            // �͈͊O
            if (stage5[0].position.x > 0)
            {        
                stage5[0].position.x = -1536;
            }

            // �����͂�
            if (door2.open)anime(&door2, 10, 10, false, 0);
            if (door2.end)stage5[5].exist = false;

            // ���A�j��
            if (stage5[1].open)
                anime(&stage5[1], 7, 10, false, 0);

            // �N���A����
            if (stage5[1].end && stage5[1].one && !door.close)
            {
                player.clear = true;
                door = stage5[1];
                door.state = 0;
                door.close = true;
            }

            // �N���A����
            if (player.clear)
            {
                player.pos.x = stage5[1].position.x + 71;    // �h�A�̈ʒu�Ɉړ�
                // �d�C��߂�
                player.elec = true;
                for (int i = 0; i < STAGE5_MAX; ++i)
                {
                    stage5[i].elec = false;
                }

                // �����܂�
                anime(&door, 7, 10, false, 0);
            }

            // �}�E�X�ł̜߈ˑ���
            if (mousePos.x > stage5[10].pos.x - 90 && mousePos.y > stage5[10].pos.y - 50 && mousePos.x < stage5[10].pos.x + 90 && mousePos.y - 50 < stage5[10].pos.y + 110)
            {
                // �d�C���΂�
                if (TRG(0) & PAD_L3)
                {
                    // �v���C���[�ɓd�C�������
                    if (!Elec.exist && player.elec)
                    {
                        SetElecMove();
                        Elec.type = 10;
                    }
                }
                // �d�C���
                if (TRG(0) & PAD_R3 && !player.elec)
                {
                    Elec.exist = false;
                    stage5[10].elec = false;
                    player.elec = true;
                }
            }

            for (int i = 7; i < 10; ++i)
            {
                if (mousePos.x > stage5[i].pos.x - 90 && mousePos.y > stage5[i].pos.y - 50 && mousePos.x < stage5[i].pos.x + 90 && mousePos.y - 50 < stage5[i].pos.y + 110)
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
                        for (int j = 7; j < 10; ++j)
                        {
                            if (i == j)continue;

                            stage5[j].elec = false;
                        }

                        Elec.exist = false;
                        stage5[i].elec = false;
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
                            stage5[Elec.type].elec = true;
                        }
                    }
                    else
                    {
                        // ��������
                        if (Elec.pos.x >= ElecPos.x)
                        {
                            player.elec = false;    // �v���C���[�̓d�C����
                            Elec.exist = false;
                            stage5[Elec.type].elec = true;
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
                            stage5[Elec.type].elec = true;
                        }
                    }
                    else
                    {
                        // ��������
                        if (Elec.pos.x <= ElecPos.x)
                        {
                            player.elec = false;    // �v���C���[�̓d�C����
                            Elec.exist = false;
                            stage5[Elec.type].elec = true;
                        }
                    }
                }
            }

            if (STATE(0) & PAD_UP)
            {
                if (!(STATE(0) & PAD_DOWN))
                {
                    speed5.y = -PLAYER_MOVE;
                }
            }
            else if (STATE(0) & PAD_DOWN)
            {
                if (!(STATE(0) & PAD_UP))
                {
                    speed5.y = PLAYER_MOVE;
                }
            }
            else
            {
                speed5.y = 0;
            }
            if (STATE(0) & PAD_LEFT)
            {
                if (!(STATE(0) & PAD_RIGHT))
                {
                    speed5.x = -PLAYER_MOVE;
                }
            }
            else if (STATE(0) & PAD_RIGHT)
            {
                if (!(STATE(0) & PAD_LEFT))
                {
                    speed5.x = PLAYER_MOVE;
                }
            }
            else
            {
                speed5.x = 0;
            }

            // �g���b�R����
            if (stage5[10].elec)
            {
                stage5[10].pos.x += speed5.x;
                stage5[10].position.x += speed5.x;

                if (stage5[10].position.x < 500)
                {          
                    stage5[10].position.x = 500;
                    stage5[10].pos.x = stage5[10].position.x + 87;
                }          
                if (stage5[10].position.x > 900)
                {          
                    stage5[10].position.x = 900;
                    stage5[10].pos.x = stage5[10].position.x + 87;
                }
            }

            // ���~�@����
            for (int i = 7; i < 10; ++i)
            {
                if (stage5[i].elec)
                {
                    // y
                    if (i == 9)
                    {
                        stage5[i].pos.y += speed5.y;
                        stage5[i].position.y += speed5.y;

                        if (stage5[i].position.y < 300)
                        {
                            stage5[i].position.y = 300;
                            stage5[i].pos.y = stage5[i].position.y + 140;
                        }
                        if (stage5[i].position.y > 540)
                        {
                            stage5[i].position.y = 540;
                            stage5[i].pos.y = stage5[i].position.y + 140;
                        }

                        continue;
                    }

                    // x
                    stage5[i].pos.x += speed5.x;
                    stage5[i].position.x += speed5.x;

                    if (i == 7)
                    {

                        if (stage5[i].position.x < 400)
                        {
                            stage5[i].position.x = 400;
                            stage5[i].pos.x = stage5[i].position.x + 89;
                        }
                        if (stage5[i].position.x > 600)
                        {
                            stage5[i].position.x = 600;
                            stage5[i].pos.x = stage5[i].position.x + 89;
                        }

                        
                    }

                    if (i == 8)
                    {
                        if (stage5[i].position.x < 700)
                        {
                            stage5[i].position.x = 700;
                            stage5[i].pos.x = stage5[i].position.x + 89;
                        }
                        if (stage5[i].position.x > 1000)
                        {
                            stage5[i].position.x = 1000;
                            stage5[i].pos.x = stage5[i].position.x + 89;
                        }
                    }
                }
            }

            // �g���b�R�ƕǂ̔���
            if (stage5[11].exist)
            {
                if (hitCheck(&stage5[10], &stage5[11]))
                {
                    stage5[11].exist = false;
                }
            }

            // �ʒu�ɃX�s�[�h�𑫂�
            player.pos.y += player.speed.y;

            // �㉺�̂߂荞�݃`�F�b�N
            for (int i = 0; i < STAGE5_MAX; ++i)
            {
                if (hitCheck(&player, &stage5[i]))
                {
                    // �x���g�R���x�A
                    if (stage5[i].type == 1)
                    {
                        player.pos.x += +20;
                    }


                    // ��
                    if (stage5[i].type == 2)
                    {
                        stage5[i].open = true;
                        continue;
                    }

                    // �����͂�
                    if (stage5[i].type == 5 && !stage5[i].exist)continue;   
                    
                    // �����
                    if (stage5[i].type == 6 && !stage5[i].exist)continue;  

                    // �X�C�b�`
                    if (stage5[i].type == 7)
                    {
                        stage5[i].texPos.x = 64;
                        stage5[5].exist = false;
                        door2.open = true;
                        continue;
                    }

                    // �߂荞�ݑ΍�		// �����蔻��
                    float dist;
                    if (player.speed.y >= 0)
                        dist = check(&player, &stage5[i], DIR::DOWN);
                    else
                        dist = check(&player, &stage5[i], DIR::UP);
                    player.pos.y += dist;
                    player.speed.y = 0;
                }
            }

            // �ʒu�ɃX�s�[�h�𑫂�         
            player.pos.x += player.speed.x;

            // ���E�̂߂荞�݃`�F�b�N
            for (int i = 0; i < STAGE5_MAX; ++i)
            {
                if (hitCheck(&player, &stage5[i]))
                {
                    // ��
                    if (stage5[i].type == 2)
                    {
                        stage5[i].open = true;
                        continue;
                    }

                    // �����͂�
                    if (stage5[i].type == 5 && !stage5[i].exist)continue;   

                    // �����
                    if (stage5[i].type == 6 && !stage5[i].exist)continue;

                    // �X�C�b�`
                    if (stage5[i].type == 7)
                    {
                        stage5[i].texPos.x = 64;
                        stage5[5].exist = false;
                        door2.open = true;
                        continue;
                    }

                    // �߂荞�ݑ΍�		// �����蔻��
                    float dist;
                    if (player.speed.x >= 0)
                        dist = check(&player, &stage5[i], DIR::RIGHT);
                    else
                        dist = check(&player, &stage5[i], DIR::LEFT);
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

void stage5_render()
{
    GameLib::clear(1, 1, 1);

    // �w�i
    sprite_render(sprStage0, 0, 0);

    // �n�`
#ifdef _DEBUG
    for (int i = 0; i < STAGE5_MAX; ++i)
    {
        primitive::rect(stage5[i].pos, stage5[i].hsize * 2, stage5[i].hsize, 0, { stage5[i].color.x,stage5[i].color.y,stage5[i].color.z,1 });
    }
#endif // _DEBUG

    // �ׂ�Ƃ���ׂ��@
    for (int i = 0; i < 13; ++i)
    {
        sprite_render(sprGear, 60 + i * 120, 765, 1, 1, 240, 0, 120, 120, 60, 60, Gangle);
    }
    sprite_render(sprBelt, stage5[0].position.x, 700 - 5);
    sprite_render(sprBelt, stage5[0].position.x + 1530, 700 - 5);
    sprite_render(sprBelt, -stage5[0].position.x, 700 + 124 + 10, 1, -1);
    sprite_render(sprBelt, -stage5[0].position.x - 1530, 700 + 124 + 10, 1, -1);

    // ����
    for (int x = 0; x < 5; ++x)
    {
        sprite_render(sprTerrain, x * 64, 632, 1, 1, 64, 0, 64, 64);
    }
    // �^�񒆏�
    for (int x = 0; x < 12; ++x)
    {
        sprite_render(sprTerrain, 330+(x * 64), 278, 1, 1, 64, 0, 64, 64);
    }
    // �^�񒆕�
    for (int y = 0; y < 3; ++y)
    {
        sprite_render(sprBoxMove, 340, 13 + (y * 88), 1, 1, 180, 0, 90, 90);
    }
    // �E��
    for (int x = 0; x < 3; ++x)
    {
        sprite_render(sprTerrain, 1360 + (x * 64), 278, 1, 1, 64, 0, 64, 64);
    }
    for (int y = 0; y < 5; ++y)
    {
        sprite_render(sprTerrain, 1034, -42 + (y * 64), 1, 1, 192, 0, 64, 64);
    }

    // �g���b�R
    sprite_render(sprTrolley, stage5[10].position.x, stage5[10].position.y, 1, 1, stage5[10].elec * 178, 0, 177, 177);

    // ������
    sprite_render(sprDoor2, 1098, 278, 1, 1, door2.texPos.x, 64, 128, 64);
    sprite_render(sprDoor2, 1360, 278, -1, 1, door2.texPos.x, 64, 128, 64);

    // ���~�@
    sprite_render(sprSyoukouki, stage5[7].position.x, stage5[7].position.y, 1, 1, stage5[7].elec * 178, 177, 177, 177);
    sprite_render(sprSyoukouki, stage5[8].position.x, stage5[8].position.y, 1, 1, stage5[8].elec * 178, 177, 177, 177);
    sprite_render(sprSyoukouki, stage5[9].position.x, stage5[9].position.y, 1, 1, stage5[9].elec * 178, 0, 177, 177);

    // �X�C�b�`
    sprite_render(sprSwitch, 1415, 216, 1, 1, stage5[12].texPos.x, 0, 64, 64);

    // �G���x�[�^�[
    sprite_render(sprEV, stage5[1].position.x - 5, stage5[1].position.y - 658);

    // ��
    sprite_render(sprDoor, stage5[1].position.x, stage5[1].position.y, 1, 1, stage5[1].texPos.x, stage5[1].texPos.y, stage5[1].texSize.x, stage5[1].texSize.y);

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

    sprite_render(sprMouse, mousePos.x, mousePos.y, 1, 1, 0, 0, 100, 100, 50, 50);
}

#if 0
#include "all.h"

void stage5_init()
{
    stage_state[5] = 0;
}

void stage5_deinit()
{
    player.Dinit();

    safe_delete(sprEV);
    safe_delete(sprEvPlayer);
    safe_delete(sprMouse);
    safe_delete(sprTerrain);
    safe_delete(sprPause);
    safe_delete(sprWhite);


    music::stop(game_bgm);
}

void stage5_update()
{
    switch (stage_state[5])
    {
    case 0:
        ///// �����ݒ� /////
        player.Init();

        sprElec = sprite_load(L"./Data/Images/elec.png");
        sprDoor = sprite_load(L"./Data/Images/door.png");
        sprEV = sprite_load(L"./Data/Images/EV.png");
        sprEvPlayer = sprite_load(L"./Data/Images/p.png");
        sprMouse = sprite_load(L"./Data/Images/mouse.png");
        sprTerrain = sprite_load(L"./Data/Images/terrain.png");
        sprPause = sprite_load(L"./Data/Images/pause.png");
        sprWhite = sprite_load(L"./Data/Images/white.png");

        ++stage_state[5];
    case 1:
        ///// �p�����[�^�[�̐ݒ� /////

        // �|�[�Y
        pause = false;

        // EvPlayer
        //EvPlayer = { stage3[4].position.x, stage3[4].position.y + 100 };

        // �h�A�Ō�
        door = {};

        // �d�C
        Elec = {};

        music::play(game_bgm, true);


        ++stage_state[5];
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

void stage5_render()
{
    GameLib::clear(1, 1, 1);


    // �|�[�Y���
    if (pause)
    {
        sprite_render(sprWhite, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprPause, 0, 0);
    }

    sprite_render(sprMouse, mousePos.x, mousePos.y, 1, 1, 0, 0, 100, 100, 50, 50);
}

#endif