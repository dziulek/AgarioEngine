#include "player.hpp"


namespace agario{

using namespace shapes;

std::pair<glm::vec2, glm::vec2> Player::getView(){

    std::pair<glm::vec2, glm::vec2> viewCoord = this->getMinRectangle(), out;

    if(viewCoord.first.x >= viewCoord.second.x || viewCoord.first.y >= viewCoord.second.y)
        return {glm::vec2(-20.0, -20.0), glm::vec2(DEFAULT_MAP_WIDTH + 20.0, DEFAULT_MAP_HEIGHT + 20.0)};

    float x_pad, y_pad;

    x_pad = y_pad = 50;

    out.first = glm::vec2(viewCoord.first.x - x_pad, viewCoord.first.y - y_pad);
    out.second = glm::vec2(viewCoord.second.x + x_pad, viewCoord.second.y + y_pad);

    return out;
}

void Player::setColor(){

    this->color = AGARIO_COLORS[rand()%n_colors];

    for(auto & blob : *this->getBlobs()){

        blob.get()->setColor(this->color);
    }
}

}