#include "all.h"

/*****�ϐ�*****/

Sprite* sprStage2;

void stage2_init()
{
    stage_state[2] = 0;
}

void stage2_deinit()
{
    player.Dinit();

    safe_delete(sprStage2);

    music::stop(game_bgm);
}

void stage2_update()
{
    switch (stage_state[2])
    {
    case 0:
        ///// �����ݒ� /////
        sprStage2 = sprite_load(L"./Data/Images/04.png");

        ++stage_state[2];
    case 1:
        ///// �p�����[�^�̐ݒ� /////
        ++stage_state[2];
    case 2:
        ///// �ʏ펞 /////
        break;
    }
}

void stage2_render()
{
    GameLib::clear(1, 1, 1);

    // �w�i
    sprite_render(sprStage2, 0, 0);


}
