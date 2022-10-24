#include "all.h"

/*******�ϐ�********/
int title_state;

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

        ++title_state;
    case 1:
        ///// �p�����[�^�[�̐ݒ� /////
        GameLib::setBlendMode(Blender::BS_ALPHA);

        ++title_state;
    case 2:
        ///// �ʏ펞 /////

        // ��ʐ؂�ւ�
        if (TRG(0) & PAD_START)
        {
            nextScene = SCENE::SELECT;
            break;
        }

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
}
