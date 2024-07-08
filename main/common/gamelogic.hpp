#pragma once

namespace RPS {

	class rps_random_generator;

	enum class Choice {
		ROCK = 0,
		PAPER = 1,
		SCISSORS = 2,
	};

	Choice selectChoice(rps_random_generator& generator);

	int decide_winner(Choice first_choice, Choice second_choice);
}
