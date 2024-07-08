#include <iostream>
#include <syncstream>

#include "scoreboard.hpp"


namespace RPS {

    void scoreboard::try_to_add_score(highscore score) {
        std::lock_guard lock(scores_mutex);

        //scoer not high enough
        if (scores[9].score > score.score) {
            return;
        }

        //empty container
        if (scores.size() == 0) {
            scores.emplace_back(score);
            return;
        }
        else {
            //algorithm finds first smaller if any, 
            //  then rotates the ones below it to the right,
            //  and inserts it into the former position of the smaller

            int first_smaller = -1;
            int reverse_first_smaller = -1;
            for (int i = 0; i < 10; ++i) {
                if (scores[i].score <= score.score) {
                    first_smaller = i;
                    reverse_first_smaller = 10 - i;
                    break;
                }
            }

            if (reverse_first_smaller != -1) {
                std::rotate(scores.rbegin(), scores.rbegin() + 1, scores.rend() - first_smaller); //right rotation
                scores[first_smaller] = score;
            }
            print();
        }
    }

    void scoreboard::print() {
        std::osyncstream bout(std::cout);
        for (int i = 0; i < 10; ++i) {
            std::string name_to_print = scores[i].name == "" ? "-" : scores[i].name;
            bout << i+1 << ". " << name_to_print << " score: " << scores[i].score << "\n";
        }
    }

    scoreboard::scoreboard() {
        scores.resize(10);
    }
}
