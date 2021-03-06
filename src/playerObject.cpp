#include "playerObject.hpp"

namespace agario{

using namespace shapes;

void PlayerObject::divideObject(){

    if(blobs.size() <= MAX_PLAYER_SIZE / 2){

        std::vector<std::unique_ptr<MoveableCircle>> tempVec;
        for(auto & b : blobs){
            if(b.get()->getArea() < 2 * MIN_PLAYER_AREA)
                continue;
            b.get()->addMass(-b.get()->getArea()/2);
            glm::vec2 new_position = b.get()->getPosition() 
                            + glm::normalize(this->mousePosition - b.get()->getPosition()) * b.get()->getRadius() * 1.1f;
            tempVec.push_back(std::unique_ptr<MoveableCircle>(new MoveableCircle(new_position, Circle::getRadiusFromArea(b.get()->getArea())))); 
        }

        for(auto & temp : tempVec){
            glm::vec2 dir = MoveableCircle::accelerationFun(0.1)
             * glm::normalize(this->mousePosition - temp.get()->getPosition());
            temp->setAcceleration(dir);
            this->blobs.push_back(std::move(temp));
            this->blobs.back().get()->setColor(blobs.front()->getColor());
        }   

        this->last_division = {std::chrono::steady_clock::time_point::clock::now(), calcSeparationTime()}; 
    }
        
}

void PlayerObject::addMass(const float mass){

    
}

void PlayerObject::move(const float dTime){

    for(auto & mc : blobs){
        
        mc->move(dTime);
    }
}

float PlayerObject::calcSeparationTime(){
    
    return (this->getTotalArea() / blobs.size()) / 5.0f;
}

bool PlayerObject::canMerge(std::chrono::steady_clock::time_point tp){

    return (std::chrono::duration_cast<std::chrono::seconds>(tp - this->last_division.first).count() 
                    >= this->last_division.second ? true : false);
}

void PlayerObject::setPosition(const glm::vec2 pos){

}

float PlayerObject::getTotalArea(){

    float sum = 0;

    for(auto & mc : blobs){
        sum += mc->getArea();
    }

    return sum;
}

int PlayerObject::getSize(){

    return this->blobs.size();
}

MoveableCircle & PlayerObject::operator[](int t){

    return *blobs[t].get();
}

void PlayerObject::setVelocities(){
    if(blobs.size() == 0) return;

    for(auto & b : blobs){

        glm::vec2 v = mousePosition - b.get()->getPosition();

        glm::vec2 before = v;

        // std::cout << before.x << " " << before.y << std::endl;
        if(abs(v.x) < 1.0 && abs(v.y) < 1.0)
            v = glm::vec2(0.f, 0.f);
        else v = glm::normalize(v);

        v *= b.get()->calculateVelocityMod();

        b.get()->setVelocity(v);
    }

    if(!canMerge(std::chrono::steady_clock::now())){

        MoveableCircle * temp_b1, * temp_b2;
        for(int i = 0; i < blobs.size() - 1; i++){
            for(int j = i + 1; j < blobs.size(); j++){ 
                
                temp_b1 = blobs[i].get();
                temp_b2 = blobs[j].get();
                glm::vec2 ax = glm::normalize(temp_b2->getPosition() - temp_b1->getPosition());
                float dist = glm::distance(temp_b1->getPosition(), temp_b2->getPosition());
                float min_dist = temp_b2->getRadius() + temp_b1->getRadius();

                if(dist < temp_b2->getRadius() + temp_b1->getRadius() && glm::length(temp_b1->getAcceleration()) < 0.1f &&
                        glm::length(temp_b2->getAcceleration()) < 0.1f){

                    auto new_velocities = MoveableCircle::calculateGravityVelocities(*temp_b1, *temp_b2);
                    temp_b1->setVelocity(new_velocities.first);
                    temp_b2->setVelocity(new_velocities.second);

                }

                // if(abs(glm::distance(temp_b1->getPosition(), temp_b2->getPosition()) - temp_b2->getRadius() - temp_b1->getRadius()) < eps){

                //     //ax is a vector of length 1 from b1 to b2
                //     float dot_b1 = glm::dot(ax, temp_b1->getVelocity());
                //     float dot_b2 = glm::dot(ax, temp_b2->getVelocity());

                //     if(dot_b1 > 0.f){

                //         if(dot_b2 > 0.f){

                //             temp_b1->setVelocity(temp_b1->getVelocity() - ax * dot_b1 + ax * std::min(dot_b1, dot_b2));
                //             // temp_b1->setVelocity(temp_b1->getVelocity() - ax * dot_b1);
                //         }
                //         else {

                //             temp_b1->setVelocity(temp_b1->getVelocity() - ax * (dot_b1 + 0.3f));
                //             temp_b2->setVelocity(temp_b2->getVelocity() - ax * (dot_b2 - 0.3f));
                //         }
                //     }
                //     else {

                //         if(dot_b2 > 0){

                //             // temp_b1->setVelocity(temp_b1->getVelocity() + ax * (dot_b1 + 0.1f));
                //             // temp_b2->setVelocity(temp_b2->getVelocity() - ax * (dot_b1 + 0.1f));
                //         }
                //         else {

                //             temp_b2->setVelocity(temp_b2->getVelocity() + ax * dot_b2 - ax * std::min(dot_b2, dot_b1));
                //             // temp_b2->setVelocity(temp_b2->getVelocity() + ax * dot_b2);
                //         }
                //     }
                // }
            }

        } 

        for(auto & blob : blobs){
            float d = glm::length(mousePosition - blob.get()->getPosition());
            if(d <= blob.get()->getRadius()){

                // blob.get()->setVelocity({0.f, 0.f});
                blob.get()->setVelocity(blob.get()->getVelocity() * d / blob.get()->getRadius());
            }
        }       
    }
}

void PlayerObject::addMass(const float mass, int mcIndex){

    blobs[mcIndex].get()->addMass(mass);
}

void PlayerObject::deleteIthElement(int i){

    blobs[i].reset();
    blobs[i] = std::move(blobs.back());

    blobs.pop_back();
    blobs.shrink_to_fit();

}

void PlayerObject::resetIthElement(int i){

    blobs[i].reset();
}

std::pair<glm::vec2, glm::vec2> PlayerObject::getMinRectangle(){

    if(this->blobs.size() == 0){
        return {glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f)};
    }

