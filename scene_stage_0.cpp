#include "all.h"

int stage_0_state;
int stage_0_timer;

extern Sprite* sprGame;
extern Player player;

void stage_0_init()
{
	stage_0_state = 0;
	stage_0_timer = 0;
}


void stage_0_deinit()
{
	player.Dinit();
}


void stage_0_update()
{
	switch (stage_0_state)
	{
	case 0:


		stage_0_state++;

	case 1:



		stage_0_state++;

	case 2:


		break;
	}
}


void stage_0_render()
{

}