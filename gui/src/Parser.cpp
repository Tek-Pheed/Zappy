/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Parser.cpp
*/

#include <iostream>
#include "Items.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "RessourcePool.hpp"
#include "ServerData.hpp"

Zappy::Parser::Parser()
{
    _ifInc = false;
    _ifBroadcast = false;
}

Zappy::Parser::~Parser()
{
}

std::vector<Zappy::items> Zappy::Parser::createItems(
    std::queue<std::string> items)
{
    std::vector<Zappy::items> listOfItems;
    int i = 0;

    while (!items.empty()) {
        int nbElem = std::stoi(items.front());
        if (i == 6)
            break;
        while (nbElem != 0) {
            if (i <= 6 && i >= 0)
                listOfItems.push_back(static_cast<Zappy::items>(i));
            nbElem--;
        }
        i++;
        items.pop();
    }
    return listOfItems;
}

std::vector<Zappy::Player> createPlayerMap(
    std::queue<std::string> nbPlayer, int x, int y)
{
    std::vector<Zappy::Player> playerList;
    int nb = std::stoi(nbPlayer.front());

    while (nb != 0) {
        Zappy::Player p;

        p.setPositionX(x);
        p.setPositionY(y);
        playerList.push_back(p);
        nb--;
    }
    return playerList;
}

Zappy::Bloc *Zappy::Parser::createBloc(std::queue<std::string> bloc)
{
    std::unique_lock lock(_mut);
    std::queue<std::string> tmpBloc = bloc;
    if (bloc.size() < 3)
        return nullptr;
    int x = std::stoi(bloc.front());
    bloc.pop();
    int y = std::stoi(bloc.front());
    bloc.pop();
    Bloc *ptr = _map.getBloc(x,y);

    if (ptr != nullptr) {
        ptr->setItems(createItems(bloc));
        ptr->setPlayers(createPlayerMap(bloc, x, y));
        return ptr;
    }
    if (!_map.getBloc().empty() && 
    _map.getBloc().size() == (unsigned int)(_map.getX() * _map.getY()))
        _map.popBloc();
    Bloc *newbloc = new Bloc(x, y);
    newbloc->setItems(createItems(bloc));
    newbloc->setPlayers(createPlayerMap(bloc, x, y));
    _map.pushBloc(newbloc);
    return newbloc;
}

void Zappy::Parser::createMap(std::queue<std::string> map, Map realmap)
{
    std::unique_lock lock(_mut);
    int x = std::stoi(map.front());
    map.pop();
    int y = std::stoi(map.front());
    map.pop();
    realmap.setX(x);
    realmap.setY(y);
}

void Zappy::Parser::createTeams(std::queue<std::string> teams)
{
    std::unique_lock lock(_mut);
    while (!teams.empty()) {
        std::cout << "Teams name: " << teams.front().c_str() << std::endl;
        teams.pop();
    }
}

int Zappy::Parser::createFrequ(std::queue<std::string> freq)
{
    std::unique_lock lock(_mut);
    int nbFreq = std::stoi(freq.front());
    return nbFreq;
}

Zappy::Player *Zappy::Parser::newPlayer(std::queue<std::string> player)
{
    std::unique_lock lock(_mut);
    int nb_p = std::stoi(player.front());
    player.pop();
    int x = std::stoi(player.front());
    player.pop();
    int y = std::stoi(player.front());
    player.pop();
    int orien = std::stoi(player.front());
    player.pop();
    player.pop();
    std::string team = player.front();
    Player *newPlayer = new Player();
    newPlayer->setID(nb_p);
    newPlayer->setPositionX(x);
    newPlayer->setPositionY(y);
    newPlayer->setPositionN(orien);
    newPlayer->setLvl(1);
    return newPlayer;
}

void Zappy::Parser::positionPlayer(std::queue<std::string> player)
{
    std::unique_lock lock(_mut);
    if (player.size() <= 3)
        return;
    int nb_p = std::stoi(player.front());
    player.pop();
    int x = std::stoi(player.front());
    player.pop();
    int y = std::stoi(player.front());
    player.pop();
    int orien = std::stoi(player.front());
    if (_playersMap.getPlayersList()[nb_p] != nullptr) {
        _playersMap.getPlayersList()[nb_p]->setPositionX(x);
        _playersMap.getPlayersList()[nb_p]->setPositionY(y);
        _playersMap.getPlayersList()[nb_p]->setPositionN(orien);
    }
}

