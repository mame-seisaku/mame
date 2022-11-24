#include "all.h"

/*****�ϐ�*****/
int tutorial_state;
int Tstate;

bool T_p;

obj2d T_pos;
obj2d T_jump;
VECTOR2 T_texPos[3];

stage tutorialS[TUTORIAL_MAX];

Sprite* sprJump;
Sprite* sprB;
Sprite* sprTutorial;
Sprite* sprTWord;
Sprite* sprWord;
Sprite* sprTutorialP;   // �`���[�g���A���v���C���[
Sprite* sprKeyW;    // AD�L�[

extern Sprite* sprBoxMove; // �������锠

extern VECTOR2 mousePos;
extern stage door;
extern Sprite* sprElec; // �d�C
extern Sprite* sprDoor; // �h�A

/// <summary>
/// �����ݒ�
/// </summary>
void tutorial_init()
{
    tutorial_state = 0;
    //Tstate = 0;
}

/// <summary>
/// �I������
/// </summary>
void tutorial_deinit()
{
    player.Dinit();

    safe_delete(sprTutorial);
    safe_delete(sprTWord);
    safe_delete(sprWord);
    safe_delete(sprB);

    safe_delete(sprEvPlayer);
    safe_delete(sprJump);
    safe_delete(sprBoxMove);
    safe_delete(sprKeyW);
    safe_delete(sprTutorialP);
    safe_delete(sprElec);
    safe_delete(sprDoor);
    safe_delete(sprEV);
    safe_delete(sprMouse);
    safe_delete(sprTerrain);
    safe_delete(sprPause);

    music::stop(game_bgm);
}

