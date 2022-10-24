#ifndef COMMON_H
#define COMMON_H

#include "../GameLib/game_lib.h"
using namespace GameLib;

// 画面サイズ
#define WIDTH   (1920)
#define HEIGHT  (1080)

// シーンラベル
enum SCENE
{
    NONE = -1,
    OPEN = 0,
    TITLE,
    SELECT,
    GAME,
    RESULT,
    TUTORIAL,
};

// 関数ポインタ
extern float(* const ToRadian)(float);// 角度をラジアンに
extern float(* const ToDegree)(float);// ラジアンを角度に

// 変数
extern int curScene;
extern int nextScene;

#endif//COMMON_H