#ifndef STAGE_H
#define STAGE_H

#define STAGE_MAX   (10)

extern int stage_state[STAGE_MAX];
extern VECTOR2 mousePos;
extern VECTOR2 ElecPos;
extern VECTOR2 EvPlayer;
extern obj2d Elec;

extern bool pause;
extern Sprite* sprEvPlayer;
extern Sprite* sprEV;
extern Sprite* sprPause;
extern Sprite* sprTerrain;

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
    VECTOR2 position;   // 画像描画用
    
    //bool exist;         // 存在するか
    bool move;      // 動けるか
 
};

// プロトタイプ宣言

bool hitCheck(obj2d* rc1, obj2d* rc2);
float check(obj2d* rc1, obj2d* rc2, int dir);

void SetElecMove();

#endif//STAGE_H