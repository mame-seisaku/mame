#include "all.h"

/*****ïœêî*****/
int tutorial_state;

Sprite* sprTutorial;

void tutorial_init()
{
    tutorial_state = 0;
}

void tutorial_deinit()
{
    safe_delete(sprTutorial);
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
