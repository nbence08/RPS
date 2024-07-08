#pragma once

#include <thread>
#include <mutex>
#include <vector>
#include <string>

namespace RPS {

    struct highscore {
        int score;
        std::string name;
    };
    
    class scoreboard {
        public:
            void try_to_add_score(highscore score);

            scoreboard();
        private:
            void print();
            std::mutex scores_mutex;
            std::vector<highscore> scores;
    };
    
}
