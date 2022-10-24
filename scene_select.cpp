#include "all.h"

/*****�ϐ�*****/
int select_state;

Sprite* sprSelect;

void select_init()
{
    select_state = 0;
}

void select_deinit()
{
    safe_delete(sprSelect);
}

void select_update()
{
    switch (select_state)
    {
    case 0:
        ///// �����ݒ� /////
        sprSelect = sprite_load(L"./Data/Images/select.png");

        ++select_state;
    case 1:
        ///// �p�����[�^�̐ݒ�
        ++select_state;
    case 2:
        ///// �ʏ펞 /////
        
        // ��ʐ؂�ւ�
        if (TRG(0) & PAD_SELECT)
        {
            nextScene = SCENE::TITLE;
            break;
        }
        if (TRG(0) & PAD_START)
        {
            nextScene = SCENE::GAME;
            break;
        }

        break;
    }
}

void select_render()
{
    GameLib::clear(1, 1, 1);

    sprite_render(sprSelect, 0, 0);
}
