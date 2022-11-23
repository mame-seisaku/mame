#include "all.h"

int zukan_state;

int Z_color[10];

int Z_page;
int Z_explanation;

Sprite* sprZukan;   // �}��
Sprite* sprV;   // �₶�邵
Sprite* sprZ_name;

extern Sprite* sprStage0;       // �w�i
extern Sprite* sprBelt;         // �x���g����
extern Sprite* sprGear;         // �M�A
extern Sprite* sprBox;          // �f�J��
extern Sprite* sprSyoukouki;    // ���~�@
extern Sprite* sprBoxMove;      // �������锠
extern Sprite* sprSwitch;       // �X�C�b�`
extern Sprite* sprTrolley;      // �g���b�R
extern Sprite* sprDoor2;        // �����h�A


void zukan_init()
{
    zukan_state = 0;
}

void zukan_deinit()
{
    safe_delete(sprZukan);

    safe_delete(sprZ_name);

    safe_delete(sprStage0);
    safe_delete(sprBelt);
    safe_delete(sprGear);
    safe_delete(sprBox);
    safe_delete(sprSyoukouki);  
    safe_delete(sprBoxMove);
    safe_delete(sprSwitch);
    safe_delete(sprTrolley);
    safe_delete(sprDoor2);
    safe_delete(sprV);

    // extern
    safe_delete(sprEvPlayer);   // evplayer
    safe_delete(sprEV);         // �G���x�[�^�[
    safe_delete(sprPause);      // �|�[�Y
    safe_delete(sprWhite);      // �|�[�Y��
    safe_delete(sprTerrain);    // �n�`
    safe_delete(sprUI);         // UI
    safe_delete(sprElec);       // �d�C
    safe_delete(sprDoor);       // �h�A
    safe_delete(sprMouse);      // �}�E�X�J�[�\��
}

