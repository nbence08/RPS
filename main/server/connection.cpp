#include <iostream>
#include <syncstream>

#include "connection.hpp"
#include "gamelogic.hpp"
#include "scoreboard.hpp"

namespace RPS {
    
    session::pointer session::create(boost::asio::io_context& io_context, scoreboard& highscores) {
        return pointer(new session(io_context, highscores));
    }

    tcp::socket& session::socket() {
        return socket_;
    }

    void session::start() {
        auto self(shared_from_this());
        boost::asio::async_read_until(socket_,
            buffer, "\0",
            boost::asio::bind_executor(strand_,
                [this, self](boost::system::error_code ec, std::size_t /*length*/)
                {
                    std::string data{
                        std::istreambuf_iterator<char>(&buffer),
                        std::istreambuf_iterator<char>()
                    };
                    std::osyncstream(std::cout) << "New client: " << data << "\n";
                    score = 0;
                    name = data;
                    write_ack();
                }
            )
        );
    }

    //ack is the neutral signal to start a new game
    void session::write_ack() {
        auto self(shared_from_this());
        message_ = "ack";
        boost::asio::async_write(socket_,
            boost::asio::buffer(message_),
            boost::asio::bind_executor(strand_,
                [this, self](const boost::system::error_code& /*error*/, size_t /*bytes_transferred*/) { play_game(); }
            )
        );
        std::osyncstream(std::cout) << "Sending \"ack\" to " << name << " with score " << score << "\n";
    }

    void session::write_won() {
        auto self(shared_from_this());
        message_ = "won";
        boost::asio::async_write(socket_,
            boost::asio::buffer(message_),
            boost::asio::bind_executor(strand_,
                [this, self](const boost::system::error_code& /*error*/, size_t /*bytes_transferred*/) { play_game(); }
            )
        );
        std::osyncstream(std::cout) << "Sending \"won\" to " << name << " with score " << score << "\n";
    }

    void session::write_lost() {
        auto self(shared_from_this());
        message_ = "lost";
        boost::asio::async_write(socket_,
            boost::asio::buffer(message_),
            boost::asio::bind_executor(strand_,
                [this, self](const boost::system::error_code& /*error*/, size_t /*bytes_transferred*/) { }
            )
        );
        std::osyncstream(std::cout) << "Sending \"lost\" to " << name << " with score " << score << "\n";
    }

    void session::play_game() {
        auto self(shared_from_this());
        boost::asio::async_read_until(socket_,
            buffer, "\0",
            boost::asio::bind_executor(strand_,
                [this, self](boost::system::error_code ec, std::size_t /*length*/)
                {
                    std::string data{
                        std::istreambuf_iterator<char>(&buffer),
                        std::istreambuf_iterator<char>()
                    };
                    RPS::Choice client_choice = RPS::Choice(std::stoi(data));
                    RPS::Choice server_choice = RPS::Choice(rand() % 3);

                    int winner = RPS::decide_winner(client_choice, server_choice);

                    //handle different win scenarios

                    if (winner == 0) {
                        //draw
                        write_ack();
                    }
                    else if (winner == -1) {
                        //client won
                        score++;
                        write_won();
                    }
                    else if (winner == 1) {
                        //server won
                        std::osyncstream(std::cout) << "Trying to add score " << score << " to name " << name << "\n";
                        highscores.try_to_add_score({ score, name });
                        write_lost();
                    }
                }
            )
        );
    }
}
