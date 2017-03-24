#ifndef LIFE_SRC_WORLD_H_
#define LIFE_SRC_WORLD_H_

#include <stack>
#include <tuple>
#include <cstdint>

#include "util/box_traverser.h"
#include "util/torus_array.h"

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
				this->matrix_.set(i, j, false);
			});
		}

		bool isLifeAt(const std::ptrdiff_t x, const std::ptrdiff_t y) const {
			return this->matrix_.get(x, y);
		}

		std::uint8_t lifeDensityAt(
			const std::ptrdiff_t x, const std::ptrdiff_t y) const {
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

		std::size_t getPopulation() const {
			return this->population_;
		}

		void summonLifeAt(const std::ptrdiff_t x, const std::ptrdiff_t y) {
			if ( this->area_(x, y) ) {
				if ( !this->matrix_.get(x, y) ) {
					this->matrix_.set(x, y, true);
					this->population_ += 1;
				}
			}
		}

		void extinguishLifeAt(const std::ptrdiff_t x, const std::ptrdiff_t y) {
			if ( this->area_(x, y) ) {
				if ( this->matrix_.get(x, y) ) {
					this->matrix_.set(x, y, false);
					this->population_ -= 1;
				}
			}
		}

		void tick() {
			this->age_++;

			std::stack<std::tuple<std::size_t, std::size_t, bool>> updates;

			this->area_.for_each([&](std::size_t i, std::size_t j) {
				const std::uint8_t d{this->lifeDensityAt(i, j)};

				if ( this->matrix_.get(i, j) ) {
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
		std::size_t population_{};
		util::TorusArray<bool, WIDTH, HEIGHT> matrix_;

};

}

#endif  // LIFE_SRC_WORLD_H_
