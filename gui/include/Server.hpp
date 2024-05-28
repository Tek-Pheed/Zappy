/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Server
*/

#pragma once

#include <iostream>

namespace Zappy {
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
}
