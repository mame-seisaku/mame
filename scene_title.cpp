#include "all.h"

/*******�ϐ�********/
int title_state;

VECTOR2 mousePos;   // �}�E�X�J�[�\���̈ʒu

Sprite* sprTitle;


/// <summary>
/// �^�C�g���̏����ݒ�
/// </summary>
void title_init()
{
    title_state = 0;
}

/// <summary>
/// �^�C�g���̏I������
/// </summary>
void title_deinit()
{
    safe_delete(sprTitle);
    safe_delete(sprMouse);
}

/// <summary>
/// �^�C�g���̍X�V����
/// </summary>
void title_update()
{
    switch (title_state)
    {
    case 0:
        ///// �����ݒ� /////
        sprTitle = sprite_load(L"./Data/Images/title.png");
        sprMouse = sprite_load(L"./Data/Images/mouse.png");

        ++title_state;
    case 1:
        ///// �p�����[�^�[�̐ݒ� /////
        GameLib::setBlendMode(Blender::BS_ALPHA);

        mousePos = {};

        ++title_state;
    case 2:
        ///// �ʏ펞 /////


        // ��ʐ؂�ւ�
        if (TRG(0) & PAD_L3)
        {
            // �X�^�[�g
            if (mousePos.x > 615 && mousePos.y > 420 && mousePos.x < 825 && mousePos.y < 495)
            {
                nextScene = SCENE::SELECT;
                break;
            }
            // �`���[�g���A��
            if (mousePos.x > 500 && mousePos.y > 600 && mousePos.x < 970 && mousePos.y < 670)
            {
                nextScene = SCENE::TUTORIAL;
                break;
            }
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
        debug::setString("PossibleStage:%d", PossibleStage);
#endif

        break;
    }
}

/// <summary>
/// �^�C�g���̕`�揈��
/// </summary>
void title_render()
{
    GameLib::clear(0, 0, 0);

    sprite_render(sprTitle, 0, 0);

    sprite_render(sprMouse, mousePos.x, mousePos.y, 1, 1, 0, 0, 100, 100, 50, 50);
}
