#include "all.h"

/*****�ϐ�*****/
int game_state;

int PossibleStage;

bool pause;

Sprite* sprGame;
Sprite* sprPause;

Player player;

// extern �錾
extern int stage;


/// <summary>
/// �Q�[���̏����ݒ�
/// </summary>
void game_init()
{
    game_state = 0;
    pause = false;
}

/// <summary>
/// �Q�[���̏I������
/// </summary>
void game_deinit()
{
    player.Dinit();

    safe_delete(sprGame);
    safe_delete(sprPause);
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
        sprPause = sprite_load(L"./Data/Images/pause.png");

        ++game_state;
    case 1:
        ///// �p�����[�^�[�̐ݒ� /////
        PossibleStage = 1;

        ++game_state;
    case 2:
        ///// �ʏ펞 /////

        // ��ʐ؂�ւ�
        if (TRG(0) & PAD_SELECT)
        {
            nextScene = SCENE::RESULT;
            break;
        }
        // �|�[�Y���
        if (TRG(0) & PAD_L1)
        {
            pause = pause ? false : true;
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

    // �|�[�Y���
    if (pause)
    {
        sprite_render(sprPause, 0, 0);
    }
}
