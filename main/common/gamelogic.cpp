#include <exception>

#include "gamelogic.hpp"
#include "random_generator.hpp"

namespace RPS {

	static Choice selectChoice(RPS::rps_random_generator& generator) {
		int random = generator.get_random_value();
		return Choice(random);
	}

	int decide_winner(Choice first_choice, Choice second_choice) {
		if (first_choice == second_choice) {
			return 0;
		}

		if (first_choice == Choice::ROCK && second_choice == Choice::SCISSORS ||
			first_choice == Choice::SCISSORS && second_choice == Choice::PAPER ||
			first_choice == Choice::PAPER && second_choice == Choice::ROCK) {
			return -1;
		}

		if (second_choice == Choice::ROCK && first_choice == Choice::SCISSORS ||
			second_choice == Choice::SCISSORS && first_choice == Choice::PAPER ||
			second_choice == Choice::PAPER && first_choice == Choice::ROCK) {
			return 1;
		}

		throw new std::exception("Unknown error encountered while evaluating winner");
	}
}
