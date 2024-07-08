#pragma once

#include <random>

namespace RPS {
	class rps_random_generator {
	public:
		rps_random_generator();

		int get_random_value();

	private:
		std::random_device r;
		std::default_random_engine e;
		std::uniform_int_distribution<int> uniform_dist;
	};
}
