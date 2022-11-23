#include "all.h"

/// <summary>
/// オーディオの初期設定
/// </summary>
void audio_init()
{

    music::load(game_bgm, L"./Data/Musics/game_bgm.wav", 0.2f);

    music::load(title_bgm, L"./Data/Musics/title_bgm.wav", 0.2f);

    music::load(result_bgm, L"./Data/Musics/result_bgm.wav", 0.2f);

    music::load(select_bgm, L"./Data/Musics/select_bgm.wav", 0.2f);

    music::load(0, L"./Data/Musics/belt_conveyor.wav"); // ベルトコンベア



    sound::load(0, L"./Data/Sounds/door.xwb");          // ドア
    sound::load(1, L"./Data/Sounds/clear.xwb");         // クリア
}

/// <summary>
/// オーディオの終了処理
/// </summary>
void audio_deinit()
{
    music::clear();
}