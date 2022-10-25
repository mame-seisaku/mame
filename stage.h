#ifndef STAGE_H
#define STAGE_H

#define STAGE_MAX   (10)

extern int stage_state[STAGE_MAX];

enum DIR
{
    DOWN,
    UP,
    LEFT,
    RIGHT,
};

class stage :public obj2d
{
public:
    int type;
    bool exist;
};

// プロトタイプ宣言
void stage_init();
void stage_deinit();
void stage_update(int s);
void stage_render(int s);

bool hitCheck(obj2d* rc1, obj2d* rc2);
float check(obj2d* rc1, obj2d* rc2, int dir);


#endif//STAGE_H