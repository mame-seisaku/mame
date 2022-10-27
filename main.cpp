#include "all.h"

int curScene = SCENE::NONE;
int nextScene = SCENE::TITLE;

int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
    //�Q�[�����C�u�����̏����ݒ�
    GameLib::init(L"�`�[������Q", WIDTH, HEIGHT, true);

    // �����h�֐�
    srand((unsigned int)time(NULL));

    // �I�[�f�B�I�̏����ݒ�
    audio_init();

    // �Q�[�����[�v
    while (GameLib::gameLoop())
    {
        // �V�[���̐؂�ւ�����
        if (curScene != nextScene)
        {
            // ���݂̃V�[���ɉ����������ݒ菈��
            switch (curScene)
            {
            case SCENE::TITLE:
                title_deinit();
                break;

            case SCENE::GAME:
                game_deinit();
                break;
                
            case SCENE::TUTORIAL:
                tutorial_deinit();
                break;

            case SCENE::STAGE_0:
                stage_0_deinit();
                break;
            }

            // ���̃V�[���ɒǂ��������ݒ菈��
            switch (nextScene)
            {
            case SCENE::TITLE:
                title_init();
                break;

            case SCENE::GAME:
                game_init();
                break;
                
            case SCENE::TUTORIAL:
                tutorial_init();
                break;

            case SCENE::STAGE_0:
                stage_0_init();
                break;
            }

            // nextScene��curScene�ɂȂ�
            curScene = nextScene;
        }

        // ���͂��X�V����
        input::update();

        // ���y�̍X�V����
        music::update();

        // ���݂̃V�[���ɉ������X�V�E�`�揈��
        switch (curScene)
        {
        case SCENE::TITLE:
            title_update();
            title_render();
            break;

        case SCENE::GAME:
            game_update();
            game_render();
            break;

        case SCENE::TUTORIAL:
            tutorial_update();
            tutorial_render();
            break;

        case SCENE::STAGE_0:
            stage_0_update();
            stage_0_render();
            break;
        }

        // �f�o�b�N�p������̕\��
        debug::display(1, 1, 1, 1);

        // ��ʂ�`��
        GameLib::present(1, 0);
    }

    // ���݂̃V�[���ɉ������I���������s��
    switch (curScene)
    {
    case SCENE::TITLE:
        title_deinit();
        break;

    case SCENE::GAME:
        game_deinit();
        break;

    case SCENE::TUTORIAL:
        tutorial_deinit();
        break;

    case SCENE::STAGE_0:
        stage_0_deinit();
        break;
    }

    // �I�[�f�B�I�̏I������
    audio_deinit();

    // �Q�[�����C�u�����̏I������
    GameLib::uninit();

    return 0;
}
