#ifndef STAGE_H
#define STAGE_H

#define STAGE_MAX   (10)
#define STAGE_MOVE  (10)

extern int stage_state[STAGE_MAX];
extern int UI;

extern VECTOR2 mousePos;
extern VECTOR2 ElecPos;
extern VECTOR2 EvPlayer;
extern obj2d Elec;
extern VECTOR2 MouseTexPos;

extern bool pause;
extern Sprite* sprEvPlayer;
extern Sprite* sprEV;
extern Sprite* sprPause;
extern Sprite* sprTerrain;

extern Sprite* sprWhite;
extern Sprite* sprUI;
extern Sprite* sprElec; // 電気
extern Sprite* sprDoor; // ドア

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
    int counter;    // 回数

    //bool exist;         // 存在するか
    bool move;      // 動けるか
 
};

extern stage door;

// プロトタイプ宣言
bool hitCheck(obj2d* rc1, obj2d* rc2);
float check(obj2d* rc1, obj2d* rc2, int dir);

void SetElecMove();

#endif//STAGE_H