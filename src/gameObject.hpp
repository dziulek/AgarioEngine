#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "./shapes/circle.hpp"
#include "constants.hpp"
#include "../lib/glm/glm/glm.hpp"

namespace agario{

using namespace shapes;

class GameObject {

public:

    virtual void setPosition(const glm::vec2 newPos) = 0;
    virtual void move(const float dTime) = 0;
    virtual void addMass(const float mass) = 0;
    virtual void divideObject() = 0;
};

}


#endif