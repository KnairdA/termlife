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
	life::util::BoxTraverser viewport(x, y, WIDTH, HEIGHT);

	tb_clear();

	viewport.for_each([&](std::size_t i, std::size_t j) {
		const std::uint8_t density{world.lifeDensityAt(i-x, j-y)};

		if ( world.isLifeAt(i-x, j-y) ) {
			tb_change_cell(i, j, 48+density, TB_BLACK, TB_GREEN);
		} else {
			if ( density == 0 ) {
				tb_change_cell(i, j, ' ', TB_BLACK, TB_BLUE);
			} else {
				tb_change_cell(i, j, 48+density, TB_BLACK, TB_BLUE);
			}
		}
	});

	util::print_tb(1, 1, TB_WHITE, TB_DEFAULT, "Age:");
	util::print_tb(13, 1, TB_WHITE, TB_DEFAULT, std::to_string(world.getAge()));

	util::print_tb(1, 2, TB_WHITE, TB_DEFAULT, "Population:");
	util::print_tb(13, 2, TB_WHITE, TB_DEFAULT, std::to_string(world.getPopulation()));

	tb_present();
}

int main(int, char*[]) {
	util::TermGuard    guard;
	life::World<60,40> world;

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
