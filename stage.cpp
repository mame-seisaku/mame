#include "all.h"

int stage_state[STAGE_MAX];

void stage_init()
{
    stage0_init();
}

void stage_deinit()
{
    stage0_deinit();
}

void stage_update(int s)
{
    switch (s)
    {
    case 0:
        stage0_update();
        break;
    case 1:
        break;
    }
}

void stage_render(int s)
{
    switch (s)
    {
    case 0:
        stage0_render();
        break;
    case 1:
        break;
    }
}
