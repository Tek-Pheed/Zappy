/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** RessourcePool
*/

#include "RessourcePool.hpp"
#include <raylib.h>

template <> Model RessourcePool<Model>::loadObject(const std::string &path)
{
    return (LoadModel(path.c_str()));
}

template <>
Texture2D RessourcePool<Texture2D>::loadObject(const std::string &path)
{
    return (LoadTexture(path.c_str()));
}

template <> Music RessourcePool<Music>::loadObject(const std::string &path)
{
    return (LoadMusicStream(path.c_str()));
}

template <> void RessourcePool<Model>::unloadObject(Model &object)
{
    UnloadModel(object);
}

template <> void RessourcePool<Music>::unloadObject(Music &object)
{
    UnloadMusicStream(object);
}

template <> void RessourcePool<Texture2D>::unloadObject(Texture2D &object)
{
    UnloadTexture(object);
}