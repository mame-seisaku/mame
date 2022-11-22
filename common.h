#ifndef COMMON_H
#define COMMON_H

#include "../GameLib/game_lib.h"
#include "obj2d.h"
using namespace GameLib;

// 画面サイズ
#define WIDTH   (1536)
#define HEIGHT  (824)

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
    STAGE0 = 6,
    STAGE1,
    STAGE2,
    STAGE3,
    STAGE4,
    STAGE5,
    STAGE6,
    STAGE7,
    STAGE8,
    STAGE9,
    STAGE10,
    RESTART,
};

// 関数ポインタ
extern float(* const ToRadian)(float);// 角度をラジアンに
extern float(* const ToDegree)(float);// ラジアンを角度に

// 変数
extern int curScene;
extern int nextScene;

void anime(obj2d* obj, int total, int flame, bool loop, int type);


#endif//COMMON_H