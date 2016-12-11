#include <termbox.h>

#include "world.h"
#include "util/term.h"

template<
	std::size_t WIDTH,
	std::size_t HEIGHT
>
void draw(
	std::size_t x,
	std::size_t y,
	life::World<WIDTH, HEIGHT>& world
) {
	tb_clear();

	for ( std::size_t i = 0; i < HEIGHT; i++ ) {
		for ( std::size_t j = 0; j < WIDTH; j++ ) {
			const char density{std::to_string(world.lifeDensityAt(j,i))[0]};

			if ( world.isLifeAt(j,i) ) {
				tb_change_cell(x+j, y+i, density, TB_BLACK, TB_GREEN);
			} else {
				tb_change_cell(x+j, y+i, density, TB_BLACK, TB_BLUE);
			}
		}
	}

	util::print_tb(1, 1, TB_WHITE, TB_DEFAULT, "Age:");
	util::print_tb(6, 1, TB_WHITE, TB_DEFAULT, std::to_string(world.getAge()));

	tb_present();
}

int main(int, char*[]) {
	util::TermGuard    guard;
	life::World<40,20> world;

	std::size_t worldOffsetX = tb_width()  / 2 - world.width  / 2;
	std::size_t worldOffsetY = tb_height() / 2 - world.height / 2;

	draw(worldOffsetX, worldOffsetY, world);

	while ( true ) {
		struct tb_event ev{ guard.poll() };

		switch ( ev.type ) {
			case TB_EVENT_KEY:
				switch ( ev.key ) {
					case TB_KEY_ESC:
						return 0;
					case TB_KEY_SPACE:
						world.tick();
						break;
				}
				break;
			case TB_EVENT_MOUSE:
				if ( ev.key == TB_KEY_MOUSE_LEFT ) {
					const std::size_t x = ev.x - worldOffsetX;
					const std::size_t y = ev.y - worldOffsetY;

					if ( world.isLifeAt(x, y) ) {
						world.extinguishLifeAt(x, y);
					} else {
						world.summonLifeAt(x, y);
					}
				}
				break;
			case TB_EVENT_RESIZE:
				worldOffsetX = ev.w / 2 - world.width  / 2;
				worldOffsetY = ev.h / 2 - world.height / 2;
				break;
		}

		draw(worldOffsetX, worldOffsetY, world);
	}

	return 0;
}
