#ifndef OBJ2D_H
#define OBJ2D_H

#define GRAVITY (1.0f)

class obj2d
{
public:
    VECTOR2 pos;        // 位置
    VECTOR2 scale;      // 大きさ
    VECTOR2 texPos;     // 元画像位置
    VECTOR2 texSize;    // 元画像大きさ
    VECTOR2 pivot;      // 基準点
    float angle;        // 角度
    VECTOR4 color;      // 色

    VECTOR2 speed;      // 速度
    VECTOR2 hsize;      // 端

    VECTOR2 moveVec;

    bool exist;         // 存在するか
    bool elec;          // 電気
    bool moveFlag;

    bool one;           // 
    bool end;           // 
    bool open;          // 扉の判定
    int anime;
    int animeTimer;
    int state;
};


#endif//OBJ2D_H