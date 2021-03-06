#include "mapBombController.hpp"

namespace agario{

using namespace shapes;

void MapBombController::update(){

    //only one explosion per player in one iteration
    bool explode = false;

    for(auto & p : this->getMap()->playerObjects){

        explode = false;
        for(auto & blob : *(p->getBlobs())){

            for(auto & bomb : this->getMap()->bombs){

                float dist = glm::length(blob.get()->getPosition() - bomb.get()->getPosition());
                if(dist < blob.get()->getRadius()){
                    
                    if(blob.get()->getArea() * 0.85 > bomb.get()->getArea()){
                        
                        float bomb_mass = bomb.get()->getArea();
                        bomb.reset();
                        bomb = std::move(this->getMap()->bombs.back());
                        this->getMap()->bombs.pop_back();
                        // std::cerr << p->getSize() << std::endl;


                        if(p->getSize() >= MAX_PLAYER_SIZE){
                            //eat bomb
                            blob.get()->addMass(bomb_mass);
                        }
                        else {
                            p->bombAction(blob);
                        }

                        explode = true;
                        break;                        
                    }
                }        
            }
            if(explode == true)
                break;
        }
    }
}

void MapBombController::initMap(){

    for(int i = 0; i < MAX_BOMB_ON_MAP; i++){

        float x = static_cast<float>(rand()) / RAND_MAX * this->getMap()->width;
        float y = static_cast<float>(rand()) / RAND_MAX * this->getMap()->height;

        this->getMap()->bombs.push_back(std::unique_ptr<Bomb>(new Bomb(glm::vec2(x, y))));
    }
}

}