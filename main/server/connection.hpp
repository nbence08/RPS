#pragma once

#include "boost/asio.hpp"

namespace RPS {
    class scoreboard;
    using boost::asio::ip::tcp;

    class session : public std::enable_shared_from_this<session> {
    public:

        typedef std::shared_ptr<session> pointer;

        static pointer create(boost::asio::io_context& io_context, scoreboard& highscores);

        tcp::socket& socket();

        void start();
        void write_ack();
        void write_won();
        void write_lost();
        void play_game();

    private:
        inline session(boost::asio::io_context& io_context, scoreboard& highscores) : socket_(io_context), highscores(highscores), strand_(boost::asio::make_strand(io_context)), score(0) { }

        inline void handle_write(const boost::system::error_code& /*error*/, size_t /*bytes_transferred*/) { }

        tcp::socket socket_;
        boost::asio::streambuf buffer;
        std::string message_;

        std::string name;
        boost::asio::strand<boost::asio::io_context::executor_type> strand_;
        int score;

        scoreboard& highscores;
    };
}

