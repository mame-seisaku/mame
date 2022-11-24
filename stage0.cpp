#include "all.h"

/*****�ϐ�*****/

float Gangle; // �M�A
int GangleT;

stage stage0[STAGE0_MAX];
stage door;

Sprite* sprStage0;
Sprite* sprStage0Floor;
Sprite* sprBox;
Sprite* sprElec;
Sprite* sprDoor;
Sprite* sprBeltConveyor;
Sprite* sprBelt;
Sprite* sprGear;

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
    safe_delete(sprElec);
    safe_delete(sprDoor);
    safe_delete(sprBeltConveyor);
    safe_delete(sprBelt);
    safe_delete(sprGear);
    safe_delete(sprEV);
    safe_delete(sprEvPlayer);
    safe_delete(sprMouse);

    safe_delete(sprWhite);
    safe_delete(sprUI);
    safe_delete(sprTerrain);
    safe_delete(sprPause);
    safe_delete(sprHelp);

    music::stop(0);
    music::stop(game_bgm);
}

void stage0_update()
{
    switch (stage_state[0])
    {
    case 0:
        ///// �����ݒ� /////
        player.Init();

        //sprStage0     = sprite_load(L"./Data/Images/stage0.png");
        sprStage0 = sprite_load(L"./Data/Images/05.png");
        sprStage0Floor = sprite_load(L"./Data/Images/03.png");
        sprBox = sprite_load(L"./Data/Images/box.png");
        sprElec = sprite_load(L"./Data/Images/elec.png");
        sprDoor = sprite_load(L"./Data/Images/door.png");
        sprBeltConveyor = sprite_load(L"./Data/Images/BeltConveyor.png");
        sprBelt = sprite_load(L"./Data/Images/Belt.png");
        sprGear = sprite_load(L"./Data/Images/gear.png");
        sprEV = sprite_load(L"./Data/Images/EV.png");
        sprEvPlayer = sprite_load(L"./Data/Images/p.png");
        sprMouse = sprite_load(L"./Data/Images/mouse.png");

        sprTerrain = sprite_load(L"./Data/Images/terrain.png");
        sprUI = sprite_load(L"./Data/Images/UI.png");
        sprPause = sprite_load(L"./Data/Images/pause.png");
        sprWhite = sprite_load(L"./Data/Images/white.png");
        sprHelp = sprite_load(L"./Data/Images/help.png");

        ++stage_state[0];
    case 1:
        ///// �p�����[�^�̐ݒ� /////

        // �|�[�Y
        pause = false;

        // �d�C�p
        ElecPos = {};

        for (int i = 0; i < STAGE0_MAX; ++i)
        {
            stage0[i] = {};
        }

        // ��
        //stage0[0].position = { 0,700 };
        stage0[0].position = { 0,0 };
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
        stage0[2].position = { 1239,530 };
        stage0[2].pos = { 1330,620 };
        stage0[2].hsize = { 80, 89 };
        stage0[2].texPos = {};
        stage0[2].texSize = { 178,177 };
        stage0[2].type = 2;
        stage0[2].exist = true;
        stage0[2].open = false;
        // ����
        stage0[3].pos = { 5,412 };
        stage0[3].hsize = { 5,412 };
        stage0[3].type = 0;
        stage0[3].exist = true;
        // �A���`
        stage0[4].position = { 70,640 };
        stage0[4].pos = { 105,650 };
        stage0[4].hsize = { 80,10 };
        stage0[4].type = 0;
        stage0[4].exist = true;

        player.clear = false;

        // �h�A�Ō�
        door = {};

        // �d�C
        Elec = {};

        // EvPlayer
        EvPlayer = { stage0[2].position.x, stage0[2].position.y + 100 };

        Gangle = 0;
        GangleT = 0;

        MouseTexPos = {};

        music::play(game_bgm, true);

        ++stage_state[0];
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
            if (PossibleStage < 1)PossibleStage = 1;
            nextScene = SCENE::RESULT;
            break;
        }

        // �|�[�Y  F
        if (TRG(0) & PAD_TRG4)
        {
            //EvPlayer.y -= 10;
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
            player.Update({ 100,200 });         
#ifdef _DEBUG
            oss << "(x=" << point.x << " y=" << point.y << ")";
            SetWindowTextA(window::getHwnd(), oss.str().c_str());   // �^�C�g���o�[�ɂ�\��������
            debug::setString("PossibleStage:%d", PossibleStage);
            debug::setString("player.elec:%d", player.elec);
            debug::setString("ElecPos.x:%f,ElecPos.y:%f", ElecPos.x, ElecPos.y);
            debug::setString("Elec.Pos.x:%f,Elec.Pos.y:%f", Elec.pos.x, Elec.pos.y);
            debug::setString("mousePos.x:%f,mousePos.y:%f", mousePos.x, mousePos.y);
#endif
            if (mousePos.x > 0 && mousePos.y > 700 && mousePos.x < 1536 && mousePos.y < 900)
            {
                MouseTexPos.x = 100;
            }
            else
            {
                MouseTexPos.x = 0;
            }

            // ���A�j��
            if (stage0[2].open)
                anime(&stage0[2], 7, 10, false, 0);

            // �N���A����
            if (stage0[2].end && stage0[2].one && !door.close)
            {
                player.clear = true;
                door = stage0[2];
                door.state = 0;
                door.close = true;
            }

            if (player.clear)
            {
                player.pos.x = stage0[2].position.x + 71;    // �h�A�̈ʒu�Ɉړ�
                // �d�C��߂�
                player.elec = true;
                for (int i = 0; i < STAGE0_MAX; ++i)
                {
                    stage0[i].elec = false;
                }

                Elec.exist = false;
                stage0[0].elec = false;
                player.elec = true;
                GangleT = 0;
                music::stop(0);

                // �����܂�
                anime(&door, 7, 10, false, 0);
            }

            // �}�E�X�ł̜߈ˑ���
            if (!player.clear)  // clear���Ă����瑀��ł��Ȃ�
            {
                // relese�ňʒu���ς��
                if (mousePos.x > 0 && mousePos.y > 700 && mousePos.x < 1536 && mousePos.y < 900)
                {
                    // �d�C���΂�
                    if (TRG(0) & PAD_L3)
                    {
                        // �v���C���[�ɓd�C�������
                        if (!Elec.exist && player.elec)
                        {
                            SetElecMove();
                            Elec.type = stage0[0].type;
                        }
                    }
                    // �d�C���
                    if (TRG(0) & PAD_R3 && !player.elec)
                    {
                        Elec.exist = false;
                        stage0[0].elec = false;
                        player.elec = true;
                        GangleT = 0;
                        music::stop(0);
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
                    // ��������
                    if (Elec.pos.x >= ElecPos.x || Elec.pos.y >= ElecPos.y)
                    {
                        player.elec = false;    // �v���C���[�̓d�C����
                        Elec.exist = false;
                        stage0[0].elec = true;

                        GangleT = 120;

                        if (Elec.type == stage0[0].type)
                            music::play(0, true);
                    }
                }
                // ���������֐i��
                else
                {
                    // ��������
                    if (Elec.pos.x <= ElecPos.x || Elec.pos.y >= ElecPos.y)
                    {
                        player.elec = false;    // �v���C���[�̓d�C����
                        Elec.exist = false;
                        stage0[0].elec = true;

                        GangleT = 120;
                    }
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
                        stage0[i].open = true;
                        continue;
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
                        stage0[i].open = true;
                        continue;
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
                Gangle += ToRadian(10);

                stage0[0].position.x += 10;
                stage0[1].position.x += 10;
                stage0[1].pos.x += 10;
            }
            else
            {
                player.texPos.y = 0;
            }
            // �͈͊O
            if (stage0[0].position.x > 0)
            {
                stage0[0].position.x = -1536;
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

void stage0_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(sprStage0, 0, 0);

    // �n�`�`��
#ifdef _DEBUG
    for (int i = 0; i < STAGE0_MAX; ++i)
    {
        primitive::rect(stage0[i].pos, stage0[i].hsize * 2, stage0[i].hsize, 0, { stage0[i].color.x,stage0[i].color.y,stage0[i].color.z,0 });
    }
#endif
    sprite_render(sprTerrain, 0, 640, 1, 1, 64, 0, 64, 64);
    sprite_render(sprTerrain, 64, 640, 1, 1, 64, 0, 64, 64);
    sprite_render(sprTerrain, 128, 640, 1, 1, 64, 0, 64, 64);
    for (int y = 0; y < 2; ++y)
    {
        for (int x = 0; x < 24; ++x)
        {
            sprite_render(sprTerrain, 64 * x, 640 + (64 * (y + 1)), 1, 1, 64, 0, 64, 64);
        }
    }

    // ��
    for (int i = 0; i < 13; ++i)
    {
        sprite_render(sprGear, 60 + i * 120, 765, 1, 1, GangleT, 0, 120, 120, 60, 60, Gangle);
    }

    sprite_render(sprBelt, stage0[0].position.x, 700 - 5);
    sprite_render(sprBelt, stage0[0].position.x + 1530, 700 - 5);
    sprite_render(sprBelt, -stage0[0].position.x, 700 + 124+10, 1, -1);
    sprite_render(sprBelt, -stage0[0].position.x - 1530, 700 + 124+10, 1, -1);

    // �G���x�[�^�[
    sprite_render(sprEV, stage0[2].position.x - 5, stage0[2].position.y - 653);

    
    // ��
    sprite_render(sprDoor, stage0[2].position.x, stage0[2].position.y, 1, 1, stage0[2].texPos.x, stage0[2].texPos.y, stage0[2].texSize.x, stage0[2].texSize.y);
    // ��
    sprite_render(sprBox, stage0[1].position.x, stage0[1].position.y);

    // �d�C
    if(Elec.exist)
        sprite_render(sprElec, Elec.pos.x, Elec.pos.y, 1, 1, 0, 0, 128, 128, 64, 64);


    // �v���C���[
    player.Render();
    //primitive::rect(player.pos, player.hsize * 2, player.hsize, 0, { 0,0,1,1 });
    
    // playerEv
    if(door.end)
        sprite_render(sprEvPlayer, EvPlayer.x +35, EvPlayer.y);
    
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

