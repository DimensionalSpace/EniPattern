#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include <math.h>
#include "AI.hpp"
#include "Door.hpp"
#include "Animation.hpp"
#include <iostream>
using namespace sf;
using namespace std;
class PushableItem{


private:
    Texture t;
    
public:
 Sprite character;
 int itemtype;
 FloatRect bounds = character.getGlobalBounds();
    PushableItem( Vector2f position, int pushableitemtype)
 {      
        itemtype = pushableitemtype;
      
        character.setPosition(position);
        
      
       
    };
    void SetTexture(){
        if(itemtype)
        t.loadFromFile("Textures/PushableItems/" + to_string(itemtype) + ".png");
        
        character.setTexture(t);
    }
    void Draw(RenderWindow& window){
        window.draw(character);
    }
    void setPosition(Vector2f pos){
        character.setPosition(pos);
    }
   
        
    
    void handleCollisions(const std::vector<Wall>& walls, const std::vector<Door>& doors, const std::vector<AI>& ai) {
     bounds = character.getGlobalBounds();
        sf::FloatRect characterBounds = character.getGlobalBounds();
        for (const Wall& wall : walls){
            
            sf::FloatRect wallBounds = wall.Wallbox.getGlobalBounds();
            

            if (characterBounds.intersects(wallBounds)) {
                sf::FloatRect overlap;
               
                characterBounds.intersects(wallBounds, overlap);

                if (overlap.width < overlap.height) {
                    if (characterBounds.left < wallBounds.left) {
                        character.setPosition(character.getPosition().x - overlap.width + 0.1f, character.getPosition().y);
                     
                    } else {
                        character.setPosition(character.getPosition().x + overlap.width -0.1f, character.getPosition().y);    
                    }
                } else {
                    
                    if (characterBounds.top < wallBounds.top) {
                        character.setPosition(character.getPosition().x, character.getPosition().y - overlap.height);
                    } else {
                        character.setPosition(character.getPosition().x, character.getPosition().y + overlap.height);
                    }
                }
            }
            
        }
         for (const Door& door : doors) {
            sf::FloatRect wallBounds = door.Wallbox.getGlobalBounds();
           
            
            if (characterBounds.intersects(wallBounds)) {
                sf::FloatRect overlap;
               
                characterBounds.intersects(wallBounds, overlap);

                if (overlap.width < overlap.height) {
                    if (characterBounds.left < wallBounds.left) {
                        character.setPosition(character.getPosition().x - overlap.width + 0.1f, character.getPosition().y);
                      
                        
                        
                        
                    } else {
                        character.setPosition(character.getPosition().x + overlap.width -0.1f, character.getPosition().y);
                        
                           
                    }
                } else {
                    
                    if (characterBounds.top < wallBounds.top) {
                        character.setPosition(character.getPosition().x, character.getPosition().y - overlap.height);
                    
                    } else {
                        character.setPosition(character.getPosition().x, character.getPosition().y + overlap.height);
                    }
                }
            }
        }
        for (const AI& door : ai) {
            sf::FloatRect wallBounds = door.body.getGlobalBounds();
           
            
            if (characterBounds.intersects(wallBounds)) {
                sf::FloatRect overlap;
               
                characterBounds.intersects(wallBounds, overlap);

                if (overlap.width < overlap.height) {
                    if (characterBounds.left < wallBounds.left) {
                        character.setPosition(character.getPosition().x - overlap.width + 0.1f, character.getPosition().y);
                      
                        
                        
                        
                    } else {
                        character.setPosition(character.getPosition().x + overlap.width -0.1f, character.getPosition().y);
                        
                           
                    }
                } else {
                    
                    if (characterBounds.top < wallBounds.top) {
                        character.setPosition(character.getPosition().x, character.getPosition().y - overlap.height);
                    
                    } else {
                        character.setPosition(character.getPosition().x, character.getPosition().y + overlap.height);
                    }
                }
            }
        }
    }
   
    
};
