#ifndef OBJ2D_H
#define OBJ2D_H

#define GRAVITY (1.0f)

class obj2d
{
public:
    VECTOR2 pos;        // �ʒu
    VECTOR2 scale;      // �傫��
    VECTOR2 texPos;     // ���摜�ʒu
    VECTOR2 texSize;    // ���摜�傫��
    VECTOR2 pivot;      // ��_
    float angle;        // �p�x
    VECTOR4 color;      // �F

    VECTOR2 speed;      // ���x
    VECTOR2 hsize;      // �[

    VECTOR2 moveVec;

    bool exist;         // ���݂��邩
    bool elec;          // �d�C
    bool moveFlag;

    bool one;           // 
    bool end;           // 
    bool open;          // ���̔���
    int anime;
    int animeTimer;
    int state;
};


#endif//OBJ2D_H