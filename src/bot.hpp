#ifndef BOT_HPP
#define BOT_HPP

#include "../lib/glm/glm/glm.hpp"
#include "player.hpp"

namespace agario{

using namespace shapes;

class Bot : public Player{

private:

    glm::vec2 maximize();

public:

    Bot(glm::vec2 pos): Player(pos, "BOT"){

    }

    virtual ~Bot(){

    }

    void setMousePosition(Map * map);
};

}

#endif