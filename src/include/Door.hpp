#pragma once


#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;
class Door
{
private:
   
public:
    Sprite Wallbox;
    Texture t;
    bool horizontal;
    
    sf::FloatRect getglobalbounds(){
        return Wallbox.getGlobalBounds();
    }
    int GetY(){
        return Wallbox.getPosition().y;
    }
    int GetX(){
        return Wallbox.getPosition().x;
    }
    Door(const string& filename, bool ishorizontal, sf::Vector2f pos ){
        t.loadFromFile(filename);
        Wallbox.setTexture(t);
        horizontal = ishorizontal;
        Wallbox.setPosition(pos);
       
    }
    void drawTo(sf::RenderWindow &window){
        window.draw(Wallbox);
    }
    void update(bool openingcondition, float openpos, float closepos){
       
      if (horizontal) {
        float newpos = Wallbox.getPosition().x;
        if (openingcondition) {
            if (newpos > openpos) {
                newpos -= 1;
            }
        } else {
            if (newpos < closepos) {
                newpos += 1;
            }
        }
        Wallbox.setPosition(newpos, Wallbox.getPosition().y);
    } else {
        float newpos = Wallbox.getPosition().y;
        if (openingcondition) {
            if (newpos > openpos) {
                newpos -= 1;
            }
        } else {
            if (newpos < closepos) {
                newpos += 1;
            }
        }
        Wallbox.setPosition(Wallbox.getPosition().x, newpos);
    }

    // Debug output for door position
  
        
    }

};


