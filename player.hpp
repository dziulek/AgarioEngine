#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "playerObject.hpp"
#include "glm/glm.hpp"
#include <vector>
#include <string>

namespace agario{

using namespace shapes;

class Player : public PlayerObject{

private:

    std::string nick = "";
    float mass;
    float highestScore;
    int highestPosition;

public:

    Player(glm::vec2 pos, std::string nickname) : PlayerObject(pos){
        
        nick = nickname;
    }
    virtual ~Player(){}

};

}

#endif