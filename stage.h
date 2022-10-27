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
    VECTOR2 position;   // �摜�`��p
    int type;           // �l�p�̃^�C�v
    bool exist;         // ���݂��邩
};

// �v���g�^�C�v�錾

bool hitCheck(obj2d* rc1, obj2d* rc2);
float check(obj2d* rc1, obj2d* rc2, int dir);


#endif//STAGE_H