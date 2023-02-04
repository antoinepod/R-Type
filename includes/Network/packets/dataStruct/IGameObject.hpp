#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <utility>
#include <memory>

namespace RType {
    namespace Network {
        class IGameObject {
            public:
                ~IGameObject() = default;
                virtual void setX(double x) = 0;
                virtual void setY(double y) = 0;
                virtual void setCelerity(double v) = 0;
                virtual void setHealth(int health) = 0;
                virtual void setStrength(int strength) = 0;
                virtual void setType(int type) = 0;
                virtual float getX() = 0;
                virtual float getY() = 0;
                virtual float getCelerity() = 0;
                virtual int getHealth() = 0;
                virtual int getStrength() = 0;
                virtual int getType() = 0;
        };
    }
}