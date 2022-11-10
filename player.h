#ifndef PLAYER_H
#define PLAYER_H
// �C���N���[�h
#include "obj2d.h"

#define PLAYER_MOVE (10)

class Player :public obj2d
{
public:
    int state;
    int timer;

    Sprite* sprPlayer;

public:
    void Init();        // �����ݒ�
    void Dinit();       // �I������
    void Update();      // �X�V����
    void Render();      // �`�揈��

    void Move();        // �ړ�
    void checkGround(); // �n�ʂƂ̔���
};

extern Player player;

#endif//PLAYER_H