/// <summary>
/// �X�V����
/// </summary>
void tutorial_update()
{
    switch (tutorial_state)
    {
    case 0:
        ///// ������ /////
        player.Init();

        sprTutorial = sprite_load(L"./Data/Images/05.png");

        sprJump = sprite_load(L"./Data/Images/jump.png");
        sprBoxMove = sprite_load(L"./Data/Images/boxMove.png");
        sprKeyW = sprite_load(L"./Data/Images/ad.png");
        sprTutorialP = sprite_load(L"./Data/Images/player1.png");
        sprB = sprite_load(L"./Data/Images/B.png");
        sprTWord = sprite_load(L"./Data/Images/Tword.png");
        sprWord = sprite_load(L"./Data/Images/word.png");
        sprElec = sprite_load(L"./Data/Images/elec.png");
        sprDoor = sprite_load(L"./Data/Images/door.png");
        sprEV = sprite_load(L"./Data/Images/EV.png");
        sprEvPlayer = sprite_load(L"./Data/Images/p.png");
        sprMouse = sprite_load(L"./Data/Images/mouse.png");
        sprTerrain = sprite_load(L"./Data/Images/terrain.png");
        sprPause = sprite_load(L"./Data/Images/pause.png");

        ++tutorial_state;
    case 1:
        ///// �p�����[�^�̐ݒ�
        
        // �|�[�Y
        pause = false;

        // �d�C�p
        ElecPos = {};

        for (int i = 0; i < TUTORIAL_MAX; ++i)
        {
            tutorialS[i] = {};
        }

        // type
        // 0 ��
        // 1 ��
        // 2 movebox

        // ��
        tutorialS[0].position = { 0,0 };
        tutorialS[0].pos = { 768,764 };
        tutorialS[0].hsize = { 768, 64 };
        tutorialS[0].type = 0;
        tutorialS[0].exist = true;

        // ��
        tutorialS[1].position = { 1239,530 };
        tutorialS[1].pos = { 1330,620 };
        tutorialS[1].hsize = { 80, 89 };
        tutorialS[1].texPos = {};
        tutorialS[1].texSize = { 178,177 };
        tutorialS[1].type = 1;
        tutorialS[1].exist = true;
        tutorialS[1].open = false;

        // movebox
        tutorialS[2].position = { 800, 610 };
        tutorialS[2].pos = { tutorialS[2].position.x + 44,tutorialS[2].position.y + 44 };
        tutorialS[2].texPos.x = 90;
        tutorialS[2].hsize = { 44,44 };
        tutorialS[2].type = 2;
        tutorialS[2].exist = true;
                

        // �h�A�Ō�
        door = {};

        // �d�C
        Elec = {};

        // EvPlayer
        EvPlayer = { tutorialS[1].position.x, tutorialS[1].position.y + 100 };

        // �}�E�X�J�[�\��
        MouseTexPos = {};


        // �v���C���[
        T_pos = {};
        T_pos.pos = { 250, 270 };
        T_pos.texSize = { 84,100 };
        T_p = true;

        // �W�����v
        T_jump = {};
        T_jump.pos = { 900 ,190 };
        T_jump.texSize = { 84,170 };

        // ����
        T_texPos[0] = {};
        T_texPos[1] = { 16,0 };
        T_texPos[2] = { 0,16 };
        


        // BGM
        music::play(game_bgm, true);

        ++tutorial_state;
    case 2:
        ///// �ʏ펞 /////

        if (door.end)
        {
            player.pos.y = EvPlayer.y - 45;
            EvPlayer.y -= STAGE_MOVE;
        }
        if (EvPlayer.y < -200)
        {
            nextScene = SCENE::SELECT;
            break;
        }

        switch (Tstate)
        {
        case 0:
            JudgeTutorial = 1;
            if (TRG(0) & PAD_L3)Tstate += 1;
            break;
        case 1:
            // �`���[�g���A����I��
            if (TRG(0) & PAD_L3)Tstate += 1;
            break;
        case 2:
            if (TRG(0) & PAD_L3)Tstate += 1;
            break;
        case 3:
            if (TRG(0) & PAD_L3)Tstate += 1;
            break;
        case 4:
            if (TRG(0) & PAD_L3)Tstate += 1;
            break;
        case 5:
            if (TRG(0) & PAD_L3)Tstate += 1;
            break;
        case 6: // �v���C���[����
            if (TRG(0) & PAD_L3)Tstate += 1;
            if (T_p)
            {
                T_texPos[0].x = 48;
                T_texPos[1].x = 16;
                T_pos.pos.x += 5;
            }
            else
            {
                T_texPos[0].x = 0;
                T_texPos[1].x = 64;
                T_pos.pos.x -= 5;
            }

            if (T_pos.pos.x > 400)T_p = false;
            if (T_pos.pos.x < 100)T_p = true;

            if (T_jump.anime == 0 || T_jump.anime == 1 || T_jump.anime == 2)
            {
                T_texPos[2].x = 48;
            }
            else
            {
                T_texPos[2].x = 0;
            }

            anime(&T_pos, 6, 10, true, 1);
            anime(&T_jump, 19, 2, true, 1);

            break;
        case 7:
            if (TRG(0) & PAD_L3)Tstate += 1;
            break;
        case 8:
            if (TRG(0) & PAD_L3)Tstate += 1;
            if (mousePos.x > 600 && mousePos.y > 276 && mousePos.x < 690 && mousePos.y < 366||
                mousePos.x > 800 && mousePos.y > 276 && mousePos.x < 890 && mousePos.y < 366)
            {
                MouseTexPos.x = 100;
            }
            else
            {
                MouseTexPos.x = 0;
            }

            break;
        case 9:
            if (TRG(0) & PAD_L3)Tstate += 1;
            if (mousePos.x > 600 && mousePos.y > 276 && mousePos.x < 690 && mousePos.y < 366 ||
                mousePos.x > 800 && mousePos.y > 276 && mousePos.x < 890 && mousePos.y < 366)
            {
                MouseTexPos.x = 100;
            }
            else
            {
                MouseTexPos.x = 0;
            }

            break;
        case 10:
            if (TRG(0) & PAD_L3)Tstate += 1;
            if (mousePos.x > 600 && mousePos.y > 276 && mousePos.x < 690 && mousePos.y < 366 ||
                mousePos.x > 800 && mousePos.y > 276 && mousePos.x < 890 && mousePos.y < 366)
            {
                MouseTexPos.x = 100;
            }
            else
            {
                MouseTexPos.x = 0;
            }
            break;
        case 11:
            if (TRG(0) & PAD_L3)Tstate += 1;
            if (mousePos.x > 600 && mousePos.y > 276 && mousePos.x < 690 && mousePos.y < 366 ||
                mousePos.x > 800 && mousePos.y > 276 && mousePos.x < 890 && mousePos.y < 366)
            {
                MouseTexPos.x = 100;
            }
            else
            {
                MouseTexPos.x = 0;
            }
            break;
        case 12:

            if (mousePos.x > 800 && mousePos.y > 610 && mousePos.x < 890 && mousePos.y < 700)
            {
                // �d�C���΂�
                if (TRG(0) & PAD_L3)
                {
                    // �v���C���[�ɓd�C�������
                    if (!Elec.exist && player.elec)
                    {
                        SetElecMove();
                    }
                }

                MouseTexPos.x = 100;
            }
            else
            {
                MouseTexPos.x = 0;
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
                            tutorialS[2].elec = true;
                            Tstate = 13;
                        }
                    }
                    else
                    {
                        // ��������
                        if (Elec.pos.x >= ElecPos.x)
                        {
                            player.elec = false;    // �v���C���[�̓d�C����
                            Elec.exist = false;
                            tutorialS[2].elec = true;
                            Tstate = 13;
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
                            tutorialS[2].elec = true;
                            Tstate = 13;
                        }
                    }
                    else
                    {
                        // ��������
                        if (Elec.pos.x <= ElecPos.x)
                        {
                            player.elec = false;    // �v���C���[�̓d�C����
                            Elec.exist = false;
                            tutorialS[2].elec = true;
                            Tstate = 13;
                        }
                    }
                }
            }
            break;
        case 13:
            if (TRG(0) & PAD_L3)Tstate += 1;
            break;
        case 14:
            if (TRG(0) & PAD_L3)Tstate += 1;
            break;
        case 15:
            if (TRG(0) & PAD_L3)Tstate += 1;
            break;
        case 16:
            if (mousePos.x > 800 && mousePos.y > 610 && mousePos.x < 890 && mousePos.y < 700)
            {
                // �d�C���
                if (TRG(0) & PAD_R3 && !player.elec)
                {
                    Elec.exist = false;
                    tutorialS[2].elec = false;
                    player.elec = true;
                    Tstate = 17;
                }

                MouseTexPos.x = 100;
            }
            else
            {
                MouseTexPos.x = 0;
            }
            break;
        case 17:
            if (TRG(0) & PAD_L3)Tstate += 1;
            break;
        case 18:
            if (TRG(0) & PAD_L3)Tstate += 1;
            break;
        case 19:
            if (TRG(0) & PAD_L3)Tstate += 1;
            break;
        case 20:
            if (TRG(0) & PAD_L3)Tstate += 1;
            break;
        case 21:
            if (mousePos.x > 800 && mousePos.y > 610 && mousePos.x < 890 && mousePos.y < 700)
            {

                // �d�C���΂�
                if (TRG(0) & PAD_L3)
                {
                    // �v���C���[�ɓd�C�������
                    if (!Elec.exist && player.elec)
                    {
                        SetElecMove();
                    }
                }
                // �d�C���
                if (TRG(0) & PAD_R3 && !player.elec)
                {
                    Elec.exist = false;
                    tutorialS[2].elec = false;
                    player.elec = true;
                }

                MouseTexPos.x = 100;
            }
            else
            {
                MouseTexPos.x = 0;
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
                            tutorialS[2].elec = true;
                        }
                    }
                    else
                    {
                        // ��������
                        if (Elec.pos.x >= ElecPos.x)
                        {
                            player.elec = false;    // �v���C���[�̓d�C����
                            Elec.exist = false;
                            tutorialS[2].elec = true;
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
                            tutorialS[2].elec = true;
                        }
                    }
                    else
                    {
                        // ��������
                        if (Elec.pos.x <= ElecPos.x)
                        {
                            player.elec = false;    // �v���C���[�̓d�C����
                            Elec.exist = false;
                            tutorialS[2].elec = true;
                        }
                    }
                }
            }
            break;
        }

        // ��ʐ؂�ւ�
        if (TRG(0) & PAD_SELECT)
        {
            nextScene = SCENE::TITLE;
            break;
        }
        // �����`���[�g���A���I��

        if (!pause)
        {
            player.Update({ 100,200 });

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
#endif
            
            // ���A�j��
            if (tutorialS[1].open)
                anime(&tutorialS[1], 7, 10, false, 0);

            // �N���A����
            if (tutorialS[1].end && tutorialS[1].one && !door.close)
            {
                player.clear = true;
                door = tutorialS[1];
                door.state = 0;
                door.close = true;
            }

            if (player.clear)
            {
                player.pos.x = tutorialS[1].position.x + 71;    // �h�A�̈ʒu�Ɉړ�
                // �d�C��߂�
                player.elec = true;
                for (int i = 0; i < TUTORIAL_MAX; ++i)
                {
                    tutorialS[i].elec = false;
                }

                Elec.exist = false;
                player.elec = true;

                // �����܂�
                anime(&door, 7, 10, false, 0);
            }


            // �ʒu�ɃX�s�[�h�𑫂�
            player.pos.y += player.speed.y;

            // �㉺�̂߂荞�݃`�F�b�N
            for (int i = 0; i < TUTORIAL_MAX; ++i)
            {
                if (hitCheck(&player, &tutorialS[i]))
                {
                    if (tutorialS[i].type == 1)
                    {
                        if(Tstate==21)
                            tutorialS[i].open = true;
                        continue;
                    }

                    // �߂荞�ݑ΍�		// �����蔻��
                    float dist;
                    if (player.speed.y >= 0)
                        dist = check(&player, &tutorialS[i], DIR::DOWN);
                    else
                        dist = check(&player, &tutorialS[i], DIR::UP);
                    player.pos.y += dist;
                    player.speed.y = 0;
                }
            }

            // �ʒu�ɃX�s�[�h�𑫂�
            player.pos.x += player.speed.x;

            // ���E�̂߂肱�݃`�F�b�N
            for (int i = 0; i < TUTORIAL_MAX; ++i)
            {
                if (hitCheck(&player, &tutorialS[i]))
                {
                    if (tutorialS[i].type == 1)
                    {
                        if (Tstate == 21)
                            tutorialS[i].open = true;
                        continue;
                    }

                    // �߂荞�ݑ΍�		// �����蔻��
                    float dist;
                    if (player.speed.x >= 0)
                        dist = check(&player, &tutorialS[i], DIR::RIGHT);
                    else
                        dist = check(&player, &tutorialS[i], DIR::LEFT);
                    player.pos.x += dist;
                    player.speed.x = 0;
                }
            }
        }

        tutorialS[2].texPos.x = tutorialS[2].elec ? 0 : 90;

        break;
    }
}

