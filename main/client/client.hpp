#pragma once

#include <string>

#include "boost/asio.hpp"

namespace RPS {
    using boost::asio::ip::tcp;

    int run_client(char* host);

    class rps_client {
    public:
        rps_client(boost::asio::io_context& io_context, char* name);

        void play_client(boost::asio::io_context& io_context, boost::asio::ip::tcp::socket& socket);
        void write_choice(boost::asio::io_context& io_context, boost::asio::ip::tcp::socket& socket);
        inline void set_name(const char* name) { this->name = name; }
    private:
        boost::asio::io_context& io_context;
        tcp::socket socket;
        std::string buf;
        boost::system::error_code error;
        boost::asio::streambuf buffer;
        std::string name;
    };
}
