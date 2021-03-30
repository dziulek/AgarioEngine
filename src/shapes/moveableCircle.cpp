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
    glm::vec2 r_norm = glm::normalize(r);
    glm::vec2 v1 = c1.velocity, v2 = c2.velocity;

    float min_dist = c1.getRadius() + c2.getRadius();

    float dot_c1 = glm::dot(r_norm, c1.velocity);
    float dot_c2 = glm::dot(r_norm, c2.velocity);

    float threshold_c1 = glm::length(c1.calculateVelocityMod());
    float threshold_c2 = glm::length(c2.calculateVelocityMod());
    float delta = 1.f;

    threshold_c1 *= 1.2f;
    threshold_c2 *= 1.2f;

    // if(dot_c1 > 0.0f && dot_c2 < 0.0f){

    //     v1 += (-r_norm * dot_c1);
    //     v2 += (-r_norm * dot_c2); 
    // }
    // // else if(dot_c1 < 0.0f)



    if(len < glm::length(min_dist) - delta){

        v1 += -r_norm * threshold_c1;
        v2 += r_norm * threshold_c2;

        return {v1, v2};
    }
    //quadratic function coefficients
    float a = -threshold_c1 / (2 * min_dist * delta - delta * delta);
    float c = -a * min_dist * min_dist;

    v1 += -r_norm * quadraticFunction(a, 0.0f, c, len);
    a = -threshold_c2 / (2 * min_dist * delta - delta * delta);
    c = -a * min_dist * min_dist;
    v2 += r_norm * quadraticFunction(a, 0.0f, c, len);

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