#include "mapPlayerMovement.hpp"

namespace agario{

using namespace shapes;

void MapPlayerMovement::update(){

    check_borders();
}

void MapPlayerMovement::check_borders(){

    
    //for each player
    for(auto & playerobject : map->playerObjects){

        //for each blob
        for(int i = 0; i < playerobject->getSize(); i++){

            glm::vec2 vel = glm::vec2(0.f, 0.f);
            float xPosition = (*playerobject)[i].getPosition().x;
            float yPosition = (*playerobject)[i].getPosition().y;
            float radius = (*playerobject)[i].getRadius();

            //left border
            float out = (*playerobject)[i].getPosition().x - (*playerobject)[i].getRadius();
            if(out < 0){
                vel += glm::vec2(borderForce(abs(out)), 0.f);
            }
            //right border
            out = (*playerobject)[i].getPosition().x + (*playerobject)[i].getRadius() - map->width;
            if(out > 0.f){
                vel += glm::vec2(-borderForce(abs(out)), 0.f);
            }
            out = (*playerobject)[i].getPosition().y - (*playerobject)[i].getRadius();
            //up border
            if(out < 0){
                vel += glm::vec2(0.f, borderForce(abs(out)));
            }
            //down border
            out = (*playerobject)[i].getPosition().y + (*playerobject)[i].getRadius() - map->height;
            if(out > 0){
                vel += glm::vec2(0.f, -borderForce(abs(out)));
            }

            (*playerobject)[i].setVelocity((*playerobject)[i].getVelocity() + vel);
        }

    }

    float xVel;
    float yVel;

    for(auto & w : map->abandoned){

        xVel = w.get()->getVelocity().x;
        yVel = w.get()->getVelocity().y;

        if(w.get()->getPosition().x - W_RADIUS < 0){
            w.get()->setVelocity({abs(xVel), yVel});
        }
        else if(w.get()->getPosition().x + W_RADIUS > map->width){
            w.get()->setVelocity({-abs(xVel), yVel});
        }
        if(w.get()->getPosition().y - W_RADIUS < 0){
            w.get()->setVelocity({xVel, abs(yVel)});
        }
        else if(w.get()->getPosition().y + W_RADIUS > map->height){
            w.get()->setVelocity({xVel, -abs(yVel)});
        }
    }
}

float MapPlayerMovement::borderForce(const float margin){

    return pow(2, margin/2);
}


}