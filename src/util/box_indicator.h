#ifndef LIFE_SRC_UTIL_BOX_INDICATOR_
#define LIFE_SRC_UTIL_BOX_INDICATOR_

#include <cstdint>

namespace life {
namespace util {

class BoxIndicator {
	public:
		BoxIndicator(
			const std::size_t offset_x,
			const std::size_t offset_y,
			const std::size_t size_x,
			const std::size_t size_y);

		BoxIndicator(const std::size_t size_x, const std::size_t size_y);

		bool operator()(const std::size_t x, const std::size_t y) const;

	protected:
		const std::size_t a_x_;
		const std::size_t a_y_;
		const std::size_t b_x_;
		const std::size_t b_y_;

};

}
}

#endif  // LIFE_SRC_UTIL_BOX_INDICATOR_
