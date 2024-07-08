#pragma once

#include <queue>
#include <functional>

#include <boost/asio.hpp>

#include "scoreboard.hpp"
#include "gamelogic.hpp"
#include "connection.hpp"

namespace RPS {

    using boost::asio::ip::tcp;
    typename session::pointer;

    class server {
    public:
        server(boost::asio::io_context& io_context);

        inline std::vector<std::thread>& get_threads() { return threads; }
    private:
        void start_accept();

        void handle_accept(session::pointer new_connection, const boost::system::error_code& error);

        boost::asio::io_context& io_context_;
        tcp::acceptor acceptor_;

        std::vector<std::thread> threads;
        scoreboard highscores;
        std::mutex accept_mutex;
    };

    void run_server();


}
