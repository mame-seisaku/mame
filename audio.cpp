#include "all.h"

/// <summary>
/// �I�[�f�B�I�̏����ݒ�
/// </summary>
void audio_init()
{
    music::load(game_bgm, L"./Data/Musics/game_bgm.wav", 0.5f);

}

/// <summary>
/// �I�[�f�B�I�̏I������
/// </summary>
void audio_deinit()
{
    music::clear();
}