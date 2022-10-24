#ifndef COMMON_H
#define COMMON_H

#include "../GameLib/game_lib.h"
using namespace GameLib;

// 画面サイズ
#define WIDTH   (1920)
#define HEIGHT  (1080)

// シーンラベル
#define SCENE_NONE  -1
#define SCENE_TITLE 0
#define SCENE_GAME  1

// 関数ポインタ
extern float(* const ToRadian)(float);// 角度をラジアンに
extern float(* const ToDegree)(float);// ラジアンを角度に

// 変数
extern int curScene;
extern int nextScene;

#endif//COMMON_H