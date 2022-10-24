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

        // ��ʐ؂�ւ�
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
void result_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(sprResult, 0, 0);
}
