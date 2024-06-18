/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** RessourcePool
*/

#pragma once
#include <iostream>
#include <raylib.h>
#include <string>
#include <unordered_map>

template <typename T> class RessourcePool {
  public:
    RessourcePool();
    ~RessourcePool();

    // Loads a ressource into the pool
    bool loadRessource(
        const std::string &keyName, const std::string &ressourcePath);

    // Returns a loaded ressource
    T &getRessource(const std::string &keyName);

    // Loads a ressource into the pool if it is not alredy loaded.
    // Otherwize, it just returns the ressource from the pool
    T &dynamicLoad(const std::string &keyName, const std::string &modelPath);

  private:
    T loadObject(const std::string &path);
    void unloadObject(T &object);
    std::unordered_map<std::string, T> _ressourceMap;
};

struct RessourceManager {
    RessourcePool<Model> models;
    RessourcePool<Texture> textures;
    RessourcePool<Music> musics;
};

template <typename T> RessourcePool<T>::RessourcePool()
{
}

template <typename T> RessourcePool<T>::~RessourcePool()
{
    for (auto &[key, value] : _ressourceMap)
        unloadObject(value);
}

template <typename T>
bool RessourcePool<T>::loadRessource(
    const std::string &keyName, const std::string &Path)
{
    if (_ressourceMap.find(keyName) != _ressourceMap.end()) {
        unloadObject(_ressourceMap[keyName]);
        _ressourceMap.erase(keyName);
    }
    try {
        _ressourceMap[keyName] = loadObject(Path);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;
}

template <typename T>
T &RessourcePool<T>::getRessource(const std::string &keyName)
{
    if (_ressourceMap.find(keyName) != _ressourceMap.end())
        return (_ressourceMap[keyName]);
    throw std::runtime_error(
        "Ressource: " + keyName + " was not loaded in the pool.");
}

template <typename T>
T &RessourcePool<T>::dynamicLoad(
    const std::string &keyName, const std::string &modelPath)
{
    if (_ressourceMap.find(keyName) != _ressourceMap.end())
        return (_ressourceMap[keyName]);
    loadRessource(keyName, modelPath);
    return (getRessource(keyName));
}
