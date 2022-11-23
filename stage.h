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
extern Sprite* sprElec; // �d�C
extern Sprite* sprDoor; // �h�A

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
    VECTOR2 position;   // �摜�`��p
    int counter;    // ��

    //bool exist;         // ���݂��邩
    bool move;      // �����邩
 
};

extern stage door;

// �v���g�^�C�v�錾
bool hitCheck(obj2d* rc1, obj2d* rc2);
float check(obj2d* rc1, obj2d* rc2, int dir);

void SetElecMove();

#endif//STAGE_H