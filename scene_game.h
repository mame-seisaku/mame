#ifndef SCENE_GAME_H
#define SCENE_GAME_H

// extern�錾
extern int PossibleStage;
extern Sprite* sprMouse;

// �v���g�^�C�v�錾
void game_init();
void game_deinit();
void game_update();
void game_render();

#endif//SCENE_GAME_H