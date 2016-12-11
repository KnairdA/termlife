#include "box_traverser.h"

namespace life {
namespace util {

void BoxTraverser::for_each(
	const std::function<void(std::size_t, std::size_t)>& f) const {
	for ( std::size_t x = this->a_x_; x < this->b_x_; x++ ) {
		for ( std::size_t y = this->a_y_; y < this->b_y_; y++ ) {
			f(x, y);
		}
	}
}

}
}
