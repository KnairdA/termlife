#ifndef LIFE_SRC_UTIL_BOX_TRAVERSER_
#define LIFE_SRC_UTIL_BOX_TRAVERSER_

#include <cstdint>
#include <functional>

#include "box_indicator.h"

namespace life {
namespace util {

struct BoxTraverser : public BoxIndicator {
	using BoxIndicator::BoxIndicator;

	void for_each(const std::function<void(std::size_t, std::size_t)>& f) const;
};

}
}

#endif  // LIFE_SRC_UTIL_BOX_TRAVERSER_
