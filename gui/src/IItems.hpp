/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** IItems
*/

#ifndef IITEMS_HPP_
#define IITEMS_HPP_

#include <vector>
#include <string>
#include <map>

class IItems {
    public:
        IItems();
        ~IItems();
        std::map<std::string, int> getPosition();
        void setPosition(positions: map<std::string string, int>);
        int GetAmount();
        void SetAmount(int amount);
        std::vector<std::map<std::string, int>> getSameItems();
        void addSameItems(std::map<std::string, int> position);
        // void RemoveItems(int amount); ???? a voir si on en a besoin

    protected:
    private:
};

#endif /* !IITEMS_HPP_ */
