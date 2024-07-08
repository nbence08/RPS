#include <ctime>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <boost/asio.hpp>
#include <syncstream>

#include "random_generator.hpp"
#include "gamelogic.hpp"
#include "server.hpp"
#include "connection.hpp"

//implementation based on boost example daytime server, see license below

//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2024 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

namespace RPS {

    using boost::asio::ip::tcp;

	void run_server() {
        try
        {
            boost::asio::io_context io_context;
            server server(io_context);
            io_context.run();

            for (auto& thread : server.get_threads()) {
                thread.join();
            }
        }
        catch (std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
	}

    server::server(boost::asio::io_context& io_context) : io_context_(io_context), acceptor_(io_context, tcp::endpoint(tcp::v4(), 13)) {
        auto thread_operation = [&]() {
            this->io_context_.run();
        };

        boost::asio::socket_base::reuse_address option(true);
        acceptor_.set_option(option);
        unsigned int thread_count = std::thread::hardware_concurrency();
        if (thread_count != 0) {
            thread_count /= 2;
        }

        for (int i = 0; i < thread_count; ++i) {
            threads.emplace_back(thread_operation);
        }
        start_accept();
        std::osyncstream(std::cout) << "Started server on port 13\n";
    }

    void server::start_accept() {
        session::pointer new_connection = session::create(io_context_, this->highscores);
        
        acceptor_.async_accept(new_connection->socket(),
            std::bind(&server::handle_accept,
                this, new_connection,
                boost::asio::placeholders::error
            )
        );
    }

    void server::handle_accept(session::pointer new_connection, const boost::system::error_code& error) {
        std::lock_guard guard(accept_mutex);
        if (!error) {
            new_connection->start();
        }

        start_accept();
    }
}