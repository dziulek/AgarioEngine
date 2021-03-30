#include "SFMLRenderer.hpp"
#include <cmath>
#include <iostream>


namespace agario{

using namespace agario::shapes;

bool SFMLRenderer::loadFont(std::string fileName){

    if(!this->font.loadFromFile(fileName)){
        return false;
    }
    return true;
}

void SFMLRenderer::drawMap(){

    this->window->setView(*view);
    //draw only borders
    sf::VertexArray borders(sf::LineStrip, 5);
    borders[0] = sf::Vertex(sf::Vector2f(0.0f, 0.0f));
    borders[1] = sf::Vertex(sf::Vector2f(0.0f, game->getMap()->height));
    borders[2] = sf::Vertex(sf::Vector2f(game->getMap()->width, game->getMap()->height));
    borders[3] = sf::Vertex(sf::Vector2f(game->getMap()->width, 0.0f));
    borders[4] = sf::Vertex(sf::Vector2f(0.0f, 0.0f));

    window->draw(borders);

    //draw minis
    sf::CircleShape mm(MINI_RADIUS);
    mm.setOrigin(MINI_RADIUS, MINI_RADIUS);
    for(auto & i : game->getMap()->minis){

        for(auto & j : i){

            for(auto & k : j){

                if(k.get() == nullptr){
                    std::cout<<"nie"<<std::endl;
                    continue;
                }
                mm.setPosition({k.get()->getPosition().x, k.get()->getPosition().y});
                mm.setFillColor(sf::Color(k.get()->getColor()));
                window->draw(mm);
            }
        }
    }
    //draw bombs
    for(auto & b : this->game->getMap()->bombs){

        sf::CircleShape octagon(BOMB_RADIUS, 8);
        octagon.setOrigin(sf::Vector2f(BOMB_RADIUS, BOMB_RADIUS));
        octagon.setPosition(sf::Vector2f(b.get()->getXCoord(), b.get()->getYCoord()));
        octagon.setFillColor(sf::Color::Green);
        window->draw(octagon);

    }

    //  draw other shapes
    for(auto & shape : this->game->getMap()->abandoned){
        sf::CircleShape w(shape.get()->getRadius());
        w.setFillColor(sf::Color(shape.get()->getColor()));
        w.setOrigin(sf::Vector2f(shape.get()->getRadius(), shape.get()->getRadius()));

        w.setPosition(sf::Vector2f(shape.get()->getPosition().x, shape.get()->getPosition().y));

        window->draw(w);
    }
   
   //draw players
   for(int i = 0; i < this->game->getnOfPlayers(); i++){

       for(int j = 0; j < game->getPlayer(i).getSize(); j++){
           
           float r = game->getPlayer(i)[j].getRadius();
           sf::CircleShape blob(r);
           blob.setFillColor(sf::Color(game->getPlayer(i)[j].getColor()));
           blob.setOutlineColor(sf::Color::Magenta);
           blob.setOutlineThickness(0.2f);
           blob.setOrigin(sf::Vector2f(r,r));

           blob.setPosition(sf::Vector2f(game->getPlayer(i)[j].getPosition().x,
                            game->getPlayer(i)[j].getPosition().y));
            window->draw(blob);

            sf::Vector2f pos = sf::Vector2f(game->getPlayer(i)[j].getPosition().x, game->getPlayer(i)[j].getPosition().y);

            sf::Vertex line[2] = {
                sf::Vertex(pos),
                sf::Vertex(pos + sf::Vector2f(game->getPlayer(i)[j].getVelocity().x, game->getPlayer(i)[j].getVelocity().y))
            };

            window->draw(line, 2, sf::Lines);

            //draw size of blobs
            // sf::Text text;
            // text.setFont(this->font);
            // text.setString(std::to_string(1));
            // text.setCharacterSize(1);
            // text.setFillColor(sf::Color::Black);
            // text.setOrigin(text.getLocalBounds().width / 2.f, 1);
            // text.setPosition(game->getPlayer(i)[j].getPosition().x, game->getPlayer(i)[j].getPosition().y);
            // window->draw(text);
       }
   }
}

}