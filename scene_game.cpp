#include "all.h"

/*****�ϐ�*****/
int game_state;

Sprite* sprGame;

Player player;

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
    player.Dinit();

    safe_delete(sprGame);
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
        player.Init();

        sprGame = sprite_load(L"./Data/Images/game.png");

        ++game_state;
    case 1:
        ///// �p�����[�^�[�̐ݒ� /////

        ++game_state;
    case 2:
        ///// �ʏ펞 /////

        // ��ʐ؂�ւ�
        if (TRG(0) & PAD_SELECT)
        {
            nextScene = SCENE_TITLE;
            break;
        }

        // �v���C���[�X�V����
        player.Update();


        break;
    }
}

/// <summary>
/// �Q�[���̕`�揈��
/// </summary>
void game_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(sprGame, 0, 0);   // �w�i

    // �v���C���[�X�V����    
    player.Render();
}
