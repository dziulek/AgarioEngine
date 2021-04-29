#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP



namespace agario{

namespace shapes{

const float eps = 0.01;
}//namespace shapes
//graphics
const float WINDOW_WIDTH = 1000;
const float WINDOW_HEIGHT = 1000;

//colors
const unsigned int BITTERSWEET = 0xfe6f5eff;
const unsigned int BARN_RED = 0x7c0a02ff;
const unsigned int BITTER_LIME = 0x648c11ff;
const unsigned int YELLOW = 0xffff00ff;
const unsigned int ORANGE = 0xff8000ff;
const unsigned int PINK = 0xff007fff;
const unsigned int BLUE_DE_FRANCE = 0x318ce7ff;
const unsigned int DARK_TANGERINE = 0xffa812ff;
const unsigned int DARK_MAGENTA = 0x8b008bff;
const unsigned int PLUM = 0xdda0ddff;
const unsigned int MAROON = 0x800000ff;

const unsigned int n_colors = 11;

const unsigned int AGARIO_COLORS[n_colors] = {
    BITTERSWEET, BARN_RED, BITTER_LIME, YELLOW, ORANGE, PINK, BLUE_DE_FRANCE, DARK_TANGERINE, DARK_MAGENTA, PLUM, MAROON
};
//physics

const float PLUS_INFINITY = 10e9;
const float MINUS_INFINITY = -10e9;
const float PI = 3.14159265359;
const float GRAVITY_CONST = 6;
const float OUT_FORCE_VALUE = 20;
const float MIN_PLAYER_RADIUS = 3;
const float MINI_RADIUS = 1.0f;
const float BOMB_RADIUS = 7;
const float DIVIDE_FORCE = 40;

const float FRICTION_COEFF = 0.2;

const int MAX_MINIS_ON_MAP = 300;
const int MAX_MISSING_MINIS = 50;
const int MAX_BOMB_ON_MAP = 10;
const float MINI_WIDTH = 50.0f;

const int DEFAULT_MAP_WIDTH = 300;
const int DEFAULT_MAP_HEIGHT = 300;

const int MAX_PLAYERS_IN_GAME = 5;
const int MAX_PLAYER_SIZE = 16;

const float W_ACCELERATION_VALUE = -0.3f;

const float W_AREA = PI * MIN_PLAYER_RADIUS * MIN_PLAYER_RADIUS;
const float MIN_PLAYER_AREA = W_AREA;
const float W_RADIUS = MIN_PLAYER_RADIUS;

//functions

constexpr float quadraticFunction(const float a, const float b, const float c, const float x){

    return a * x * x + b * x + c;
}

}//namespace agario

#endif