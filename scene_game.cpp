#include "all.h"

/*****�ϐ�*****/
int game_state;

int PossibleStage;


Sprite* sprGame;


Player player;

// extern �錾
extern int selectStage;

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
        PossibleStage = 0;

        ++game_state;
    case 2:
        ///// �ʏ펞 /////

        // ��ʐ؂�ւ�
        if (TRG(0) & PAD_SELECT)
        {
            nextScene = SCENE::RESULT;
            break;
        }




        // �v���C���[�X�V����
        player.Update({100,200});

#ifdef _DEBUG
        debug::setString("stage:%d", selectStage);
#endif

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
