/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** gameObject.hpp
*/

#pragma once

#include "../../interfaces/IGameObject.hpp"

namespace RType {
    namespace Network {
        class GameObject : public IGameObject {
            public:
                void setX(double x){
                    this->_x = x;
                };
                void setY(double y){
                    this->_y = y;
                };
                void setCelerity(double v){
                    this->_v = v;
                };
                void setHealth(int health){
                    this->_health = health;
                };
                void setStrength(int strength){
                    this->_strength = strength;
                };
                void setType(int type){
                    this->_type = type;
                };
                void setPlayerNumber(int playerNumber){
                    this->_playerNumber = playerNumber;
                };
                double getX(){
                    return this->_x;
                };
                double getY(){
                    return this->_y;
                };
                double getCelerity(){
                    return this->_v;
                };
                int getHealth(){
                    return this->_health;
                };
                int getStrength(){
                    return this->_strength;
                };
                int getType(){
                    return this->_type;
                };
                int getPlayerNumber(){
                    return this->_playerNumber;
                };

            private:
                double _x;
                double _y;
                double _v;
                int _health;
                int _strength;
                int _playerNumber;
                int _type;
        };
    }
}