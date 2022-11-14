#include "all.h"

/// <summary>
/// �I�[�f�B�I�̏����ݒ�
/// </summary>
void audio_init()
{

    music::load(game_bgm, L"./Data/Musics/game_bgm.wav", 0.5f);

    music::load(0, L"./Data/Musics/belt_conveyor.wav"); // �x���g�R���x�A



    sound::load(0, L"./Data/Sounds/door.xwb");          // �h�A
    sound::load(1, L"./Data/Sounds/clear.xwb");         // �N���A
}

/// <summary>
/// �I�[�f�B�I�̏I������
/// </summary>
void audio_deinit()
{
    music::clear();
}