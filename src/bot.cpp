#include "bot.hpp"

namespace agario{

using namespace shapes;

glm::vec2 Bot::maximize(){

}

void Bot::setMousePosition(Map * map){

    auto rect = this->getMinRectangle();
    float min_dist = 1e9;

    // for(int i = (int)(rect.first.x / MINI_WIDTH); i < rect.second.x / MINI_WIDTH + 1; i++){

    //     for(int j = (int)(rect.first.y / MINI_WIDTH); j < rect.second.y / MINI_WIDTH + 1; j++){

            
    //     }
    // }
}

}