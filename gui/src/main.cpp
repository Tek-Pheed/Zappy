/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** main.cpp
*/

#include "../include/ServerData.hpp"

int main(int ac, char **av)
{
    int port = std::stoi(av[1]);

    Zappy::Server serv(port, av[2]);
    serv.messConnect();
    while (true) {
        serv.receiveMess();
        std::queue<std::queue<std::string>> result = serv.getData();
        while (!result.empty()) {
            std::queue<std::string> lineQueue = result.front();
            while (!lineQueue.empty()) {
                std::cout << lineQueue.front() << " ";
                lineQueue.pop();
            }
            std::cout << std::endl;
            result.pop();
            serv.popData();
        }
    }
    return 0;
}
