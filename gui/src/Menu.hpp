/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include <iostream>

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

#endif /* !MENU_HPP_ */
