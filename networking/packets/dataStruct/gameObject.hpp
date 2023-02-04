#pragma once

#include "IGameObject.hpp"

namespace RType {
    namespace Network {
        class GameObject : public IGameObject {
            public:
                void setX(double x);
                void setY(double y);
                void setCelerity(double v);
                void setHealth(int health);
                void setStrength(int strength);
                void setType(int type);
                void setPlayerNumber(int playerNumber);
                double getX();
                double getY();
                double getCelerity();
                int getHealth();
                int getStrength();
                int getType();
                int getPlayerNumber();

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