#ifndef PLAYER_H
#define PLAYER_H
// �C���N���[�h
#include "obj2d.h"

#define PLAYER_MOVE (7)

class Player :public obj2d
{
public:
    int state;
    int timer;
    int AnimeState;

    int jumpTimer;
    bool jump;
    bool clear;   // �N���A

    Sprite* sprPlayer;

public:
    void Init();        // �����ݒ�
    void Dinit();       // �I������
    void Update(VECTOR2 Pos);      // �X�V����
    void Render();      // �`�揈��

    void Move();        // �ړ�
    void checkGround(); // �n�ʂƂ̔���

    void Anime(int total, int flame);
};

extern Player player;


#endif//PLAYER_H