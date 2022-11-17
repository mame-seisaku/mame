#ifndef SCENE_GAME_H
#define SCENE_GAME_H

// extern宣言
extern int PossibleStage;
extern Sprite* sprMouse;

// プロトタイプ宣言
void game_init();
void game_deinit();
void game_update();
void game_render();

#endif//SCENE_GAME_H