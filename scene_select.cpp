#include "all.h"

/*****�ϐ�*****/
int select_state;

int stage;

Sprite* sprSelect;
Sprite* sprLock;

// extern�錾
extern VECTOR2 mousePos;

/// <summary>
/// �����ݒ�
/// </summary>
void select_init()
{
    select_state = 0;
}

/// <summary>
/// �I������
/// </summary>
void select_deinit()
{
    safe_delete(sprSelect);
    safe_delete(sprLock);
}

/// <summary>
/// �X�V����
/// </summary>
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

        stage = 0;

        ++select_state;
    case 2:
        ///// �ʏ펞 /////
        
        // �}�E�X�J�[�\��
        std::ostringstream oss;                                 // ������X�g���[��
        POINT point;                                            // �ʒu�p�̕ϐ���錾����
        GetCursorPos(&point);                                   // �X�N���[�����W���擾����
        ScreenToClient(window::getHwnd(), &point);              // �N���C�A���g���W�ɕϊ�����
        mousePos.x = point.x;
        mousePos.y = point.y;
#ifdef _DEBUG
        oss << "(x=" << point.x << " y=" << point.y << ")";
        SetWindowTextA(window::getHwnd(), oss.str().c_str());   // �^�C�g���o�[�ɂ�\��������
#endif
      

        // ��ʐ؂�ւ�
        //����
        if (mousePos.x > 95 && mousePos.y > 250 && mousePos.x < 260 && mousePos.y < 390)
        {
            mouseClick(0);
            break;
        } 
        if (mousePos.x > 295 && mousePos.y > 250 && mousePos.x < 490 && mousePos.y < 390)
        {
            mouseClick(1);
            break;
        }



        if (TRG(0) & PAD_SELECT)
        {
            nextScene = SCENE::TITLE;
            break;
        }
        


        break;
    }
}

/// <summary>
/// �`�揈��
/// </summary>
void select_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(sprSelect, 0, 0);

    disp_key();


}

/// <summary>
/// ���������Ă�摜�`��
/// </summary>
void disp_key()
{
    switch (PossibleStage)
    {
        // ����
    case 0:
        sprite_render(sprLock, 375.0f, 320.0f, 1.0f, 1.0f, 0, 0, 105.0f, 105.0f, 52.5f, 52.5f);
    case 1:
        sprite_render(sprLock, 575.0f, 320.0f, 1.0f, 1.0f, 0, 0, 105.0f, 105.0f, 52.5f, 52.5f);
    case 2:
        sprite_render(sprLock, 775.0f, 320.0f, 1.0f, 1.0f, 0, 0, 105.0f, 105.0f, 52.5f, 52.5f);
    case 3:
        sprite_render(sprLock, 975.0f, 320.0f, 1.0f, 1.0f, 0, 0, 105.0f, 105.0f, 52.5f, 52.5f);
    case 4:
        sprite_render(sprLock, 1175.0f, 320.0f, 1.0f, 1.0f, 0, 0, 105.0f, 105.0f, 52.5f, 52.5f);
        // ����
    case 5:
        sprite_render(sprLock, 290.0f, 495.0f, 1.0f, 1.0f, 0, 0, 105.0f, 105.0f, 52.5f, 52.5f);
    case 6:
        sprite_render(sprLock, 490.0f, 495.0f, 1.0f, 1.0f, 0, 0, 105.0f, 105.0f, 52.5f, 52.5f);
    case 7:
        sprite_render(sprLock, 690.0f, 495.0f, 1.0f, 1.0f, 0, 0, 105.0f, 105.0f, 52.5f, 52.5f);
    case 8:
        sprite_render(sprLock, 890.0f, 495.0f, 1.0f, 1.0f, 0, 0, 105.0f, 105.0f, 52.5f, 52.5f);
    case 9:
        sprite_render(sprLock, 1090.0f, 495.0f, 1.0f, 1.0f, 0, 0, 105.0f, 105.0f, 52.5f, 52.5f);
    case 10:
        sprite_render(sprLock, 1290.0f, 495.0f, 1.0f, 1.0f, 0, 0, 105.0f, 105.0f, 52.5f, 52.5f);
        // �O���
    case 11:
        sprite_render(sprLock, 400.0f, 670.0f, 1.0f, 1.0f, 0, 0, 105.0f, 105.0f, 52.5f, 52.5f);
    case 12:
        sprite_render(sprLock, 600.0f, 670.0f, 1.0f, 1.0f, 0, 0, 105.0f, 105.0f, 52.5f, 52.5f);
    case 13:
        sprite_render(sprLock, 800.0f, 670.0f, 1.0f, 1.0f, 0, 0, 105.0f, 105.0f, 52.5f, 52.5f);
    case 14:
        sprite_render(sprLock, 1000.0f, 670.0f, 1.0f, 1.0f, 0, 0, 105.0f, 105.0f, 52.5f, 52.5f);
    case 15:
        sprite_render(sprLock, 1200.0f, 670.0f, 1.0f, 1.0f, 0, 0, 105.0f, 105.0f, 52.5f, 52.5f);
    case 16:
        sprite_render(sprLock, 1400.0f, 670.0f, 1.0f, 1.0f, 0, 0, 105.0f, 105.0f, 52.5f, 52.5f);
    }
}

/// <summary>
/// �}�E�X�N���b�N����
/// </summary>
/// <param name="s">�X�e�[�W�ԍ�</param>
void mouseClick(int s)
{
    if (TRG(0) & PAD_R3)
    {
        stage = s;

        // �V�[���؂�ւ�
        nextScene = SCENE::GAME;
    }
}