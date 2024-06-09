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
    createItems(bloc);
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

void Zappy::Parser::newPlayer(std::queue<std::string> player)
{
    int nb_p = std::stoi(player.front());
    player.pop();
    int x = std::stoi(player.front());
    player.pop();
    int y = std::stoi(player.front());
    player.pop();
    int north = std::stoi(player.front());
    player.pop();
    int est = std::stoi(player.front());
    player.pop();
    int south = std::stoi(player.front());
    player.pop();
    int west = std::stoi(player.front());
    player.pop();
    int level = std::stoi(player.front());
    player.pop();
    std::string team = player.front();
}

void Zappy::Parser::positionPlayer(std::queue<std::string> player)
{
    int nb_p = std::stoi(player.front());
    player.pop();
    int x = std::stoi(player.front());
    player.pop();
    int y = std::stoi(player.front());
    player.pop();
    int north = std::stoi(player.front());
    player.pop();
    int est = std::stoi(player.front());
    player.pop();
    int south = std::stoi(player.front());
    player.pop();
    int west = std::stoi(player.front());
}

void Zappy::Parser::levelPlayer(std::queue<std::string> player)
{
    int nb_p = std::stoi(player.front());
    player.pop();
    int level = std::stoi(player.front());
}

void Zappy::Parser::inventoryPlayer(std::queue<std::string> player)
{
    int nb_p = std::stoi(player.front());
    player.pop();
    int x = std::stoi(player.front());
    player.pop();
    int y = std::stoi(player.front());
    player.pop();
    //items;
}

void Zappy::Parser::expulsion(std::queue<std::string> player)
{
    int nb_p = std::stoi(player.front());
}

void Zappy::Parser::broadcast(std::queue<std::string> player)
{
    int nb_p = std::stoi(player.front());
    player.pop();
    std::queue<std::string> message = player;
}

void Zappy::Parser::startInc(std::queue<std::string> player)
{
    std::list<int> list_n;
    int x = std::stoi(player.front());
    player.pop();
    int y = std::stoi(player.front());
    player.pop();
    int level = std::stoi(player.front());
    player.pop();
    while (!player.empty()){
        list_n.push_back(std::stoi(player.front()));
        player.pop();
    }
}

void Zappy::Parser::endInc(std::queue<std::string> player)
{
    int x = std::stoi(player.front());
    player.pop();
    int y = std::stoi(player.front());
    player.pop();
    std::string result = player.front();
}

void Zappy::Parser::layingEgg(std::queue<std::string> player)
{
    int nb_p = std::stoi(player.front());
}

void Zappy::Parser::dropRess(std::queue<std::string> player)
{
    int nb_p = std::stoi(player.front());
    player.pop();
    int nb_i = std::stoi(player.front());
}

void Zappy::Parser::collectRess(std::queue<std::string> player)
{
    int nb_p = std::stoi(player.front());
    player.pop();
    int nb_i = std::stoi(player.front());
}

void Zappy::Parser::death(std::queue<std::string> player)
{
    int nb_p = std::stoi(player.front());
}

void Zappy::Parser::laidEgg(std::queue<std::string> egg)
{
    int nb_e = std::stoi(egg.front());
    egg.pop();
    int nb_p = std::stoi(egg.front());
    egg.pop();
    int x = std::stoi(egg.front());
    egg.pop();
    int y = std::stoi(egg.front());
}

void Zappy::Parser::connectEgg(std::queue<std::string> egg)
{
    int nb_e = std::stoi(egg.front());
}

void Zappy::Parser::deathEgg(std::queue<std::string> egg)
{
    int nb_e = std::stoi(egg.front());
}

void Zappy::Parser::frequModification(std::queue<std::string> freq)
{
    int time_frq = std::stoi(freq.front());
}

void Zappy::Parser::endGame(std::queue<std::string> team)
{
    std::string team_name = team.front();
}

void Zappy::Parser::messServer(std::queue<std::string> mess)
{
    //utiliser la queue
}

void Zappy::Parser::unknowCommand()
{
    std::cout << "WRONG" << std::endl;
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
    if (tmpFront.front() == "pnw") {
        tmpFront.pop();
        newPlayer(tmpFront);
    }
    if (tmpFront.front() == "ppo") {
        tmpFront.pop();
        positionPlayer(tmpFront);
    }
    if (tmpFront.front() == "plv") {
        tmpFront.pop();
        levelPlayer(tmpFront);
    }
    if (tmpFront.front() == "pin") {
        tmpFront.pop();
        inventoryPlayer(tmpFront);
    }
    if (tmpFront.front() == "pex") {
        tmpFront.pop();
        expulsion(tmpFront);
    }
    if (tmpFront.front() == "pbc") {
        tmpFront.pop();
        broadcast(tmpFront);
    }
    if (tmpFront.front() == "pic") {
        tmpFront.pop();
        startInc(tmpFront);
    }
    if (tmpFront.front() == "pie") {
        tmpFront.pop();
        endInc(tmpFront);
    }
    if (tmpFront.front() == "pfk") {
        tmpFront.pop();
        layingEgg(tmpFront);
    }
    if (tmpFront.front() == "pdr") {
        tmpFront.pop();
        dropRess(tmpFront);
    }
    if (tmpFront.front() == "pgt") {
        tmpFront.pop();
        collectRess(tmpFront);
    }
    if (tmpFront.front() == "pdi") {
        tmpFront.pop();
        death(tmpFront);
    }
    if (tmpFront.front() == "enw") {
        tmpFront.pop();
        laidEgg(tmpFront);
    }
    if (tmpFront.front() == "ebo") {
        tmpFront.pop();
        connectEgg(tmpFront);
    }
    if (tmpFront.front() == "edi") {
        tmpFront.pop();
        deathEgg(tmpFront);
    }
    if (tmpFront.front() == "sst") {
        tmpFront.pop();
        frequModification(tmpFront);
    }
    if (tmpFront.front() == "seg") {
        tmpFront.pop();
        endGame(tmpFront);
    }
    if (tmpFront.front() == "smg") {
        tmpFront.pop();
        messServer(tmpFront);
    }
    // if (tmpFront.front() == "sbp") {
    //     tmpFront.pop();
    // }
    if (tmpFront.front() == "suc") {
        tmpFront.pop();
        unknowCommand();
    }
}
