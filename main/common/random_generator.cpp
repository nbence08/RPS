#include "random_generator.hpp"

namespace RPS {

	rps_random_generator::rps_random_generator(): r(), e(r()), uniform_dist(0, 2) { }

	int rps_random_generator::get_random_value() {
		return uniform_dist(e);
	}

}
