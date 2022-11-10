#include "all.h"

/// <summary>
/// オーディオの初期設定
/// </summary>
void audio_init()
{
    music::load(game_bgm, L"./Data/Musics/game_bgm.wav", 0.5f);

}

/// <summary>
/// オーディオの終了処理
/// </summary>
void audio_deinit()
{
    music::clear();
}