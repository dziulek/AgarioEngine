#include "mapMiniController.hpp"

namespace agario{

using namespace shapes;

void MapMiniController::update(){

    cullDeadMinis();

    int missing = MAX_MINIS_ON_MAP - this->getMap()->nOfMinis;

    if(missing > MAX_MISSING_MINIS){

        int xFields = this->getMap()->minis[0].size();
        int yFields = this->getMap()->minis.size();

        for(int i = 0; i < missing; i++){

            //pick random map coordinates
            float x = distribution("uniform") * this->getMap()->width;
            float y = distribution("uniform") * this->getMap()->height;
            //[optional] check for collision with another mini
            //not necessary
            //add to the map
            this->getMap()->minis[int(y / MINI_WIDTH)][int(x / MINI_WIDTH)].push_back(std::unique_ptr<Mini>(new Mini(glm::vec2(x, y))));
            
        }
        this->map->nOfMinis+=missing;
    }

}

void MapMiniController::initMap(){

    //resize minis vector if needed
    this->map->minis.resize(int(map->height / MINI_WIDTH) + 1);
    for(int i = 0; i < map->minis.size(); i++)
        map->minis[i].resize(int(map->width / MINI_WIDTH) + 1);
    //fill the map with minis

    for(int i = 0; i < MAX_MINIS_ON_MAP; i++){
        //pick random map roordinates
        float x = distribution("uniform") * this->getMap()->width;
        float y = distribution("uniform") * this->getMap()->height;
        //check for collision with another mini
        //not necessary
        //add to the map
        this->getMap()->minis[int(y / MINI_WIDTH)][int(x / MINI_WIDTH)].push_back(std::unique_ptr<Mini>(new Mini(glm::vec2(x, y))));
    }
    map->nOfMinis = MAX_MINIS_ON_MAP;
}

void MapMiniController::cullDeadMinis(){

    for(PlayerObject * p : map->playerObjects){

        for(int i = 0; i < p->getSize(); i++){

            //x coordinates
            int lowerBoundx = floor(((*p)[i].getPosition().x - (*p)[i].getRadius()) / MINI_WIDTH); 
            int upperBoundx = ceil(((*p)[i].getPosition().x + (*p)[i].getRadius()) / MINI_WIDTH);

            lowerBoundx = std::max(0, lowerBoundx);
            upperBoundx = std::min(upperBoundx, (int)map->minis[0].size() - 1);

            //y coordinates
            int lowerBoundy = floor(((*p)[i].getPosition().y - (*p)[i].getRadius()) / MINI_WIDTH);
            int upperBoundy = ceil(((*p)[i].getPosition().y + (*p)[i].getRadius()) / MINI_WIDTH);

            lowerBoundy = std::max(0, lowerBoundy);
            upperBoundy = std::min(upperBoundy, (int)map->minis.size() - 1);

            for(int j = lowerBoundx; j < upperBoundx; j++){
                
                for(int k = lowerBoundy; k < upperBoundy; k++){

                    for(auto & mc : map->minis[k][j]){
                        
                        if(mc.get() != nullptr && glm::length(mc->getPosition() - (*p)[i].getPosition()) < (*p)[i].getRadius()){
                            
                            float mass = mc.get()->getArea();
                            mc.reset();
                            mc = std::move(map->minis[k][j].back());
                            map->minis[k][j].pop_back();
                            map->nOfMinis--;

                            (*p)[i].addMass(mass);
                        }       
                    }
                }   
            }
        }
    }
}

float MapMiniController::distribution(const std::string name){

    if(name == "uniform"){

        return static_cast<float>(rand())/RAND_MAX;
    }
    else if(name == "gaussian"){
        
        return 1;
    }
     
    return -1;
}

}