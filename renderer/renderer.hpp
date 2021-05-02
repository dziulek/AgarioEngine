#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "../src/agario_engine.hpp"
#include "../src/gameObject.hpp"

namespace agario{

class Renderer{

private:

    Game * game;

public:

    // virtual void drawGameObject(GameObject & gameObject) = 0;
    virtual void drawMap() = 0;
    Game * getGame(){return this->game;}

};

}

#endif