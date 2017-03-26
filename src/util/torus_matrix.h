#ifndef LIFE_SRC_UTIL_TORUS_MATRIX_
#define LIFE_SRC_UTIL_TORUS_MATRIX_

#include <array>
#include <cstdint>

namespace life {
namespace util {

template<
	typename    TYPE,
	std::size_t WIDTH,
	std::size_t HEIGHT
>
class TorusMatrix {
	static std::size_t toMatrixColumn(const std::ptrdiff_t x) {
		if ( x >= 0 ) {
			return x % WIDTH;
		} else {
			return WIDTH - ( std::abs(x) % WIDTH );
		}
	}

	static std::size_t toMatrixRow(const std::ptrdiff_t y) {
		if ( y >= 0 ) {
			return y % HEIGHT;
		} else {
			return HEIGHT - ( std::abs(y) % HEIGHT );
		}
	}

	public:
		static const std::size_t width  = WIDTH;
		static const std::size_t height = HEIGHT;

		TYPE get(const std::ptrdiff_t x, const std::ptrdiff_t y) const {
			return this->matrix_[toMatrixRow(y)][toMatrixColumn(x)];
		}

		void set(const std::ptrdiff_t x, const std::ptrdiff_t y, TYPE&& value) {
			this->matrix_[toMatrixRow(y)][toMatrixColumn(x)] = value;
		}
	
	private:
		std::array<std::array<TYPE, WIDTH>, HEIGHT> matrix_;

};

}
}

#endif  // LIFE_SRC_UTIL_TORUS_MATRIX_
