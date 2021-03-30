#include "moveableCircle.hpp"

namespace agario{

namespace shapes{

void MoveableCircle::setVelocity(const glm::vec2 v){

    this->velocity = v;
    // this->acceleration = glm::normalize(v);
}

const glm::vec2 MoveableCircle::getVelocity() const{

    return this->velocity;
}

void MoveableCircle::move(const float dTime){

    glm::vec2 old = this->velocity;

    float dirx, diry;

    if(glm::length(acceleration) > eps && invAccelerationFun(glm::length(acceleration)) < 1.f){

        // this->acceleration -= this->acceleration / (3.f * (float)sqrt(this->area));
        this->acceleration = glm::normalize(this->acceleration) * accelerationFun(
            invAccelerationFun(glm::length(acceleration)) + dTime
        );
        // std::cerr<<glm::length(acceleration) <<" ";
        this->velocity += this->acceleration * dTime;        
    }
    else this->acceleration = {0.0f, 0.0f};
    // this->velocity += (glm::length(this->acceleration) > eps ? this->acceleration * dTime : glm::vec2(0.0f, 0.0f));

    dirx = old.x * this->velocity.x;
    diry = old.y * this->velocity.y;

    if(glm::length(this->velocity) > eps)
        centerPosition += dTime * velocity;
    // std::cout << glm::length(velocity) <<std::endl;
}

std::pair<glm::vec2, glm::vec2> MoveableCircle::calculateGravityVelocities(const MoveableCircle & c1, const MoveableCircle & c2){

    glm::vec2 r = c2.getPosition() - c1.getPosition();
    float len = glm::length(r);
    // if(len < c1.getRadius() + c2.getRadius() - eps){

    //     return {c1.getVelocity(), c2.getVelocity()};
    // }

    float min_dist = c1.getRadius() + c2.getRadius();

    glm::vec2 v1 = c1.getVelocity() - glm::normalize(r) * (float)pow(c1.getRadius(), 2.f) * float(-log(len/(min_dist)));

    r = -r;
    glm::vec2 v2 = c2.getVelocity() - glm::normalize(r) * (float)pow(c2.getRadius(), 2.f) * float(-log(len/(min_dist)));

    return {v1, v2};
}

void MoveableCircle::addMass(const float mass){

    this->area += mass;
    float r = Circle::getRadiusFromArea(this->area);
    this->radius = r;
}

float MoveableCircle::accelerationFun(const float x){

    // return -30.f *log(x);
    // return 1.f / (x - 1.2) + 35.f;
    // return 1.f / (2.f - x * 1001.f / 1000.f) + 1010.5f;
    return -3000.f * (x * x - 1.f);

}

float MoveableCircle::invAccelerationFun(const float y){

    // return 1.f / (y - 35.f) + 1.2;
    // return (2.f - 1.f / (y - 1010.5f)) * 1000.f / 1001.f;
    return sqrt(-y/3000.f + 1.f);
}

}

}