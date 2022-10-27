#include "all.h"

int curScene = SCENE::NONE;
int nextScene = SCENE::TITLE;

int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
    //ゲームライブラリの初期設定
    GameLib::init(L"チーム制作２", WIDTH, HEIGHT, true);

    // ランド関数
    srand((unsigned int)time(NULL));

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

            case SCENE::STAGE_0:
                stage_0_deinit();
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

            case SCENE::STAGE_0:
                stage_0_init();
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

        case SCENE::STAGE_0:
            stage_0_update();
            stage_0_render();
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

    case SCENE::STAGE_0:
        stage_0_deinit();
        break;
    }

    // オーディオの終了処理
    audio_deinit();

    // ゲームライブラリの終了処理
    GameLib::uninit();

    return 0;
}
