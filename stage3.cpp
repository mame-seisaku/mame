#include "all.h"
/*****�ϐ�*****/

stage stage3[STAGE3_MAX];

VECTOR2 speed3;

Sprite* spr3;
Sprite* sprSyoukouki; // ���~�@
extern Sprite* sprBox; 

extern VECTOR2 mousePos;
extern stage door;

extern Sprite* sprElec; // �d�C
extern Sprite* sprDoor; // �h�A


void stage3_init()
{
	stage_state[3] = 0;
}

void stage3_deinit()
{
    player.Dinit();

	safe_delete(spr3);
	safe_delete(sprSyoukouki);
    safe_delete(sprUI);
    safe_delete(sprEV);
    safe_delete(sprEvPlayer);
    safe_delete(sprMouse);
    safe_delete(sprBox);
    safe_delete(sprTerrain);
    safe_delete(sprPause);
    safe_delete(sprWhite);
    safe_delete(sprHelp);

    music::stop(game_bgm);
}

void stage3_update()
{
    switch (stage_state[3])
    {
    case 0:
        ///// �����ݒ� /////
        player.Init();

        spr3 = sprite_load(L"./Data/Images/05.png");
        sprSyoukouki = sprite_load(L"./Data/Images/syoukouki2.png");

        sprBox = sprite_load(L"./Data/Images/box.png");

        sprUI = sprite_load(L"./Data/Images/UI.png");
        sprElec = sprite_load(L"./Data/Images/elec.png");
        sprDoor = sprite_load(L"./Data/Images/door.png");
        sprEV = sprite_load(L"./Data/Images/EV.png");
        sprEvPlayer = sprite_load(L"./Data/Images/p.png");
        sprMouse = sprite_load(L"./Data/Images/mouse.png");
        sprTerrain = sprite_load(L"./Data/Images/terrain.png");
        sprPause = sprite_load(L"./Data/Images/pause.png");
        sprWhite = sprite_load(L"./Data/Images/white.png");
        sprHelp = sprite_load(L"./Data/Images/help.png");

        ++stage_state[3];
    case 1:
        ///// �p�����[�^�̐ݒ� /////

        // �|�[�Y
        pause = false;

        for (int i = 0; i < STAGE1_MAX; ++i)
        {
            stage3[i] = {};
        }

        // type 
        // 0 kabe
        // 2 ��

        // ��
        stage3[0].pos = { 768,764 };
        stage3[0].hsize = { 768, 64 };
        stage3[0].type = 0;
        stage3[0].exist = true;
        // ����
        //stage3[1].pos = { 5,412 };
        //stage3[1].hsize = { 5,412 };
        //stage3[1].type = 0;
        //stage3[1].exist = true;
        // �E��
        stage3[2].pos = { 1531,412 };
        stage3[2].hsize = { 15,412 };
        stage3[2].type = 0;
        stage3[2].exist = true;
        //���~�@
        stage3[3].position = { 890,510 };
        stage3[3].pos = { 979,650 };
        stage3[3].hsize = { 89, 50 };
        stage3[3].type = 0;
        stage3[3].exist = true;

        // ��
        stage3[4].position = { 1239,230 };
        stage3[4].pos = { 1330,320 };
        stage3[4].hsize = { 80, 89 };
        stage3[4].texPos = {};
        stage3[4].texSize = { 178,177 };
        stage3[4].type = 2;
        stage3[4].exist = true;
        stage3[4].open = false;

        // ����
        stage3[5].pos = { 1340,550 };
        stage3[5].hsize = { 180, 150 };
        stage3[5].type = 0;
        stage3[5].exist = true;

        // �^�񒆂̃f�Jbox
        stage3[6].position = { 480,523 };
        stage3[6].pos = { 569,612.5f };
        stage3[6].hsize = { 89, 88.5f };
        stage3[6].type = 7;
        stage3[6].exist = true;

        //���~�@2
        stage3[7].position = { 240,210 };
        stage3[7].pos = { 329,350 };
        stage3[7].hsize = { 89, 50 };
        stage3[7].type = 0;
        stage3[7].exist = true;

        // EvPlayer
        EvPlayer = { stage3[4].position.x, stage3[4].position.y + 100 };

        // �h�A�Ō�
        door = {};

        // �d�C
        Elec = {};

        music::play(game_bgm, true);

        ++stage_state[3];
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
            if (PossibleStage < 4)PossibleStage = 4;
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

        if (!pause)
        {
            player.Update({100,200});

#ifdef _DEBUG
            oss << "(x=" << point.x << " y=" << point.y << ")";
            SetWindowTextA(window::getHwnd(), oss.str().c_str());   // �^�C�g���o�[�ɂ�\��������
            debug::setString("PossibleStage:%d", PossibleStage);
            debug::setString("stage3[3].pos.x:%f", stage3[3].pos.x);
            debug::setString("stage3[3].pos.y:%f", stage3[3].pos.y);
            debug::setString("stage3[7].pos.x:%f", stage3[7].pos.x);
            debug::setString("stage3[7].pos.y:%f", stage3[7].pos.y);
#endif
            // ���A�j��
            if (stage3[4].open)
                anime(&stage3[4], 7, 10, false, 0);

            // �N���A����
            if (stage3[4].end && stage3[4].one && !door.close)
            {
                player.clear = true;
                door = stage3[4];
                door.state = 0;
                door.close = true;
            }

            if (player.clear)
            {
                player.pos.x = stage3[4].position.x + 71;    // �h�A�̈ʒu�Ɉړ�
                // �d�C��߂�
                player.elec = true;
                for (int i = 0; i < STAGE0_MAX; ++i)
                {
                    stage3[i].elec = false;
                }

                // �����܂�
                anime(&door, 7, 10, false, 0);
            }

            if (mousePos.x > stage3[3].pos.x - 90 && mousePos.y > stage3[3].pos.y - 50 && mousePos.x < stage3[3].pos.x + 90 && mousePos.y < stage3[3].pos.y + 50||
                mousePos.x > stage3[7].pos.x - 90 && mousePos.y > stage3[7].pos.y - 50 && mousePos.x < stage3[7].pos.x + 90 && mousePos.y < stage3[7].pos.y + 50)
            {
                MouseTexPos.x = 100;
            }
            else
            {
                MouseTexPos.x = 0;
            }


            // �}�E�X�ł̜߈ˑ���
            //���~�@1
            if (mousePos.x > stage3[3].pos.x - 90 && mousePos.y > stage3[3].pos.y - 50 && mousePos.x < stage3[3].pos.x + 90 && mousePos.y < stage3[3].pos.y + 50)
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
            //���~�@2
            if (mousePos.x > stage3[7].pos.x - 90 && mousePos.y > stage3[7].pos.y - 50 && mousePos.x < stage3[7].pos.x + 90 && mousePos.y < stage3[7].pos.y + 50)
            {
                if (TRG(0) & PAD_L3)
                {
                    if (!Elec.exist && player.elec)
                    {
                        SetElecMove();
                        Elec.type = 7;
                    }
                }
            }
            if (TRG(0) & PAD_R3 && !player.elec)
            {
                stage3[3].elec = false;
                stage3[7].elec = false;
                player.elec = true;
            }


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
                            stage3[Elec.type].elec = true;
                           
                        }
                    }
                    else
                    {
                        // ��������
                        if (Elec.pos.x >= ElecPos.x)
                        {
                            player.elec = false;    // �v���C���[�̓d�C����
                            Elec.exist = false;
                            stage3[Elec.type].elec = true;
                            
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
                            stage3[Elec.type].elec = true;
                            
                        }
                    }
                    else
                    {
                        // ��������
                        if (Elec.pos.x <= ElecPos.x)
                        {
                            player.elec = false;    // �v���C���[�̓d�C����
                            Elec.exist = false;
                            stage3[Elec.type].elec = true;
                            
                        }
                    }
                }
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
            //���~�@1 �ړ�
            if (stage3[3].elec == true) {
                stage3[3].pos.y += speed3.y;
                stage3[3].position.y = stage3[3].pos.y - 140;
            }
            //���~�@2 �ړ�
            if (stage3[7].elec == true) {
                stage3[7].pos.y += speed3.y;
                stage3[7].position.y = stage3[7].pos.y - 140;
            }

            // �㉺�̂߂荞�݃`�F�b�N
            for (int i = 0; i < STAGE3_MAX; ++i)
            {
                if (hitCheck(&player, &stage3[i]))
                {
                    // ��
                    if (stage3[i].type == 2)
                    {
                        stage3[i].open = true;
                        continue;
                    }


                    // �߂荞�ݑ΍�		// �����蔻��
                    float dist;
                    if (player.speed.y >= 0)
                        dist = check(&player, &stage3[i], DIR::DOWN);
                    else
                        dist = check(&player, &stage3[i], DIR::UP);
                    player.pos.y += dist;
                    player.speed.y = 0;
                    
                }
                //���~�@1
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
                //���~�@2
                if (hitCheck(&stage3[7], &stage3[0]))
                {
                    float dist;
                    if (speed3.y >= 0)
                        dist = check(&stage3[7], &stage3[0], DIR::DOWN);
                    else
                        dist = check(&stage3[7], &stage3[0], DIR::UP);
                    stage3[7].pos.y += dist;
                    speed3.y = 0;
                    stage3[7].position.y += dist;
                }
               
            }

            //�� ���
            //���~�@1
            if (stage3[3].pos.y < 200) {
                stage3[3].pos.y = 200;
                stage3[3].position.y = 60;
            }
            //���~�@2
            if (stage3[7].pos.y < 200) {
                stage3[7].pos.y = 200;
                stage3[7].position.y = 60;
            }


            //����؂�ւ�
            player.pos.x += player.speed.x;


            // ���E�̂߂荞�݃`�F�b�N
            for (int i = 0; i < STAGE3_MAX; ++i)
            {
                if (player.elec == true) {
                    if (hitCheck(&player, &stage3[i]))
                    {
                        // ��
                        if (stage3[i].type == 2)
                        {
                            stage3[i].open = true;
                            continue;
                        }

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

            if (TRG(0) & PAD_START)
            {
                help = 9;
                nextScene = SCENE::ZUKAN;
                break;
            }
        }

        UI = player.elec ? 0 : 105;

        break;
    }
}

