#ifndef MOVABLE_CIRCLE_HPP
#define MOVABLE_CIRCLE_HPP

#include "circle.hpp"
#include "../../lib/glm/glm/glm.hpp"
#include <utility>
#include <cmath>
#include <iostream>

namespace agario{

namespace shapes{

class MoveableCircle : public Circle{

protected:

    glm::vec2 acceleration = glm::vec2(0.f, 0.f);
    glm::vec2 velocity = glm::vec2(0.f, 0.f);
    void calculateVelocity();

    // glm::vec2 calcResultantForce();
    

public:

    MoveableCircle(){
        Circle();
    }
    MoveableCircle(glm::vec2 pos, const float radius) : Circle(radius, pos){}
    virtual ~MoveableCircle(){}
    
    inline float calculateVelocityMod() const{
        return 40.f * pow(this->getArea(), -0.239);
    };
    void addMass(const float mass);
    const glm::vec2 getVelocity() const;
    void setVelocity(const glm::vec2 v);
    void setColor(uint32_t color){ this->color = color;}
    virtual void move(const float dTime);
    static std::pair<glm::vec2, glm::vec2> calculateGravityVelocities(const MoveableCircle & c1, const MoveableCircle & c2);
    void setAcceleration(glm::vec2 acc){this->acceleration = acc;}
    glm::vec2 getAcceleration(){ return this->acceleration;}    
    
    static float accelerationFun(const float x);
    static float invAccelerationFun(const float y);
};

}//namespace shapes

}//namespace agario



#endif