/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** GameObject.hpp
*/

#pragma once

#include "IGameObject.hpp"

    namespace Network {
        class GameObject : public IGameObject {
        public:
            void setX(float x){
                this->_x = x;
            };
            void setY(float y){
                this->_y = y;
            };
            void setCelerity(float v){
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
            float getX(){
                return this->_x;
            };
            float getY(){
                return this->_y;
            };
            float getCelerity(){
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
            float _x;
            float _y;
            float _v;
            int _health;
            int _strength;
            int _playerNumber;
            int _type;
        };
    }