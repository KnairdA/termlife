#include <termbox.h>

#include "world.h"

void print_tb(
	std::size_t   x,
	std::size_t   y,
	std::uint16_t fg,
	std::uint16_t bg,
	const std::string& text
) {
	for ( const char& c : text ) {
		tb_change_cell(x, y, c, fg, bg);
		x++;
	}
}

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

	print_tb(x+1, y+21, TB_WHITE, TB_DEFAULT, "Age:");
	print_tb(x+6, y+21, TB_WHITE, TB_DEFAULT, std::to_string(world.getAge()));

	tb_present();
}

int main(int, char*[]) {
	tb_init();

	tb_select_output_mode(TB_OUTPUT_NORMAL);
	tb_select_input_mode(TB_INPUT_ESC | TB_INPUT_MOUSE);

	life::World<40,20> world;

	std::size_t worldOffsetX = tb_width()  / 2 - world.width  / 2;
	std::size_t worldOffsetY = tb_height() / 2 - world.height / 2;

	draw(worldOffsetX, worldOffsetY, world);

	while ( true ) {
		struct tb_event ev;
		int t = tb_poll_event(&ev);

		if ( t == -1 ) {
			tb_shutdown();
			return -1;
		}

		switch ( t ) {
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
