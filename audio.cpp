#include "all.h"

/// <summary>
/// オーディオの初期設定
/// </summary>
void audio_init()
{

    music::load(game_bgm, L"./Data/Musics/game_bgm.wav", 0.1f);

    music::load(title_bgm, L"./Data/Musics/title_bgm.wav", 0.1f);

    music::load(result_bgm, L"./Data/Musics/result_bgm.wav", 0.1f);

    music::load(select_bgm, L"./Data/Musics/select_bgm.wav", 0.1f);

    music::load(BELT_, L"./Data/Musics/belt_conveyor.wav", 0.2f); // ベルトコンベア

    music::load(TROLLEY, L"./Data/Musics/trolley.wav");

    music::load(6, L"./Data/Musics/zukan.wav", 0.2f);

    sound::load(0, L"./Data/Sounds/door.xwb");          // ドア
    sound::load(1, L"./Data/Sounds/clear.xwb");         // クリア
    sound::load(2, L"./Data/Sounds/broken.xwb");
}

/// <summary>
/// オーディオの終了処理
/// </summary>
void audio_deinit()
{
    music::clear();
}