#include "all.h"

<<<<<<< HEAD
int tutorial_state;

=======
/*****�ϐ�*****/
int tutorial_state;

Sprite* sprTutorial;

/// <summary>
/// �����ݒ�
/// </summary>
>>>>>>> 2ccefa9e3716e6aa28dc92d8de0ebaeab916b8d8
void tutorial_init()
{
    tutorial_state = 0;
}

<<<<<<< HEAD
void tutorial_deinit()
{

}

=======
/// <summary>
/// �I������
/// </summary>
void tutorial_deinit()
{
    safe_delete(sprTutorial);
}

/// <summary>
/// �X�V����
/// </summary>
>>>>>>> 2ccefa9e3716e6aa28dc92d8de0ebaeab916b8d8
void tutorial_update()
{
    switch (tutorial_state)
    {
    case 0:
<<<<<<< HEAD
        ++tutorial_state;
    case 1:
        ++tutorial_state;
    case 2:
=======
        ///// ������ /////
        sprTutorial = sprite_load(L"./Data/Images/tutorial.png");

        ++tutorial_state;
    case 1:
        ///// �p�����[�^�̐ݒ�
        ++tutorial_state;
    case 2:
        ///// �ʏ펞 /////

        // ��ʐ؂�ւ�
        if (TRG(0) & PAD_SELECT)
        {
            nextScene = SCENE::TITLE;
            break;
        }

>>>>>>> 2ccefa9e3716e6aa28dc92d8de0ebaeab916b8d8
        break;
    }
}

<<<<<<< HEAD
void tutorial_render()
{

=======
/// <summary>
/// �`�揈��
/// </summary>
void tutorial_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(sprTutorial, 0, 0);
>>>>>>> 2ccefa9e3716e6aa28dc92d8de0ebaeab916b8d8
}
