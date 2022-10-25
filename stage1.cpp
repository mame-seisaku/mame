#include "all.h"

/*****�ϐ�*****/
Sprite* spr2;

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
    safe_delete(spr2);
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
        spr2 = sprite_load(L"./Data/Images/02.png");

        ++stage_state[1];
    case 1:
        ///// �p�����[�^�̐ݒ� /////
        ++stage_state[1];
    case 2:
        ///// �ʏ펞 /////
        break;
    }
}

/// <summary>
/// �`�揈��
/// </summary>
void stage1_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(spr2, 0, 0);
}
