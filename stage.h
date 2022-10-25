#ifndef STAGE_H
#define STAGE_H

#define STAGE_MAX   (10)

extern int stage_state[STAGE_MAX];

// プロトタイプ宣言
void stage_init();
void stage_deinit();
void stage_update(int s);
void stage_render(int s);

#endif//STAGE_H