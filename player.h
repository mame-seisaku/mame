#ifndef PLAYER_H
#define PLAYER_H
// �C���N���[�h
#include "obj2d.h"

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


#endif//PLAYER_H