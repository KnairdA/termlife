#ifndef LIFE_SRC_WORLD_H_
#define LIFE_SRC_WORLD_H_

#include <array>
#include <stack>
#include <tuple>
#include <cstdint>

#include <termbox.h>

namespace life {

template<
	std::size_t WIDTH,
	std::size_t HEIGHT
>
class World {
	public:
		World() {
			for ( std::size_t j = 0; j < HEIGHT; j++ ) {
				for ( std::size_t i = 0; i < WIDTH; i++ ) {
					this->matrix_[j][i] = false;
				}
			}
		}

		void summonLifeAt(std::size_t x, std::size_t y) {
			this->matrix_[y][x] = true;
		}

		void extinguishLifeAt(std::size_t x, std::size_t y) {
			this->matrix_[y][x] = false;
		}

		bool isLifeAt(std::ptrdiff_t x, std::ptrdiff_t y) {
			if ( x >= 0      &&
			     x <  WIDTH  &&
			     y >= 0      &&
			     y <  HEIGHT ) {
				return this->matrix_[y][x];
			} else {
				return false; // end of world is dead
			}
		}

		std::uint8_t lifeDensityAt(std::size_t x, std::size_t y) {
			std::uint8_t counter = 0;

			if ( this->isLifeAt(x - 1, y) ) {
				counter++;
			}
			if ( this->isLifeAt(x + 1, y) ) {
				counter++;
			}
			if ( this->isLifeAt(x, y - 1) ) {
				counter++;
			}
			if ( this->isLifeAt(x, y + 1) ) {
				counter++;
			}
			if ( this->isLifeAt(x - 1, y + 1) ) {
				counter++;
			}
			if ( this->isLifeAt(x - 1, y - 1) ) {
				counter++;
			}
			if ( this->isLifeAt(x + 1, y + 1) ) {
				counter++;
			}
			if ( this->isLifeAt(x + 1, y - 1) ) {
				counter++;
			}

			return counter;
		}

		void tick() {
			this->age_++;

			std::stack<std::tuple<std::size_t, std::size_t, bool>> updates;

			for ( std::size_t j = 0; j < HEIGHT; j++ ) {
				for ( std::size_t i = 0; i < WIDTH; i++ ) {
					const std::uint8_t d = this->lifeDensityAt(i, j);

					if ( this->matrix_[j][i] ) {
						if ( d < 2 ) {
							updates.push(std::make_tuple(i, j, false));	
						} else if ( d == 2 || d == 3 ) {
							updates.push(std::make_tuple(i, j, true));	
						} else if ( d > 3 ) {
							updates.push(std::make_tuple(i, j, false));	
						}
					} else {
						if ( d == 3 ) {
							updates.push(std::make_tuple(i, j, true));	
						}
					}
				}
			}

			while ( !updates.empty() ) {
				const auto& update = updates.top();

				if ( std::get<2>(update) ) {
					this->summonLifeAt(
						std::get<0>(update),
						std::get<1>(update)
					);
				} else {
					this->extinguishLifeAt(
						std::get<0>(update),
						std::get<1>(update)
					);
				}
				
				updates.pop();
			}
		}

		void draw() {
			tb_clear();

			for ( std::size_t j = 0; j < HEIGHT; j++ ) {
				for ( std::size_t i = 0; i < WIDTH; i++ ) {
					if ( this->matrix_[j][i] ) {
						tb_change_cell(i, j, 0x2588, TB_BLACK, TB_GREEN);
					} else {
						tb_change_cell(i, j, 0x2591, TB_BLACK, TB_BLUE);
					}
				}
			}

			tb_present();
		}

	private:
		std::size_t age_ = 0;

		std::array<std::array<bool, WIDTH>, HEIGHT> matrix_;

};

}

#endif  // LIFE_SRC_WORLD_H_
