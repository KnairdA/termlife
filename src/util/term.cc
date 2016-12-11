#include "term.h"

#include <termbox.h>

namespace util {

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

TermGuard::TermGuard() {
	tb_init();
	tb_select_output_mode(TB_OUTPUT_NORMAL);
	tb_select_input_mode(TB_INPUT_ESC | TB_INPUT_MOUSE);
}

TermGuard::~TermGuard() {
	tb_shutdown();
}

}