void stage3_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(spr3, 0, 0);

    // �n�`�`��
   /* for (int i = 0; i < STAGE1_MAX; ++i)
    {
        primitive::rect(stage3[i].pos, stage3[i].hsize * 2, stage3[i].hsize, 0, { 1,0,0,1 });
    }*/
    //��
    for (int y = 0; y < 2; ++y)
    {
        for (int x = 0; x < 24; ++x)
        {
            sprite_render(sprTerrain, x * 64, 700 + (y * 64), 1, 1, 64, 0, 64, 64);
        }
    }
    
    //����
    for (int y = 0; y < 7; ++y)
    {
        for (int x = 0; x < 6; ++x)
        {
            sprite_render(sprTerrain, 1152 + (x * 64), 400 + (y * 64), 1, 1, 64, 0, 64, 64);
        }
    }


    // ���~�@
    sprite_render(sprSyoukouki, stage3[3].position.x, stage3[3].position.y, 1, 1, stage3[3].elec * 178, 0, 177, 177);
    // ���~�@2
    sprite_render(sprSyoukouki, stage3[7].position.x, stage3[7].position.y, 1, 1, stage3[7].elec * 178, 0, 177, 177);
    
    // �G���x�[�^�[
    sprite_render(sprEV, stage3[4].position.x - 5, stage3[4].position.y - 653);

    
    // �f�J��
    sprite_render(sprBox, stage3[6].position.x, stage3[6].position.y);

    // ��
    sprite_render(sprDoor, stage3[4].position.x, stage3[4].position.y, 1, 1, stage3[4].texPos.x, stage3[4].texPos.y, stage3[4].texSize.x, stage3[4].texSize.y);

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

    sprite_render(sprMouse, mousePos.x, mousePos.y, 1, 1, MouseTexPos.x, MouseTexPos.y, 100, 100, 50, 50);
}