/// <summary>
/// �`�揈��
/// </summary>
void tutorial_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(sprTutorial, 0, 0);

    // �n�`�`��
#ifdef _DEBUG
    for (int i = 0; i < TUTORIAL_MAX; ++i)
    {
        primitive::rect(tutorialS[i].pos, tutorialS[i].hsize * 2, tutorialS[i].hsize, 0, { tutorialS[i].color.x,tutorialS[i].color.y,tutorialS[i].color.z,1 });
    }
#endif

    for (int y = 0; y < 2; ++y)
    {
        for (int x = 0; x < 24; ++x)
        {
            sprite_render(sprTerrain, 64 * x, 640 + (64 * (y + 1)), 1, 1, 64, 0, 64, 64);
        }
    }

    // �G���x�[�^�[
    sprite_render(sprEV, tutorialS[1].position.x - 5, tutorialS[1].position.y - 653);

    // ��
    sprite_render(sprDoor, tutorialS[1].position.x, tutorialS[1].position.y, 1, 1, tutorialS[1].texPos.x, tutorialS[1].texPos.y, tutorialS[1].texSize.x, tutorialS[1].texSize.y);

    // �d�C
    if (Elec.exist)
        sprite_render(sprElec, Elec.pos.x, Elec.pos.y, 1, 1, 0, 0, 128, 128, 64, 64);

    player.Render();

    // playerEv
    if (door.end)
        sprite_render(sprEvPlayer, EvPlayer.x + 35, EvPlayer.y);

    // ��
    sprite_render(sprDoor, door.position.x, door.position.y, 1, 1, door.texPos.x, 177, door.texSize.x, door.texSize.y);

    // movebox
    sprite_render(sprBoxMove, tutorialS[2].position.x, tutorialS[2].position.y, 1, 1, tutorialS[2].texPos.x, 0, 90, 90);               // ������

    // word 
    switch (Tstate)
    {
    case 0: // ���`���[�g���A����΂����Ƃ����ˁH
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 0, 1, 1, 1499.9f, 0, 1536, 724);
        break;
    case 1: // ����ɂ���
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 0, 1, 1, 0, 0, 1536, 724);
        break;
    case 2: // �`���[�g���A���ł�
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 0, 1, 1, 2999.8f, 0, 1536, 724);
        break;
    case 3: // ���̍r��ʂĂ����E�œd�͂��g����̂����Ȃ�����
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 0, 1, 1, 4499.7f, 0, 1536, 724);
        break;
    case 4: // �������g�̓d�C�𐢊E�ɕ����^����������E�o���悤
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 0, 1, 1, 5999.6f, 0, 1536, 724);
        break;
    case 5: // �v���C���[�̑�������������
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 0, 1, 1, 7499.5f, 0, 1536, 724);

        sprite_render(sprTutorialP, 768, 270, 1, 1, 0, 0, 84, 100, 42, 50);                              // �v���C���[
        break;
    case 6: // AD�L�[�ŉ��Ɉړ��A�X�y�[�X�ŃW�����v�\
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 0, 1, 1, 8999.4f, 0, 1536, 724);

        sprite_render(sprTerrain, 1421, 366, 1, 1, 64, 0, 64, 64);              // �n�`   
        for (int i = 0; i < 22; ++i)
        {
            sprite_render(sprTerrain, 51 + (64 * i), 366, 1, 1, 64, 0, 64, 64); // �n�`
        }
        sprite_render(sprTutorialP, T_pos.pos.x, 270, 1, 1, T_pos.texPos.x, T_pos.texPos.y, 84, 100);    // ���ɓ����v���C���[
        sprite_render(sprJump, T_jump.pos.x,T_jump.pos.y, 1, 1, T_jump.texPos.x, 0, 84, 170);                              // �c�ɓ����v���C���[
        sprite_render(sprKeyW, 200, 150, 4, 4, T_texPos[0].x, T_texPos[0].y, 16, 16);   // A
        sprite_render(sprKeyW, 300, 150, 4, 4, T_texPos[1].x, T_texPos[1].y, 16, 16);   // D
        sprite_render(sprKeyW, 620, 150, 4, 4, T_texPos[2].x, T_texPos[2].y, 32, 16);   // space

        break;
    case 7: // ����ł͓d�C�𕪂��^����Ƃ��炩��n�߂��
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 0, 1, 1, 10499.3f, 0, 1536, 724);
        break;
    case 8: // ����͒P���B�}�E�X�𓮂��������v������Ƃ����T����
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 0, 1, 1, 11999.2f, 0, 1536, 724);

        sprite_render(sprTerrain, 1421, 366, 1, 1, 64, 0, 64, 64);              // �n�`   
        for (int i = 0; i < 22; ++i)
        {
            sprite_render(sprTerrain, 51 + (64 * i), 366, 1, 1, 64, 0, 64, 64); // �n�`
        }
        sprite_render(sprBoxMove, 600, 276, 1, 1, 90, 0, 90, 90);               // ������
        sprite_render(sprBoxMove, 800, 276, 1, 1, 90, 0, 90, 90);               // ������
        sprite_render(sprMouse, 200,200, 1, 1, 0, 0, 100, 100);                 // �}�E�X�J�[�\��
        sprite_render(sprMouse, 300,200, 1, 1, 100, 0, 100, 100);               // �}�E�X�J�[�\��
        break;
    case 9: // �����v�������Ă���Ƃ��ɍ��N���b�N�œd�C�𕪂��^���邱�Ƃ��o����
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 0, 1, 1, 13499.1f, 0, 1536, 724);

        sprite_render(sprTerrain, 1421, 366, 1, 1, 64, 0, 64, 64);              // �n�`   
        for (int i = 0; i < 22; ++i)
        {
            sprite_render(sprTerrain, 51 + (64 * i), 366, 1, 1, 64, 0, 64, 64); // �n�`
        }
        sprite_render(sprBoxMove, 600, 276, 1, 1, 90, 0, 90, 90);               // ������
        sprite_render(sprBoxMove, 800, 276, 1, 1, 90, 0, 90, 90);               // ������
        sprite_render(sprMouse, 200, 200, 1, 1, 0, 0, 100, 100);                 // �}�E�X�J�[�\��
        sprite_render(sprMouse, 300, 200, 1, 1, 100, 0, 100, 100);               // �}�E�X�J�[�\��
        break;
    case 10: // �d�C�𕪂��^����Ƃ��̃I�u�W�F�N�g�𓮂������Ƃ��o���܂� 
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 20, 1, 1, 0, 724, 1536, 724);

        sprite_render(sprTerrain, 1421, 366, 1, 1, 64, 0, 64, 64);              // �n�`   
        for (int i = 0; i < 22; ++i)
        {
            sprite_render(sprTerrain, 51 + (64 * i), 366, 1, 1, 64, 0, 64, 64); // �n�`
        }
        sprite_render(sprBoxMove, 600, 276, 1, 1, 90, 0, 90, 90);               // ������
        sprite_render(sprBoxMove, 800, 276, 1, 1, 90, 0, 90, 90);               // ������
        sprite_render(sprMouse, 200, 200, 1, 1, 0, 0, 100, 100);                 // �}�E�X�J�[�\��
        sprite_render(sprMouse, 300, 200, 1, 1, 100, 0, 100, 100);               // �}�E�X�J�[�\��
        break;
    case 11: // ����ł͑�������Ă݂܂��傤
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 20, 1, 1, 1499.9f, 724, 1536, 724);

        sprite_render(sprTerrain, 1421, 366, 1, 1, 64, 0, 64, 64);              // �n�`   
        for (int i = 0; i < 22; ++i)
        {
            sprite_render(sprTerrain, 51 + (64 * i), 366, 1, 1, 64, 0, 64, 64); // �n�`
        }
        sprite_render(sprBoxMove, 600, 276, 1, 1, 90, 0, 90, 90);               // ������
        sprite_render(sprBoxMove, 800, 276, 1, 1, 90, 0, 90, 90);               // ������
        sprite_render(sprMouse, 200, 200, 1, 1, 0, 0, 100, 100);                 // �}�E�X�J�[�\��
        sprite_render(sprMouse, 300, 200, 1, 1, 100, 0, 100, 100);               // �}�E�X�J�[�\��
        break;
    case 12:
        break;
    case 13: // �悭�ł��܂����B���Ȃ��͂�������
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 20, 1, 1, 2999.8f, 724, 1536, 724);
        break;
    case 14: // �������g�ɓd�C���Ȃ���Ԃł͓����Ȃ��̂ŋC��t����悤��
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 20, 1, 1, 4499.7f, 724, 1536, 724);
        break;
    case 15: // �E�N���b�N�œd�C��������邱�Ƃ��o���܂�
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 20, 1, 1, 5999.6f, 724, 1536, 724);
        break;
    case 16:
        break;
    case 17: // �悭�ł��܂����B���Ȃ��͓V�˂ł�
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 20, 1, 1, 7499.5f, 724, 1536, 724);
        break;
    case 18: // �����V�X�e���͗����ł��܂����ˁH
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 20, 1, 1, 8999.4f, 724, 1536, 724);
        break;
    case 19: // ���Ƃ͂Ђ��������ڎw�������ł�
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 20, 1, 1, 10499.3f, 724, 1536, 724);

        sprite_render(sprTerrain, 1421, 366, 1, 1, 64, 0, 64, 64);              // �n�`   
        for (int i = 0; i < 22; ++i)
        {
            sprite_render(sprTerrain, 51 + (64 * i), 366, 1, 1, 64, 0, 64, 64); // �n�`
        }
        sprite_render(sprDoor, 700, 197, 1, 1, 0, 0, tutorialS[1].texSize.x, tutorialS[1].texSize.y);
        break;
    case 20: // good luck have fun
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1536, 824, 0, 0, 0, 1, 1, 1, 0.4f);
        sprite_render(sprTWord, 0, 0, 1, 1, 1536, 0, 1536, 724);
        sprite_render(sprTWord, 0, 0);
        sprite_render(sprWord, 0, 20, 1, 1, 11999.2f, 724, 1536, 724);

        sprite_render(sprTerrain, 1421, 366, 1, 1, 64, 0, 64, 64);              // �n�`   
        for (int i = 0; i < 22; ++i)
        {
            sprite_render(sprTerrain, 51 + (64 * i), 366, 1, 1, 64, 0, 64, 64); // �n�`
        }
        sprite_render(sprDoor, 700, 197, 1, 1, 0, 0, tutorialS[1].texSize.x, tutorialS[1].texSize.y);
        break;
    }



    // �}�E�X�J�[�\��
    sprite_render(sprMouse, mousePos.x, mousePos.y, 1, 1, MouseTexPos.x, MouseTexPos.y, 100, 100, 50, 50);

    // �|�[�Y���
    if (pause)
    {
        sprite_render(sprPause, 0, 0);
    }
}
