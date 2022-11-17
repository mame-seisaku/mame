#include "all.h"

/*****�ϐ�*****/
int result_state;

Sprite* sprResult;

/// <summary>
/// �����ݒ�
/// </summary>
void result_init()
{
    result_state = 0;
}

/// <summary>
/// �I������
/// </summary>
void result_deinit()
{
    safe_delete(sprResult);
}

/// <summary>
/// �X�V����
/// </summary>
void result_update()
{
    switch (result_state)
    {
    case 0:
        ///// ������ /////
        sprResult = sprite_load(L"./Data/Images/result.png");
        

        ++result_state;
    case 1:
        ///// �p�����[�^�̐ݒ� /////
        ++result_state;
    case 2:
        ///// �ʏ펞 /////

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

        // ��ʐ؂�ւ�

        if (TRG(0) & PAD_L3)
        {
            if (mousePos.x > 385 && mousePos.y > 585 && mousePos.x < 1175 && mousePos.y < 640)
            {
                nextScene = SCENE::TITLE;
                break;
            }
            if (mousePos.x > 385 && mousePos.y > 415 && mousePos.x < 1075 && mousePos.y < 520)
            {
                mouseClick(selectStage + 1);
                break;
            }
        }

        /*if (TRG(0) & PAD_SELECT)
        {
            nextScene = SCENE::TITLE;
            break;
        }

        if (STATE(0) & PAD_START)
        {
            mouseClick(selectStage + 1);
            break;
        }*/

        break;
    }
}

/// <summary>
/// �`�揈��
/// </summary>
void result_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(sprResult, 0, 0);
}
