#include "all.h"

int zukan_state;

Sprite* sprZukan;   // �}��

extern Sprite* sprBelt; // �x���g����
extern Sprite* sprGear; // �M�A

void zukan_init()
{
    zukan_state = 0;
}

void zukan_deinit()
{
    safe_delete(sprZukan);

    safe_delete(sprBelt);
    safe_delete(sprGear);
}

void zukan_update()
{
    switch (zukan_state)
    {
    case 0:
        ///// �����ݒ� //////
        sprZukan = sprite_load(L"./Data/Images/zukan.png");

        sprBelt = sprite_load(L"./Data/Images/Belt.png");
        sprGear = sprite_load(L"./Data/Images/gear.png");


        ++zukan_state;
    case 1:
        ///// �p�����[�^�[�̐ݒ� /////
        ++zukan_state;
    case 2:
        ///// �ʏ펞 /////

        if (TRG(0) & PAD_START)
        {
            nextScene = SCENE::TITLE;
            break;
        }

        break;
    }
}

void zukan_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(sprZukan, 0, 0);
}
