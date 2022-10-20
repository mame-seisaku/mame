#include "all.h"

int curScene    = SCENE_NONE;
int nextScene   = SCENE_TITLE;

int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
    //�Q�[�����C�u�����̏����ݒ�
    GameLib::init(L"�`�[������Q", 1920, 1080, false);

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
            case SCENE_TITLE:
                title_deinit();
                break;

            case SCENE_GAME:
                game_deinit();
                break;
            }

            // ���̃V�[���ɒǂ��������ݒ菈��
            switch (nextScene)
            {
            case SCENE_TITLE:
                title_init();
                break;
                
            case SCENE_GAME:
                game_init();
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
        case SCENE_TITLE:
            title_update();
            title_render();
            break;

        case SCENE_GAME:
            game_update();
            game_render();
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
    case SCENE_TITLE:
        title_deinit();
        break;
        
    case SCENE_GAME:
        game_deinit();
        break;
    }

    // �I�[�f�B�I�̏I������
    audio_deinit();

    // �Q�[�����C�u�����̏I������
    GameLib::uninit();

    return 0;
}
