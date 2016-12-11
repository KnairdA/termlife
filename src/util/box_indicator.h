#ifndef LIFE_SRC_UTIL_BOX_INDICATOR_
#define LIFE_SRC_UTIL_BOX_INDICATOR_

namespace life {
namespace util {

class BoxIndicator {
	public:
	   	BoxIndicator(
			const std::size_t offset_x,
			const std::size_t offset_y,
			const std::size_t size_x,
			const std::size_t size_y):
			a_x_{offset_x},
			a_y_{offset_y},
			b_x_{a_x_ + size_x},
			b_y_{a_y_ + size_y} { }

	   	BoxIndicator(const std::size_t size_x, const std::size_t size_y):
			BoxIndicator(0, 0, size_x, size_y) { }

		bool operator()(const std::size_t x, const std::size_t y) const {
			return x >= this->a_x_
			    && x <  this->b_x_
			    && y >= this->a_y_
			    && y <  this->b_y_;
		}

	protected:
		const std::size_t a_x_;
		const std::size_t a_y_;
		const std::size_t b_x_;
		const std::size_t b_y_;

};

}
}

#endif  // LIFE_SRC_UTIL_BOX_INDICATOR_
