#ifndef COMMON_H
#define COMMON_H

#include "../GameLib/game_lib.h"
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
<<<<<<< HEAD
    STAGE_0,
=======
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
>>>>>>> 42f78feaa418dc3dd06df3974bcf2448484ff3f7
};

// 関数ポインタ
extern float(* const ToRadian)(float);// 角度をラジアンに
extern float(* const ToDegree)(float);// ラジアンを角度に

// 変数
extern int curScene;
extern int nextScene;

#endif//COMMON_H