#include "all.h"

/*****�ϐ�*****/

stage stage1[STAGE1_MAX];


Sprite* spr1;
Sprite* sprBox1;
Sprite* sprTrolley;

VECTOR2 speed1;

extern VECTOR2 mousePos;
extern stage door;

extern Sprite* sprElec; // �d�C
extern Sprite* sprDoor; // �h�A

/// <summary>
/// �����ݒ�
/// </summary>
void stage1_init()
{
    stage_state[1] = 0;
}

/// <summary>
/// �I������
/// </summary>
void stage1_deinit()
{
    player.Dinit();

    safe_delete(spr1);
    safe_delete(sprBox1);
    safe_delete(sprTrolley);


    safe_delete(sprElec);
    safe_delete(sprDoor);
    safe_delete(sprEV);
    safe_delete(sprEvPlayer);

    safe_delete(sprTerrain);

    safe_delete(sprPause);

    music::stop(game_bgm);
}

/// <summary>
/// �X�V����
/// </summary>
void stage1_update()
{
    switch (stage_state[1])
    {
    case 0:
        ///// �����ݒ� /////
        player.Init();

        spr1 = sprite_load(L"./Data/Images/04.png");
        sprBox1 = sprite_load(L"./Data/Images/box.png");
        sprTrolley = sprite_load(L"./Data/Images/trolley.png");

        sprElec = sprite_load(L"./Data/Images/elec.png");
        sprDoor = sprite_load(L"./Data/Images/door.png");
        sprEV = sprite_load(L"./Data/Images/EV.png");
        sprEvPlayer = sprite_load(L"./Data/Images/p.png");

        sprTerrain = sprite_load(L"./Data/Images/terrain.png");

        sprPause = sprite_load(L"./Data/Images/pause.png");

        ++stage_state[1];
    case 1:
        ///// �p�����[�^�̐ݒ� /////

        // �|�[�Y
        pause = false;

        for (int i = 0; i < STAGE1_MAX; ++i)
        {
            stage1[i] = {};
        }

        // type
        // 1 �g���b�R
        // 2 �Ƃт�@

        // ��
        stage1[0].pos = { 768,764 };
        stage1[0].hsize = { 768, 64 };
        stage1[0].type = 0;
        stage1[0].exist = true;
        // ����
        stage1[1].pos = { 5,412 };
        stage1[1].hsize = { 5,412 };
        stage1[1].type = 0;
        stage1[1].exist = true;
        // �E��
        stage1[2].pos = { 1531,412 };
        stage1[2].hsize = { 15,412 };
        stage1[2].type = 0;
        stage1[2].exist = true;
        //�g���b�R
        stage1[3].position = { 190,522 };
        stage1[3].pos = { 277,650 };
        stage1[3].hsize = { 90, 50 };
        stage1[3].type = 1;
        stage1[3].exist = true;
        // BOX
        stage1[4].position = { 890,523 };
        stage1[4].pos = { 979,612.5f };
        stage1[4].hsize = { 89, 88.5f };
        stage1[4].type = 0;
        stage1[4].exist = true;
        // stop
        stage1[5].pos = { 52,650 };
        stage1[5].hsize = { 135, 50 };
        stage1[5].type = 0;
        stage1[5].exist = true;

        // ��
        stage1[6].position = { 1239,530 };
        stage1[6].pos = { 1330,620 };
        stage1[6].hsize = { 80, 89 };
        stage1[6].texPos = {};
        stage1[6].texSize = { 178,177 };
        stage1[6].type = 2;
        stage1[6].exist = true;
        stage1[6].open = false;

        // EvPlayer
        EvPlayer = { stage1[6].position.x, stage1[6].position.y };

        // �h�A�Ō�
        door = {};

        // �d�C
        Elec = {};

        music::play(game_bgm, true);

        ++stage_state[1];
    case 2:
        ///// �ʏ펞 /////

        // �V�[���؂�ւ�
        if (door.end)
        {
            EvPlayer.y -= 10;
        }
        if (EvPlayer.y < -200)
        {
            nextScene = SCENE::RESULT;
            break;
        }

        // �|�[�Y  F
        if (TRG(0) & PAD_TRG4)
        {
            pause = pause ? false : true;
        }

        if (!pause)
        {

            player.Update({100,200});

            // �}�E�X�J�[�\��
#ifdef _DEBUG
#endif
            std::ostringstream oss;                                 // ������X�g���[��
            POINT point;                                            // �ʒu�p�̕ϐ���錾����
            GetCursorPos(&point);                                   // �X�N���[�����W���擾����
            ScreenToClient(window::getHwnd(), &point);              // �N���C�A���g���W�ɕϊ�����
            mousePos.x = (float)(point.x);
            mousePos.y = (float)(point.y);
            oss << "(x=" << point.x << " y=" << point.y << ")";
            SetWindowTextA(window::getHwnd(), oss.str().c_str());   // �^�C�g���o�[�ɂ�\��������
            //debug::setString("PossibleStage:%d", PossibleStage);
            //debug::setString("toroko:%f", stage1[3].pos.x);
            debug::setString("mousePos.x:%f,mousePos.y:%f", mousePos.x, mousePos.y);
            debug::setString("stage1[3].pos.x:%f", stage1[3].pos.x);
            debug::setString("stage1[3].pos.y:%f", stage1[3].pos.y);

            // ���A�j��
            if (stage1[6].open)
                anime(&stage1[6], 7, 10, false, 0);

            // �N���A����
            if (stage1[6].end && stage1[6].one && !door.close)
            {
                player.clear = true;
                door = stage1[6];
                door.state = 0;
                door.close = true;
            }

            if (player.clear)
            {
                player.pos.x = stage1[6].position.x + 51;    // �h�A�̈ʒu�Ɉړ�
                // �d�C��߂�
                player.elec = true;
                for (int i = 0; i < STAGE0_MAX; ++i)
                {
                    stage1[i].elec = false;
                }

                // �����܂�
                anime(&door, 7, 10, false, 0);
            }



            // �}�E�X�ł̜߈ˑ���
            if (mousePos.x > stage1[3].pos.x - 90 && mousePos.y > stage1[3].pos.y - 50 && mousePos.x < stage1[3].pos.x + 90 && mousePos.y - 50 < stage1[3].pos.y + 110)
            {
                // �d�C���΂�
                if (TRG(0) & PAD_L3)
                {
                    // �v���C���[�ɓd�C�������
                    if (!Elec.exist && player.elec)
                        SetElecMove();

                }
                // �d�C���
                if (TRG(0) & PAD_R3 && !player.elec)
                {
                    Elec.exist = false;
                    stage1[3].elec = false;
                    player.elec = true;
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
                            stage1[3].elec = true;
                        }
                    }
                    else
                    {
                        // ��������
                        if (Elec.pos.x >= ElecPos.x)
                        {
                            player.elec = false;    // �v���C���[�̓d�C����
                            Elec.exist = false;
                            stage1[3].elec = true;
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
                            stage1[3].elec = true;
                        }
                    }
                    else
                    {
                        // ��������
                        if (Elec.pos.x <= ElecPos.x)
                        {
                            player.elec = false;    // �v���C���[�̓d�C����
                            Elec.exist = false;
                            stage1[3].elec = true;
                        }
                    }
                }
            }


            if (STATE(0) & PAD_LEFT)
            {
                if (!(STATE(0) & PAD_RIGHT))
                {
                    speed1.x = -PLAYER_MOVE;
                }
            }
            else if (STATE(0) & PAD_RIGHT)
            {
                if (!(STATE(0) & PAD_LEFT))
                {
                    speed1.x = PLAYER_MOVE;
                }
            }
            else
            {
                speed1.x = 0;
            }

            player.pos.y += player.speed.y;

            // �㉺�̂߂荞�݃`�F�b�N
            for (int i = 0; i < STAGE0_MAX; ++i)
            {
                if (hitCheck(&player, &stage1[i]))
                {

                    //��ɏ�������̈ړ�
                    if (stage1[i].type == 1 && stage1[i].elec)
                    {
                        player.pos.x += speed1.x;
                    }

                    // ��
                    if (stage1[i].type == 2)
                    {
                        stage1[i].open = true;
                        break;
                    }

                    // �߂荞�ݑ΍�		// �����蔻��
                    float dist;
                    if (player.speed.y >= 0)

                        dist = check(&player, &stage1[i], DIR::DOWN);
                    else
                        dist = check(&player, &stage1[i], DIR::UP);
                    player.pos.y += dist;
                    player.speed.y = 0;
                }
            }

            //����؂�ւ�
            if (player.elec == true)
            {
                player.pos.x += player.speed.x;
            }
            else if (stage1[3].elec == true)
            {
                stage1[3].pos.x += speed1.x;
                stage1[3].position.x = stage1[3].pos.x - 86;
            }

            // ���E�̂߂荞�݃`�F�b�N
            for (int i = 0; i < STAGE0_MAX; ++i)
            {
                if (player.elec == true) {
                    if (hitCheck(&player, &stage1[i]))
                    {
                        // ��
                        if (stage1[i].type == 2)
                        {
                            stage1[i].open = true;
                            break;
                        }

                        // �߂荞�ݑ΍�		// �����蔻��
                        float dist;
                        if (player.speed.x >= 0)
                            dist = check(&player, &stage1[i], DIR::RIGHT);
                        else
                            dist = check(&player, &stage1[i], DIR::LEFT);
                        player.pos.x += dist;
                        player.speed.x = 0;
                    }

                }
                if (player.elec == false) {
                    if (hitCheck(&player, &stage1[i]))
                    {
                        // �߂荞�ݑ΍�		// �����蔻��
                        float dist;
                        if (speed1.x >= 0)
                            dist = check(&player, &stage1[i], DIR::RIGHT);
                        else
                            dist = check(&player, &stage1[i], DIR::LEFT);
                        player.pos.x += dist;
                        speed1.x = 0;
                    }
                    if (hitCheck(&stage1[3], &player))
                    {
                        // �߂荞�ݑ΍�		// �����蔻��
                        float dist;
                        if (speed1.x >= 0)
                            dist = check(&stage1[3], &player, DIR::RIGHT);
                        else
                            dist = check(&stage1[3], &player, DIR::LEFT);
                        stage1[3].pos.x += dist;
                        speed1.x = 0;
                        stage1[3].position.x += dist;
                    }
                    if (hitCheck(&stage1[3], &stage1[1]))
                    {
                        // �߂荞�ݑ΍�		// �����蔻��
                        float dist;
                        if (speed1.x >= 0)
                            dist = check(&stage1[3], &stage1[1], DIR::RIGHT);
                        else
                            dist = check(&stage1[3], &stage1[1], DIR::LEFT);
                        stage1[3].pos.x += dist;
                        speed1.x = 0;
                        stage1[3].position.x += dist;
                    }
                    if (hitCheck(&stage1[3], &stage1[4]))
                    {
                        // �߂荞�ݑ΍�		// �����蔻��
                        float dist;
                        if (speed1.x >= 0)
                            dist = check(&stage1[3], &stage1[4], DIR::RIGHT);
                        else
                            dist = check(&stage1[3], &stage1[4], DIR::LEFT);
                        stage1[3].pos.x += dist;
                        speed1.x = 0;
                        stage1[3].position.x += dist;
                    }
                    if (hitCheck(&stage1[3], &stage1[5]))
                    {
                        // �߂荞�ݑ΍�		// �����蔻��
                        float dist;
                        if (speed1.x >= 0)
                            dist = check(&stage1[3], &stage1[5], DIR::RIGHT);
                        else
                            dist = check(&stage1[3], &stage1[5], DIR::LEFT);
                        stage1[3].pos.x += dist;
                        speed1.x = 0;
                        stage1[3].position.x += dist;
                    }
                }
            }
            break;
        }
    }
}

