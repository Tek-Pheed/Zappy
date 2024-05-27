/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <iostream>

class Server {
    public:
        Server();
        ~Server();
        void init_connection();
        std::string getData();
        void close_connection();

    protected:
    private:
};

#endif /* !SERVER_HPP_ */
