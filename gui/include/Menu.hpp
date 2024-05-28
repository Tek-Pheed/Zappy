/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Menu
*/

#pragma once

#include <iostream>

namespace Zappy {
class Menu {
    public:
        Menu();
        ~Menu();
        void setHost(std::string host);
        void setPort(std::string port);

    protected:
    private:
        std::string _host;
        std::string _port;
};
}
