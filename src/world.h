#ifndef LIFE_SRC_WORLD_H_
#define LIFE_SRC_WORLD_H_

#include <array>
#include <stack>
#include <tuple>
#include <cstdint>

#include "util/box_traverser.h"

namespace life {

template<
	std::size_t WIDTH,
	std::size_t HEIGHT
>
class World {
	public:
		static const std::size_t width  = WIDTH;
		static const std::size_t height = HEIGHT;

		World():
			area_(width, height) {
			this->area_.for_each([&](std::size_t i, std::size_t j) {
				this->matrix_[j][i] = false;
			});
		}

		bool isLifeAt(std::ptrdiff_t x, std::ptrdiff_t y) const {
			if ( this->area_(x, y) ) {
				return this->matrix_[y][x];
			} else {
				return false; // end of world is dead
			}
		}

		std::uint8_t lifeDensityAt(std::size_t x, std::size_t y) const {
			std::uint8_t counter{};

			counter += this->isLifeAt(x - 1, y);
			counter += this->isLifeAt(x + 1, y);
			counter += this->isLifeAt(x,     y - 1);
			counter += this->isLifeAt(x,     y + 1);
			counter += this->isLifeAt(x - 1, y + 1);
			counter += this->isLifeAt(x - 1, y - 1);
			counter += this->isLifeAt(x + 1, y + 1);
			counter += this->isLifeAt(x + 1, y - 1);

			return counter;
		}

		std::size_t getAge() const {
			return this->age_;
		}

		void summonLifeAt(std::size_t x, std::size_t y) {
			if ( this->area_(x, y) ) {
				this->matrix_[y][x] = true;
			}
		}

		void extinguishLifeAt(std::size_t x, std::size_t y) {
			if ( this->area_(x, y) ) {
				this->matrix_[y][x] = false;
			}
		}

		void tick() {
			this->age_++;

			std::stack<std::tuple<std::size_t, std::size_t, bool>> updates;

			this->area_.for_each([&](std::size_t i, std::size_t j) {
				const std::uint8_t d{this->lifeDensityAt(i, j)};

				if ( this->matrix_[j][i] ) {
					if ( d < 2 ) {
						updates.emplace(i, j, false);
					} else if ( d == 2 || d == 3 ) {
						updates.emplace(i, j, true);
					} else if ( d > 3 ) {
						updates.emplace(i, j, false);
					}
				} else {
					if ( d == 3 ) {
						updates.emplace(i, j, true);
					}
				}
			});

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

	private:
		const util::BoxTraverser area_;

		std::size_t age_{};
		std::array<std::array<bool, WIDTH>, HEIGHT> matrix_;

};

}

#endif  // LIFE_SRC_WORLD_H_
