#ifndef SELECT_H
#define SELECT_H

extern int selectStage;

// �v���g�^�C�v�錾
void select_init();
void select_deinit();
void select_update();
void select_render();

void disp_key();
void mouseClick(int s);

#endif//SELECT_H