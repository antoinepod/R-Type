/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** deserialization.cpp
*/

#include "Deserialization.hpp"


std::vector<Network::Object> Network::Deseria::D_eserialize(boost::array<char, 1024>& buffer) {
    Network::Object gameObject;
    std::size_t pos = 0;
    std::size_t size = 0;
    std::vector<Network::Object> gameObjectHolder;

    size = getMeta(buffer, pos);
    //std::cout << "the buffer size is: " << size << std::endl;
    for (int i = 0; i < size; i++) {
        // TODO
        // gameObject.setName(getStringValue(buffer, pos));
        gameObject.setX(getFloatValue(buffer, pos));
        gameObject.setY(getFloatValue(buffer, pos));
        gameObject.setCelerity(getFloatValue(buffer, pos));
        gameObject.setHealth(getIntValue(buffer, pos));
        gameObject.setStrength(getIntValue(buffer, pos));
        gameObject.setId(getIntValue(buffer, pos));
        gameObject.setType((ObjectType)getIntValue(buffer, pos));
        gameObject.setFrame(getIntValue(buffer, pos));
        gameObject.setExplosion((ExplosionType)getIntValue(buffer, pos));
        gameObject.setBullet((BulletType)getIntValue(buffer, pos));
        gameObjectHolder.push_back(gameObject);
    }
    return gameObjectHolder;
}

std::size_t Network::Deseria::getMeta(boost::array<char, 1024> buffer, std::size_t& pos) {
    std::size_t result = 0;
    std::memcpy(&result, buffer.data() + pos, sizeof(result));
    pos += sizeof(result);
    //std::cout << "size_t value: " << result << "and pos is: " << pos << std::endl;
    return result;
}

int Network::Deseria::getIntValue(boost::array<char, 1024> buffer, std::size_t& pos) {
    int result = 0;
    std::memcpy(&result, buffer.data() + pos, sizeof(result));
    pos += sizeof(result);
    ///std::cout << "int value: " << result << "and pos is: " << pos << std::endl;
    return result;
}

float Network::Deseria::getFloatValue(boost::array<char, 1024> buffer, std::size_t& pos) {
    float result = 0;
    std::memcpy(&result, buffer.data() + pos, sizeof(result));
    pos += sizeof(result);
    //std::cout << "double value: " << result << "and pos is: " << pos << std::endl;
    return result;
}

std::string Network::Deseria::getStringValue(boost::array<char, 1024> buffer, std::size_t& pos) {
    char result[] = "";
    std::memcpy(&result, buffer.data() + pos, sizeof(result));
    pos += sizeof(result);
    //std::cout << "double value: " << result << "and pos is: " << pos << std::endl;
    return std::string(result);
}