void zukan_update()
{
    switch (zukan_state)
    {
    case 0:
        ///// �����ݒ� //////
        sprZukan = sprite_load(L"./Data/Images/zukan.png");

        sprZ_name = sprite_load(L"./Data/Images/z_name.png");

        sprStage0 = sprite_load(L"./Data/Images/04.png");
        sprBelt = sprite_load(L"./Data/Images/Belt.png");
        sprGear = sprite_load(L"./Data/Images/gear.png");
        sprBox = sprite_load(L"./Data/Images/box.png");
        sprSyoukouki = sprite_load(L"./Data/Images/syoukouki2.png");
        sprBoxMove = sprite_load(L"./Data/Images/boxMove.png");
        sprSwitch = sprite_load(L"./Data/Images/switch.png");
        sprTrolley = sprite_load(L"./Data/Images/trolley.png");
        sprDoor2 = sprite_load(L"./Data/Images/door2.png");
        sprV = sprite_load(L"./Data/Images/v.png");

        sprEvPlayer = sprite_load(L"./Data/Images/p.png");
        sprEV = sprite_load(L"./Data/Images/EV.png");
        sprPause = sprite_load(L"./Data/Images/pause.png");
        sprWhite = sprite_load(L"./Data/Images/white.png");
        sprTerrain = sprite_load(L"./Data/Images/terrain.png");
        sprUI = sprite_load(L"./Data/Images/UI.png");
        sprElec = sprite_load(L"./Data/Images/elec.png");
        sprDoor = sprite_load(L"./Data/Images/door.png");
        sprMouse = sprite_load(L"./Data/Images/mouse.png");

        ++zukan_state;
    case 1:
        ///// �p�����[�^�[�̐ݒ� /////

        for (int i = 0; i < 10; ++i)
        {
            Z_color[i] = 1;
        }

        // �y�[�W
        Z_page = 0;
        Z_explanation = -1;

        ++zukan_state;
    case 2:
        ///// �ʏ펞 /////

        // �y�[�W�؂�ւ�
        if (mousePos.x > 1300 && mousePos.y > 600 && mousePos.x < 1420 && mousePos.y < 700 && Z_page == 0)
        {
            if (TRG(0) & PAD_L3)Z_page += 1;
        }
        if (mousePos.x > 1150 && mousePos.y > 600 && mousePos.x < 1270 && mousePos.y < 700 && Z_page == 1)
        {
            if (TRG(0) & PAD_L3)Z_page -= 1;
        }

        if (TRG(0) & PAD_L3)
        {
            // �Ђ��肤��
            if (mousePos.x > 765 && mousePos.y > 90 && mousePos.x < 1070 && mousePos.y < 280)
            {
                Z_explanation = 0;
            }
            // �݂�����
            if (mousePos.x > 1130 && mousePos.y > 90 && mousePos.x < 1450 && mousePos.y < 280)
            {
                Z_explanation = 1;
            }
            // �Ђ���܂�Ȃ�
            if (mousePos.x > 765 && mousePos.y > 315 && mousePos.x < 1070 && mousePos.y < 505)
            {
                Z_explanation = 2;
            }
            // �݂��܂�Ȃ�
            if (mousePos.x > 1130 && mousePos.y > 315 && mousePos.x < 1450 && mousePos.y < 505)
            {
                Z_explanation = 3;
            }
            if (mousePos.x > 765 && mousePos.y > 540 && mousePos.x < 1070 && mousePos.y < 740)
            {
                Z_explanation = 4;
            }
        }
       

        if (TRG(0) & PAD_START)
        {
            nextScene = SCENE::TITLE;
            break;
        }

        switch (PossibleStage)
        {
        case 0:
            Z_color[0] = 0;
        case 1:
            Z_color[1] = 0;
        case 2:
            Z_color[2] = 0;
        case 3:
            Z_color[3] = 0;
        case 4:
            Z_color[4] = 0;
        case 5:
            Z_color[5] = 0;
        case 6:
            Z_color[6] = 0;
        case 7:
            Z_color[7] = 0;
        case 8:
            Z_color[8] = 0;
        case 9:
            Z_color[9] = 0;
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

        break;
    }
}

void zukan_render()
{
    GameLib::clear(1, 1, 1);

    GameLib::sprite_render(sprStage0, 0, 0);
    GameLib::sprite_render(sprZukan, 0, 0);

    switch (Z_explanation)
    {
    case 0:
        GameLib::sprite_render(sprBelt, 108, 580, 1, 1, 0, 0, 620, 124, 0, 0, 0, Z_color[0], Z_color[0], Z_color[0]);
        GameLib::sprite_render(sprBelt, 108, 720, 1, -1, 0, 0, 620, 124, 0, 0, 0, Z_color[0], Z_color[0], Z_color[0]);
        for (int i = 0; i < 5; ++i)
        {
            GameLib::sprite_render(sprGear, 103 + (i * 120), 590, 1, 1, 0, 0, 120, 120, 0, 0, 0, Z_color[0], Z_color[0], Z_color[0]);
        }
        GameLib::sprite_render(sprGear, 703, 560, 1, 1, 0, 0, 25, 120, 0, 0, 0, Z_color[0], Z_color[0], Z_color[0]);

        GameLib::sprite_render(sprGear, 160, 170, 1, 1, 0, 0, 120, 120, 0, 0, 0, Z_color[0], Z_color[0], Z_color[0]);
        GameLib::sprite_render(sprGear, 160, 310, 1, 1, 120, 0, 120, 120, 0, 0, 0, Z_color[0], Z_color[0], Z_color[0]);
        GameLib::sprite_render(sprGear, 160, 450, 1, 1, 240, 0, 120, 120, 0, 0, 0, Z_color[5], Z_color[5], Z_color[5]);

        // �x���g�R���x�A�[
        if(Z_color[0]==0)
            sprite_render(sprZ_name, 0, 0, 1, 1, 0, 0, 1536, 824);
        else
            sprite_render(sprZ_name, 0, 0, 1, 1, 1536, 0, 1536, 824);


        break;
    case 1:
        GameLib::sprite_render(sprBox, 200, 450, 1, 1, 0, 0, 178, 177, 0, 0, 0, Z_color[0], Z_color[0], Z_color[0]);
        GameLib::sprite_render(sprBox, 450, 450, 1, 1, 0, 0, 178, 177, 0, 0, 0, Z_color[0], Z_color[0], Z_color[0]);

        // box
        if (Z_color[0] == 0)
            sprite_render(sprZ_name, 0, 0, 1, 1, 0, 0, 1536, 824);
        else
            sprite_render(sprZ_name, 0, 0, 1, 1, 1536 * 2, 0, 1536, 824);

        break;
    case 2:

        // box
        if (Z_color[0] == 0)
            sprite_render(sprZ_name, 0, 0, 1, 1, 0, 0, 1536, 824);
        else
            sprite_render(sprZ_name, 0, 0, 1, 1, 1536 * 3, 0, 1536, 824);

        break;
    case 3:

        // box
        if (Z_color[0] == 0)
            sprite_render(sprZ_name, 0, 0, 1, 1, 0, 0, 1536, 824);
        else
            sprite_render(sprZ_name, 0, 0, 1, 1, 1536 * 4, 0, 1536, 824);

        break;
    case 4:

        // box
        if (Z_color[1] == 0)
            sprite_render(sprZ_name, 0, 0, 1, 1, 0, 0, 1536, 824);
        else
            sprite_render(sprZ_name, 0, 0, 1, 1, 1536 * 5, 0, 1536, 824);

        break;
    default:
        break;
    }

    switch (Z_page)
    {
    case 0:
        // �x���g�R���x�A�[
        GameLib::sprite_render(sprGear, 765, 130, 1, 1, 0, 0, 120, 120, 0, 0, 0, Z_color[0], Z_color[0], Z_color[0]);
        GameLib::sprite_render(sprGear, 885, 130, 1, 1, 0, 0, 120, 120, 0, 0, 0, Z_color[0], Z_color[0], Z_color[0]);
        GameLib::sprite_render(sprGear, 1005, 130, 1, 1, 0, 0, 60, 120, 0, 0, 0, Z_color[0], Z_color[0], Z_color[0]);
        GameLib::sprite_render(sprBelt, 770, 120, 1, 1, 0, 0, 290, 124, 0, 0, 0, Z_color[0], Z_color[0], Z_color[0]);
        GameLib::sprite_render(sprBelt, 770, 260, 1, -1, 0, 0, 290, 124, 0, 0, 0, Z_color[0], Z_color[0], Z_color[0]);

        // �{�b�N�X
        GameLib::sprite_render(sprBox, 1200, 95, 1, 1, 0, 0, 178, 177, 0, 0, 0, Z_color[0], Z_color[0], Z_color[0]);

        // �n�`
        GameLib::sprite_render(sprTerrain, 820, 400, 1, 1, 0, 0, 192, 64, 0, 0, 0, Z_color[0], Z_color[0], Z_color[0]);

        // �ǂ�
        GameLib::sprite_render(sprDoor, 1200, 325, 1, 1, 0, 0, 177, 177, 0, 0, 0, Z_color[0], Z_color[0], Z_color[0]);

        // �g���b�R
        GameLib::sprite_render(sprTrolley, 820, 530, 1, 1, 0, 0, 178, 177, 0, 0, 0, Z_color[1], Z_color[1], Z_color[1]);

        // �₶�邵
        GameLib::sprite_render(sprV, 1300, 580, 0.5f, 0.5f);
        
        break;
    case 1:
        // movebox
        GameLib::sprite_render(sprBoxMove, 820, 160, 1, 1, 0, 0, 180, 90, 0, 0, 0, Z_color[2], Z_color[2], Z_color[2]);

        // �X�C�b�`
        GameLib::sprite_render(sprSwitch, 1200, 160, 1, 1, 0, 0, 64, 64, 0, 0, 0, Z_color[2], Z_color[2], Z_color[2]);
        GameLib::sprite_render(sprSwitch, 1300, 160, 1, 1, 0, 64, 64, 64, 0, 0, 0, Z_color[2], Z_color[2], Z_color[2]);

        // ����
        GameLib::sprite_render(sprDoor2, 850, 400, 1, 1, 1152, 0, 128, 64, 0, 0, 0, Z_color[2], Z_color[2], Z_color[2]);

        // ���~�@
        GameLib::sprite_render(sprSyoukouki, 1200, 300, 1, 1, 0, 0, 178, 177, 0, 0, 0, Z_color[3], Z_color[3], Z_color[3]);

        // ���~�@
        GameLib::sprite_render(sprSyoukouki, 830, 530, 1, 1, 0, 177, 178, 177, 0, 0, 0, Z_color[4], Z_color[4], Z_color[4]);

        // �₶�邵
        GameLib::sprite_render(sprV, 1280, 580, -0.5f, 0.5f);

        break;
    }

    // �}�E�X�J�[�\��
    GameLib::sprite_render(sprMouse, mousePos.x, mousePos.y, 1, 1, MouseTexPos.x, MouseTexPos.y, 100, 100, 50, 50);

}
