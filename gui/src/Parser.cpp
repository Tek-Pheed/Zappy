/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Parser.cpp
*/

#include "../include/ServerData.hpp"
#include "../include/Items.hpp"

Zappy::Parser::Parser()
{
}

Zappy::Parser::~Parser()
{
}

std::list<Zappy::IItems> Zappy::Parser::createItems(std::queue<std::string> items)
{

}

void Zappy::Parser::createBloc(std::queue<std::string> bloc)
{
    int x = std::stoi(bloc.front());
    bloc.pop();
    int y = std::stoi(bloc.front());
    bloc.pop();
    std::cout << "Position Bloc x: " << x << ", y: " << y << std::endl;
}

void Zappy::Parser::createMap(std::queue<std::string> map)
{
    int x = std::stoi(map.front());
    map.pop();
    int y = std::stoi(map.front());
    map.pop();
    std::cout << "Position Map x: " << x << ", y: " << y << std::endl;
}

void Zappy::Parser::createTeams(std::queue<std::string> teams)
{
    while (!teams.empty()) {
        std::cout << "Teams name: " << teams.front().c_str() << std::endl;
        teams.pop();
    } 
}

void Zappy::Parser::createFrequ(std::queue<std::string> freq)
{
    int nbFreq = std::stoi(freq.front());
    std::cout << "Frequence: " << nbFreq << std::endl;
}

void Zappy::Parser::parsing(std::queue<std::queue<std::string>> data)
{
    std::queue<std::string> tmpFront = data.front();
    if (tmpFront.front() == "tna") {
        tmpFront.pop();
        createTeams(tmpFront);
    }
    if (tmpFront.front() == "sgt") {
        tmpFront.pop();
        createFrequ(tmpFront);
    }
    if (tmpFront.front() == "msz") {
        tmpFront.pop();
        createMap(tmpFront);
    }
    if (tmpFront.front() == "bct") {
        tmpFront.pop();
        createBloc(tmpFront);
    }
}
