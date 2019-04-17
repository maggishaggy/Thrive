#pragma once

#include "general/json_registry.h"

#include <OgreColourValue.h>
#include <map>
#include <string>
#include <vector>

class CScriptArray;

namespace thrive {

struct BiomeCompoundData {
public:
    unsigned int amount = 0;
    double density = 1.0f;
    double dissolved = 0.0f;

    BiomeCompoundData() {}

    BiomeCompoundData(unsigned int amount, double density, double dissolved) :
        amount(amount), density(density), dissolved(dissolved)
    {}
};

struct ChunkCompoundData {
public:
    unsigned int amount = 0;
    std::string name;
    ChunkCompoundData() {}

    // Move constructor
    ChunkCompoundData(ChunkCompoundData&& other) :
        name(std::move(other.name)), amount(other.amount)
    {}

    // Copy constructor
    ChunkCompoundData(const ChunkCompoundData& other) :
        name(other.name), amount(other.amount)
    {}

    ChunkCompoundData(unsigned int amount, std::string name) :
        amount(amount), name(name)
    {}
};

struct ChunkData {
public:
    std::string name = "";
    double density = 1.0f;
    bool dissolves = true;
    unsigned int radius = 0;
    unsigned int mass = 0;
    unsigned int size = 0;
    double ventAmount = 3.0f;

    std::vector<std::string> meshes;
    std::map<size_t, ChunkCompoundData> chunkCompounds;

    // Move constructor
    ChunkData(ChunkData&& other) :
        name(std::move(other.name)), dissolves(other.dissolves),
        radius(other.radius), mass(other.mass), size(other.size),
        ventAmount(other.ventAmount)
    {
        meshes = std::move(other.meshes);
        chunkCompounds = std::move(other.chunkCompounds);
    }

    // Copy constructor
    ChunkData(const ChunkData& other) :
        name(other.name), dissolves(other.dissolves),
        radius(other.radius), mass(other.mass), size(other.size),
        ventAmount(other.ventAmount)
    {
        meshes = other.meshes;
        chunkCompounds = other.chunkCompounds;
    }

    ChunkData() {}

    ChunkData(std::string name, double density, bool dissolves) :
        name(name), density(density), dissolves(dissolves)
    {}

    ChunkCompoundData*
        getCompound(size_t type);

    CScriptArray*
        getCompoundKeys() const;
};

class SimulationParameters;

class Biome : public RegistryType {
public:
    std::map<size_t, BiomeCompoundData> compounds;
    std::map<size_t, ChunkData> chunks;
    std::string background = "error";

    Ogre::ColourValue specularColors;
    Ogre::ColourValue diffuseColors;
    // Ambient Lights
    Ogre::ColourValue upperAmbientColor;
    Ogre::ColourValue lowerAmbientColor;

    float lightPower;
    Biome();

    Biome(Json::Value value);

    BiomeCompoundData*
        getCompound(size_t type);
    CScriptArray*
        getCompoundKeys() const;
};

} // namespace thrive