void Zappy::Parser::levelPlayer(std::queue<std::string> player)
{
    std::unique_lock lock(_mut);
    int nb_p = std::stoi(player.front());
    player.pop();
    _playersMap.getPlayersList()[nb_p]->setLvl(std::stoi(player.front()));
}

void Zappy::Parser::inventoryPlayer(std::queue<std::string> player)
{
    std::unique_lock lock(_mut);

    if (player.size() > 0)
        player.pop();
    if (player.size() > 0)
        player.pop();
    if (player.size() > 0)
        player.pop();
}

void Zappy::Parser::expulsion(std::queue<std::string> player)
{
    (void) player;
}

void Zappy::Parser::broadcast(std::queue<std::string> player)
{
    std::unique_lock lock(_mut);
    player.pop();
    std::queue<std::string> message = player;
    _ifBroadcast = true;
}

void Zappy::Parser::startInc(std::queue<std::string> player)
{
    std::unique_lock lock(_mut);
    std::list<int> list_n;
    player.pop();
    player.pop();
    player.pop();
    while (!player.empty()) {
        list_n.push_back(std::stoi(player.front()));
        player.pop();
    }
    _ifInc = true;
}

void Zappy::Parser::endInc(std::queue<std::string> player)
{
    std::unique_lock lock(_mut);
    player.pop();
    player.pop();
    std::string result = player.front();
    _ifInc = false;
}

void Zappy::Parser::layingEgg(std::queue<std::string> player)
{
    (void) player;
}

void Zappy::Parser::dropRess(std::queue<std::string> player)
{
    (void)player;
}

void Zappy::Parser::collectRess(std::queue<std::string> player)
{
    (void) player;
}

void Zappy::Parser::death(std::queue<std::string> player)
{
    std::unique_lock lock(_mut);
    int nb_p = std::stoi(player.front());
    std::map<int, Player *> doppel;
    doppel = _playersMap.getPlayersList();
    auto keydelete = doppel.find(nb_p);
    if (keydelete != doppel.end()) {
        std::unique_lock player_lock(keydelete->second->getMutex());
        doppel.erase(keydelete);
    }
    _playersMap.setPlayersList(doppel);
}

void Zappy::Parser::laidEgg(std::queue<std::string> egg)
{
    (void) egg;
}

void Zappy::Parser::connectEgg(std::queue<std::string> egg)
{
    (void) egg;
}

void Zappy::Parser::deathEgg(std::queue<std::string> egg)
{
    (void) egg;
}

void Zappy::Parser::frequModification(std::queue<std::string> freq)
{
    (void) freq;
}

void Zappy::Parser::endGame(std::queue<std::string> team)
{
    (void) team;
}

void Zappy::Parser::messServer(std::queue<std::string> mess)
{
    (void) mess;
}

void Zappy::Parser::unknowCommand()
{
    std::cout << "WRONG" << std::endl;
}

void Zappy::Parser::parsing(std::queue<std::queue<std::string>> data)
{
    std::queue<std::string> tmpFront;

    while (!data.empty()) {
        tmpFront = data.front();

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
            _playersMap.mapPlayers(newPlayer(tmpFront));
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
        if (tmpFront.front() == "suc") {
            tmpFront.pop();
            unknowCommand();
        }
        data.pop();
    }
}

Zappy::Map Zappy::Parser::getMap()
{
    return _map;
}

void Zappy::Parser::setMap(Zappy::Map map)
{
    _map = map;
}

void Zappy::Parser::createMap(std::queue<std::string> map)
{
    int x = std::stoi(map.front());
    map.pop();
    int y = std::stoi(map.front());
    map.pop();
    _map.setX(x);
    _map.setY(y);
}

Zappy::Players Zappy::Parser::getPlayersList()
{
    return _playersMap;
}

void Zappy::Parser::setPlayersList(Zappy::Players list)
{
    _playersMap = list;
}

void Zappy::Parser::setInc(bool ifInc)
{
    _ifInc = ifInc;
}

bool Zappy::Parser::getInc()
{
    return _ifInc;
}

void Zappy::Parser::setBroadcast(bool ifBroadcast)
{
    _ifBroadcast = ifBroadcast;
}

bool Zappy::Parser::getBroadcast()
{
    return _ifBroadcast;
}
