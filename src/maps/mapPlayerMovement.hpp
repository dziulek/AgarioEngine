#ifndef MAP_PLAYER_MOVEMENT_HPP
#define MAP_PLAYER_MOVEMENT_HPP

#include "mapController.hpp"
#include <cmath>
#include <iostream>

namespace agario{

using namespace shapes;

class MapPlayerMovement : public MapController{

private:

    void check_borders();
    float borderForce(const float margin);

public:

    MapPlayerMovement(Map * map) : MapController(map){

    }
    void update() override;
};

}

#endif