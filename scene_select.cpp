#include "all.h"

/*****�ϐ�*****/
int select_state;

Sprite* sprSelect;
Sprite* sprLock;

void select_init()
{
    select_state = 0;
}

void select_deinit()
{
    safe_delete(sprSelect);
    safe_delete(sprLock);
}

void select_update()
{
    switch (select_state)
    {
    case 0:
        ///// �����ݒ� /////
        sprSelect = sprite_load(L"./Data/Images/select.png");
        sprLock = sprite_load(L"./Data/Images/lock.png");

        ++select_state;
    case 1:
        ///// �p�����[�^�̐ݒ�
        ++select_state;
    case 2:
        ///// �ʏ펞 /////
        
        // ��ʐ؂�ւ�
        if (TRG(0) & PAD_SELECT)
        {
            nextScene = SCENE::TITLE;
            break;
        }
        if (TRG(0) & PAD_START)
        {
            nextScene = SCENE::GAME;
            break;
        }

        // �}�E�X�J�[�\��
#ifdef _DEBUG
        std::ostringstream oss;                                 // ������X�g���[��
        POINT point;                                            // �ʒu�p�̕ϐ���錾����
        GetCursorPos(&point);                                   // �X�N���[�����W���擾����
        ScreenToClient(window::getHwnd(), &point);              // �N���C�A���g���W�ɕϊ�����
        oss << "(x=" << point.x << " y=" << point.y << ")";
        SetWindowTextA(window::getHwnd(), oss.str().c_str());   // �^�C�g���o�[�ɂ�\��������
#endif

        break;
    }
}

void select_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(sprSelect, 0, 0);


    sprite_render(sprLock, 175.0f, 335.0f, 1.0f, 1.0f, 0, 0);//, 105.0f, 105.0f, 52.5f, 52.5f);
}
