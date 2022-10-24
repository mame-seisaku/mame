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
};


#endif//OBJ2D_H