    glm::vec2 left_upper = glm::vec2(PLUS_INFINITY, PLUS_INFINITY);
    glm::vec2 down_right = glm::vec2(MINUS_INFINITY, MINUS_INFINITY);

    for(auto & blob : blobs){

        left_upper.x = std::min(left_upper.x, blob.get()->getPosition().x - blob.get()->getRadius());
        left_upper.y = std::min(left_upper.y, blob.get()->getPosition().y - blob.get()->getRadius());

        down_right.x = std::max(down_right.x, blob.get()->getPosition().x + blob.get()->getRadius());
        down_right.y = std::max(down_right.y, blob.get()->getPosition().y + blob.get()->getRadius());
    }

    return {left_upper, down_right};
}

float PlayerObject::bombAction(const unsigned int blob_index){


}

float PlayerObject::bombAction(std::unique_ptr<MoveableCircle> & mv){

    if(this->blobs.size() >= MAX_PLAYER_SIZE){

        //eat the bomb
    }
    else {

        int nOfnewBlobs = MAX_PLAYER_SIZE - this->blobs.size();
        float newAreaBlob = mv.get()->getArea() / (float)nOfnewBlobs;
        float new_radius = Circle::getRadiusFromArea(newAreaBlob);

        glm::vec2 explosionCenter = mv.get()->getPosition();

        auto color = mv.get()->getColor();

        mv.reset();
        mv = std::move(this->blobs.back());
        blobs.pop_back();

        float x, y, r = 1.f, deg = 2*PI / (float)(nOfnewBlobs + 1);

        for(int i = 0; i < nOfnewBlobs + 1; i++){

            x = explosionCenter.x + cos(float(i) * deg) * r;
            y = explosionCenter.y + sin(float(i) * deg) * r;

            this->blobs.push_back(std::unique_ptr<MoveableCircle>(new MoveableCircle(glm::vec2(x, y), new_radius)));
            this->blobs.back()->setColor(color);
            glm::vec2 dir = MoveableCircle::accelerationFun(0.1f)
             * glm::normalize(blobs.back().get()->getPosition() - explosionCenter);
            blobs.back()->setAcceleration(dir);
        }

        this->last_division = {std::chrono::steady_clock::time_point::clock::now(), calcSeparationTime()}; 
    }
}

}