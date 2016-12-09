#include <termbox.h>

#include "world.h"

int main(int, char*[]) {
	tb_init();

	tb_select_input_mode(TB_INPUT_ESC | TB_INPUT_MOUSE);	

	life::World<20,20> world;

	while ( true ) {
		struct tb_event ev;
		int t = tb_poll_event(&ev);

		if ( t == -1 ) {
			tb_shutdown();
			return -1;
		}

		switch (t) {
			case TB_EVENT_KEY:
				switch ( ev.key ) {
					case TB_KEY_ESC:
						tb_shutdown();
						return 0;
					case TB_KEY_SPACE:
						world.tick();
						break;
				}
				break;
			case TB_EVENT_MOUSE:
				if (ev.key == TB_KEY_MOUSE_LEFT) {
					world.summonLifeAt(ev.x, ev.y);
				}

				break;
			case TB_EVENT_RESIZE:
				break;
		}

		world.draw();
	}

	return 0;
}
