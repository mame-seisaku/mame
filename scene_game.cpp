#include "all.h"

/*****�ϐ�*****/
int game_state;

/// <summary>
/// �Q�[���̏����ݒ�
/// </summary>
void game_init()
{
    game_state = 0;
}

/// <summary>
/// �Q�[���̏I������
/// </summary>
void game_deinit()
{

}

/// <summary>
/// �Q�[���̍X�V����
/// </summary>
void game_update()
{
    switch (game_state)
    {
    case 0:
        ///// �����ݒ� /////
        ++game_state;
    case 1:
        ///// �p�����[�^�[�̐ݒ� /////

        // test

        ++game_state;
    case 2:
        ///// �ʏ펞 /////
        break;
    }
}

/// <summary>
/// �Q�[���̕`�揈��
/// </summary>
void game_render()
{
    GameLib::clear(1, 1, 1);
}
