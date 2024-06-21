/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** Thread.cpp
*/

#include <thread>
#include "Thread.hpp"
#include "RessourcePool.hpp"

Zappy::Thread::Thread()
{
    _running = true;
}

Zappy::Thread::~Thread(){}

void Zappy::Thread::ManageServer(Server &s, Parser &p)
{
    while (_running) {
        s.receiveMess();
        p.parsing(s.getData());
        s.popData();
    }
}

void Zappy::Thread::setRunningFalse()
{
    _running = false;
}
