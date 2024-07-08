//
// client.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2024 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <array>
#include <iostream>
#include <boost/asio.hpp>
#include <string>

#include "gamelogic.hpp"

#include "client.hpp"

using boost::asio::ip::tcp;

namespace RPS {

    int run_client(char* name)
    {
        try
        {
            boost::asio::io_context io_context;

            rps_client client(io_context, name);
            io_context.run();
        }
        catch (std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }

        return EXIT_SUCCESS;
    }

    rps_client::rps_client(boost::asio::io_context& io_context, char* input_name) : io_context(io_context), socket(io_context) {
        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints = resolver.resolve("", "13");

        boost::asio::connect(socket, endpoints);
        this->name = input_name;

        while (name.size() == 0 || name.size() > 128) {
            std::cout << "The selected name is too long, please select a name shorter than 128 characters!\n";
            name = "";
            std::cin >> name;
        }

        buf.resize(128);

        boost::asio::post(io_context,
            [&]()
            {
                boost::asio::async_write(socket,
                    boost::asio::buffer(name, name.length()),
                    [&](boost::system::error_code ec, std::size_t /*length*/)
                    {
                        play_client(io_context, socket);
                    }
                );
            }
        );
    }

    void rps_client::play_client(boost::asio::io_context& io_context, tcp::socket& socket) {
        boost::asio::post(io_context,
            [&]() {
                boost::asio::async_read_until(socket,
                    buffer, "\0",
                    [&](boost::system::error_code ec, std::size_t /*length*/)
                    {
                        std::string data{
                            std::istreambuf_iterator<char>(&buffer),
                            std::istreambuf_iterator<char>()
                        };

                        int ack = data.compare("ack");
                        int won = data.compare("won");
                        int lost = data.compare("lost");
                        std::cout << data << "\n";
                        if (ack == 0 || won == 0) {
                            write_choice(io_context, socket);
                        }
                        else if (lost == 0) {
                            socket.close();
                            return;
                        }
                    }
                );
            }
        );
    }

    void rps_client::write_choice(boost::asio::io_context& io_context, tcp::socket& socket) {
        int choice = rand() % 3;
        buf.clear();
        buf = std::to_string(choice);
        boost::asio::post(io_context, 
            [&]() {
                boost::asio::async_write(socket,
                    boost::asio::buffer(buf.data(), 1),
                    [&](const boost::system::error_code& /*error*/, size_t /*bytes_transferred*/) { play_client(io_context, socket); }
                );
            }
        );
    }
}
