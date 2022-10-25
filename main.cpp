#include "all.h"

int curScene = SCENE::NONE;
int nextScene = SCENE::TITLE;

// �t�@�C���ǂݍ��ݗp
struct Data
{
    int stage_max;
};

int APIENTRY wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int)
{
    //�Q�[�����C�u�����̏����ݒ�
    GameLib::init(L"�`�[������Q", WIDTH, HEIGHT, true);

    // �����h�֐�
    srand((unsigned int)time(NULL));

    // �t�@�C���f�[�^�ۑ���ϐ�
    struct Data data = {};

    // �t�@�C���ǂݍ���
    std::ifstream ifs;
    ifs.open("mame.bin", std::ios::binary);
    if (ifs)
    {
        ifs.read((char*)&data.stage_max, sizeof(data));
        ifs.close();
    }
    PossibleStage = data.stage_max;

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

            case SCENE::SELECT:
                select_deinit();
                break;

            case SCENE::RESULT:
                result_deinit();
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

            case SCENE::SELECT:
                select_init();
                break;

            case SCENE::RESULT:
                result_init();
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

        case SCENE::SELECT:
            select_update();
            select_render();
            break;

        case SCENE::RESULT:
            result_update();
            result_render();
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

    case SCENE::SELECT:
        select_deinit();
        break;

    case SCENE::RESULT:
        result_deinit();
        break;
    }

    //  �t�@�C�������o��
    data.stage_max = PossibleStage;
    std::ofstream ofs;
    ofs.open("mame.bin", std::ios::binary);
    if (ofs)
    {
        ofs.write((const char*)&data.stage_max, sizeof(data.stage_max));
    }

    // �I�[�f�B�I�̏I������
    audio_deinit();

    // �Q�[�����C�u�����̏I������
    GameLib::uninit();

    return 0;
}
