/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Map
*/

#ifndef MAP_HPP_
#define MAP_HPP_

class Map {
    public:
        Map();
        ~Map();
        void setX(int x);
        int getX();
        void setY(int y);
        int getY();

    protected:
    private:
        int _x;
        int _y;
};

#endif /* !MAP_HPP_ */
