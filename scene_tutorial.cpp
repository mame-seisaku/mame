#include "all.h"

int tutorial_state;

void tutorial_init()
{
    tutorial_state = 0;
}

void tutorial_deinit()
{

}

void tutorial_update()
{
    switch (tutorial_state)
    {
    case 0:
        ++tutorial_state;
    case 1:
        ++tutorial_state;
    case 2:
        break;
    }
}

void tutorial_render()
{

}