/// <summary>
/// �`�揈��
/// </summary>
void stage1_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(spr1, 0, 0);

    
#ifdef _DEBUG
    for (int i = 0; i < STAGE1_MAX; ++i)
    {
        primitive::rect(stage1[i].pos, stage1[i].hsize * 2, stage1[i].hsize, 0, { 1,0,0, 0 });
    }
#endif
    for (int y = 0; y < 2; ++y)
    {
        for (int x = 0; x < 3; ++x)
        {
            sprite_render(sprTerrain, x * 64, 600 + (y * 35), 1, 1, 64, 0, 64, 64);
        }
    }
    for (int y = 0; y < 2; ++y)
    {
        for (int x = 0; x < 24; ++x)
        {
            sprite_render(sprTerrain, 64 * x, 635 + (64 * (y + 1)), 1, 1, 64, 0, 64, 64);
        }
    }


    // ��
    sprite_render(sprBox1, stage1[4].position.x, stage1[4].position.y);
    // �g���b�R
    sprite_render(sprTrolley, stage1[3].position.x, stage1[3].position.y, 1, 1, stage1[3].elec * 178, 0, 177, 177);
   
    // �G���x�[�^�[
    sprite_render(sprEV, stage1[6].position.x - 5, stage1[6].position.y - 650);

    // playerEv
    if (door.end)
        sprite_render(sprEvPlayer, EvPlayer.x - 5, EvPlayer.y);

    // ��
    sprite_render(sprDoor, stage1[6].position.x, stage1[6].position.y, 1, 1, stage1[6].texPos.x, stage1[6].texPos.y, stage1[6].texSize.x, stage1[6].texSize.y);

    // �d�C
    if (Elec.exist)
        sprite_render(sprElec, Elec.pos.x, Elec.pos.y, 0.5f, 0.5f, 0, 0, 128, 128, 64, 64);

    player.Render();

    // ��
    sprite_render(sprDoor, door.position.x, door.position.y, 1, 1, door.texPos.x, 177, door.texSize.x, door.texSize.y);

    // �|�[�Y���
    if (pause)
    {
        sprite_render(sprPause, 0, 0);
    }

#ifdef _DEBUG
    debug::setString("player%d", player.elec);
#endif
}
