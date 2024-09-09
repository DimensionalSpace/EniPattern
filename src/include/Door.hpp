#pragma once


#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;
class Door
{
private:
   int Design;
   float openpos, closepos;
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
    void settexture(){
        if(horizontal){
            t.loadFromFile("Textures/Doors/DoorD"+ to_string(Design) +"h.png");
        }
        else{
            t.loadFromFile("Textures/Doors/DoorD"+ to_string(Design) +"v.png");
        }
        Wallbox.setTexture(t);
     }
    Door(int design, bool ishorizontal, sf::Vector2f pos ){
        horizontal = ishorizontal;
        Wallbox.setPosition(pos);
        
       Design = design;
       if(horizontal){
        openpos = Wallbox.getPosition().x -32;
        closepos = Wallbox.getPosition().x;
       }else{
         openpos = Wallbox.getPosition().y -32;
        closepos = Wallbox.getPosition().y;
       }
    }
    void drawTo(sf::RenderWindow &window){
        window.draw(Wallbox);
    }
    void update(bool openingcondition){
       
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


