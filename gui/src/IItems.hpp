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
        virtual ~IItems() = default;
        virtual std::map<std::string, int> getPosition() = 0;
        virtual void setPosition(std::map<std::string, int> position) = 0;
        virtual int GetAmount() = 0;
        virtual void SetAmount(int amount) = 0;
        virtual std::vector<std::map<std::string, int>> getSameItems() = 0;
        virtual void addSameItems(std::map<std::string, int> position) = 0;
        // void RemoveItems(int amount); ???? a voir si on en a besoin

    protected:
    private:
};

#endif /* !IITEMS_HPP_ */
