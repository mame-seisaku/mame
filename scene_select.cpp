#include "all.h"

int select_state;

void select_init()
{
    select_state = 0;
}

void select_deinit()
{

}

void select_update()
{
    switch (select_state)
    {
    case 0:
        ++select_state;
    case 1:
        ++select_state;
    case 2:
        break;
    }
}

void select_render()
{
    GameLib::clear(1, 1, 1);


}
