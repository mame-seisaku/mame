#include "all.h"

int curScene = SCENE::NONE;
int nextScene = SCENE::TITLE;
//int nextScene = SCENE::RESULT;

// �t�@�C���ǂݍ��ݗp
struct Data
{
    int stage_max;
    int tutorial;
};

int APIENTRY wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int)
{
    //�Q�[�����C�u�����̏����ݒ�
    GameLib::init(L"Mystery of Electricity", WIDTH, HEIGHT, false);

    // �����h�֐�
    srand((unsigned int)time(NULL));

    //ShowCursor(false);

    // �t�@�C���f�[�^�ۑ���ϐ�
    struct Data data = {};

    // �t�@�C���ǂݍ���
    std::ifstream ifs;
    ifs.open("mame.bin", std::ios::binary);
    if (ifs)
    {
        ifs.read((char*)&data.stage_max, sizeof(data));
        ifs.read((char*)&data.tutorial, sizeof(data));
        ifs.close();
    }
    PossibleStage = data.stage_max;
    JudgeTutorial = data.tutorial;

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

            case SCENE::STAGE0:
                stage0_deinit();
                break;

            case SCENE::STAGE1:
                stage1_deinit();
                break;

            case SCENE::STAGE2:
                stage2_deinit();
                break;

            case SCENE::STAGE3:
                stage3_deinit();
                break;

            case SCENE::STAGE4:
                stage4_deinit();
                break;

            case SCENE::STAGE5:
                stage5_deinit();
                break;

            case SCENE::STAGE6:
                stage6_deinit();
                break;

            case SCENE::RESTART:
                restart_deinit();
                break;

            case SCENE::ZUKAN:
                zukan_deinit();
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

            case SCENE::STAGE0:
                stage0_init();
                break;

            case SCENE::STAGE1:
                stage1_init();
                break;

            case SCENE::STAGE2:
                stage2_init();
                break;

            case SCENE::STAGE3:
                stage3_init();
                break;

            case SCENE::STAGE4:
                stage4_init();
                break;

            case SCENE::STAGE5:
                stage5_init();
                break;

            case SCENE::STAGE6:
                stage6_init();
                break;

            case SCENE::RESTART:
                restart_init();
                break;

            case SCENE::ZUKAN:
                zukan_init();
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

        case SCENE::STAGE0:
            stage0_update();
            stage0_render();
            break;

        case SCENE::STAGE1:
            stage1_update();
            stage1_render();
            break;

        case SCENE::STAGE2:
            stage2_update();
            stage2_render();
            break;

        case SCENE::STAGE3:
            stage3_update();
            stage3_render();
            break;

        case SCENE::STAGE4:
            stage4_update();
            stage4_render();
            break;

        case SCENE::STAGE5:
            stage5_update();
            stage5_render();
            break;

        case SCENE::STAGE6:
            stage6_update();
            stage6_render();
            break;

        case SCENE::RESTART:
            restart_update();
            restart_render();
            break;

        case SCENE::ZUKAN:
            zukan_update();
            zukan_render();
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

    case SCENE::STAGE0:
        stage0_deinit();
        break;

    case SCENE::STAGE1:
        stage1_deinit();
        break;

    case SCENE::STAGE2:
        stage2_deinit();
        break;

    case SCENE::STAGE3:
        stage3_deinit();
        break;

    case SCENE::STAGE4:
        stage4_deinit();
        break;

    case SCENE::STAGE5:
        stage5_deinit();
        break;

    case SCENE::STAGE6:
        stage6_deinit();
        break;

    case SCENE::RESTART:
        restart_deinit();
        break;

    case SCENE::ZUKAN:
        zukan_deinit();
        break;
    }

    //  �t�@�C�������o��
    data.stage_max = PossibleStage;
    data.tutorial = JudgeTutorial;
    std::ofstream ofs;
    ofs.open("mame.bin", std::ios::binary);
    if (ofs)
    {
        ofs.write((const char*)&data.stage_max, sizeof(data.stage_max));
        ofs.write((const char*)&data.tutorial, sizeof(data.tutorial));
    }

    // �I�[�f�B�I�̏I������
    audio_deinit();

    // �Q�[�����C�u�����̏I������
    GameLib::uninit();

    return 0;
}
