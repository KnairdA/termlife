#ifndef LIFE_SRC_BOX_TRAVERSER_
#define LIFE_SRC_BOX_TRAVERSER_

#include <functional>

#include "box_indicator.h"

namespace life {
namespace util {

struct BoxTraverser : public BoxIndicator {
	using BoxIndicator::BoxIndicator;

	void for_each(const std::function<void(std::size_t, std::size_t)> f) const {
		for ( std::size_t x = this->a_x_; x < this->b_x_; x++ ) {
			for ( std::size_t y = this->a_y_; y < this->b_y_; y++ ) {
				f(x, y);
			}
		}
	}
};

}
}

#endif  // LIFE_SRC_BOX_TRAVERSER_
