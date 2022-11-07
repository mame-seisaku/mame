#include "all.h"

/*****�ϐ�*****/

stage stage1[STAGE1_MAX];


Sprite* spr1;
Sprite* sprBox1;
Sprite* sprTrolley;
VECTOR2 speed1;

extern VECTOR2 mousePos;
extern Sprite* sprElec; // �d�C

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
    safe_delete(spr1);
    safe_delete(sprBox1);
    safe_delete(sprTrolley);
    safe_delete(sprElec);
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

        spr1 = sprite_load(L"./Data/Images/stage0.png");
        sprBox1 = sprite_load(L"./Data/Images/box.png");
        sprTrolley = sprite_load(L"./Data/Images/trolley.png");

        sprElec = sprite_load(L"./Data/Images/elec.png");

        ++stage_state[1];
    case 1:
        ///// �p�����[�^�̐ݒ� /////

        for (int i = 0; i < STAGE1_MAX; ++i)
        {
            stage1[i] = {};
        }

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
        stage1[3].position = { 682,522 };
        stage1[3].pos = { 768,650 };
        stage1[3].hsize = { 90, 50 };
        stage1[3].type = 0;
        stage1[3].exist = true;
        // BOX
        stage1[4].position = { 890,523 };
        stage1[4].pos = { 979,612.5f };
        stage1[4].hsize = { 89, 88.5f };
        stage1[4].type = 0;
        stage1[4].exist = true;
        // stop
        stage1[5].pos = { 52,658 };
        stage1[5].hsize = { 42, 42 };
        stage1[5].type = 0;
        stage1[5].exist = true;

        // �d�C
        Elec = {};

        ++stage_state[1];
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
        if (mousePos.x > stage1[3].pos.x - 80 && mousePos.y > stage1[3].pos.y - 50 && mousePos.x < stage1[3].pos.x + 80 && mousePos.y < stage1[3].pos.y + 50)
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
                // ��������
                if (Elec.pos.x >= ElecPos.x || Elec.pos.y >= ElecPos.y)
                {
                    player.elec = false;    // �v���C���[�̓d�C����
                    Elec.exist = false;
                    stage1[3].elec = true;
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
                    stage1[3].elec = true;
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
                    //if (stop == false) {
                if (stage1[i].type == 0 && stage1[i].elec)
                {
                    player.pos.x += speed1.x;
                }
                //}

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
        if (player.elec == true) {
            player.pos.x += player.speed.x;
        }
        else if (stage1[3].elec == true) {
            stage1[3].pos.x += speed1.x;
            stage1[3].position.x = stage1[3].pos.x - 86;

        }

        // ���E�̂߂荞�݃`�F�b�N
        for (int i = 0; i < STAGE0_MAX; ++i)
        {
            if (player.elec == true) {
                if (hitCheck(&player, &stage1[i]))
                {
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

/// <summary>
/// �`�揈��
/// </summary>
void stage1_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(spr1, 0, 0);

    player.Render();
    
#ifdef _DEBUG
    for (int i = 0; i < STAGE1_MAX; ++i)
    {
        primitive::rect(stage1[i].pos, stage1[i].hsize * 2, stage1[i].hsize, 0, { 1,0,0,1 });
    }
#endif

    // ��
    sprite_render(sprBox1, stage1[4].position.x, stage1[4].position.y);
    // �g���b�R
    sprite_render(sprTrolley, stage1[3].position.x, stage1[3].position.y, 1, 1, stage1[3].elec * 178, 0, 177, 177);
   
    // �d�C
    if (Elec.exist)
        sprite_render(sprElec, Elec.pos.x, Elec.pos.y, 0.5f, 0.5f, 0, 0, 128, 128, 64, 64);

#ifdef _DEBUG
    debug::setString("player%d", player.elec);
   

#endif
}
