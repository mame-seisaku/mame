#include "all.h"

int curScene = SCENE::NONE;
int nextScene = SCENE::TITLE;

// ファイル読み込み用
struct Data
{
    int stage_max;
};

int APIENTRY wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int)
{
    //ゲームライブラリの初期設定
    GameLib::init(L"チーム制作２", WIDTH, HEIGHT, true);

    // ランド関数
    srand((unsigned int)time(NULL));

    // ファイルデータ保存先変数
    struct Data data = {};

    // ファイル読み込み
    std::ifstream ifs;
    ifs.open("mame.bin", std::ios::binary);
    if (ifs)
    {
        ifs.read((char*)&data.stage_max, sizeof(data));
        ifs.close();
    }
    PossibleStage = data.stage_max;

    // オーディオの初期設定
    audio_init();

    // ゲームループ
    while (GameLib::gameLoop())
    {
        // シーンの切り替え処理
        if (curScene != nextScene)
        {
            // 現在のシーンに応じた初期設定処理
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

            // 次のシーンに追う下初期設定処理
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

            // nextSceneがcurSceneになる
            curScene = nextScene;
        }

        // 入力を更新する
        input::update();

        // 音楽の更新処理
        music::update();

        // 現在のシーンに応じた更新・描画処理
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

        // デバック用文字列の表示
        debug::display(1, 1, 1, 1);

        // 画面を描画
        GameLib::present(1, 0);
    }

    // 現在のシーンに応じた終了処理を行う
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

    //  ファイル書き出し
    data.stage_max = PossibleStage;
    std::ofstream ofs;
    ofs.open("mame.bin", std::ios::binary);
    if (ofs)
    {
        ofs.write((const char*)&data.stage_max, sizeof(data.stage_max));
    }

    // オーディオの終了処理
    audio_deinit();

    // ゲームライブラリの終了処理
    GameLib::uninit();

    return 0;
}
