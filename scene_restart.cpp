#include "all.h"

int restart_state;
int restart_timer;

void restart_init()
{
    restart_state = 0;
    restart_timer = 0;
}

void restart_deinit()
{

}

void restart_update()
{
    switch (restart_state)
    {
    case 0:
        ///// �����ݒ� /////
        ++restart_state;
    case 1:
        ///// �p�����[�^�̐ݒ� /////
        ++restart_state;
    case 2:
        ///// �ʏ펞 /////
    
    if(restart_timer>30)
    {
        NotmouseClick(selectStage);
        break;
    }

        break;
    }
    ++restart_timer;
}

void restart_render()
{
    GameLib::clear(1, 1, 1);
}
