#ifndef COMMON_H
#define COMMON_H

#include "../GameLib/game_lib.h"
using namespace GameLib;

// ��ʃT�C�Y
#define WIDTH   (1920)
#define HEIGHT  (1080)

// �V�[�����x��
#define SCENE_NONE  -1
#define SCENE_TITLE 0
#define SCENE_GAME  1

// �֐��|�C���^
extern float(* const ToRadian)(float);// �p�x�����W�A����
extern float(* const ToDegree)(float);// ���W�A�����p�x��

// �ϐ�
extern int curScene;
extern int nextScene;

#endif//COMMON_H