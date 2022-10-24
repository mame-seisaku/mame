#ifndef PLAYER_H
#define PLAYER_H
// インクルード
#include "obj2d.h"

class Player :public obj2d
{
public:
    int state;
    int timer;

    Sprite* sprPlayer;

public:
    void Init();        // 初期設定
    void Dinit();       // 終了処理
    void Update();      // 更新処理
    void Render();      // 描画処理

    void Move();        // 移動
    void checkGround(); // 地面との判定
};


#endif//PLAYER_H