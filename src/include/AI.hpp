#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include <math.h>
#include "Selection.hpp"
#include "Animation.hpp"
#include "Door.hpp"
using namespace sf;
class AI
{
private:
    
    
    
    float movementSpeed;
    bool mouseDown = false;
    bool Selected = false;
    Animation animation;
    unsigned int setani = 2;
    Texture t;
    
    
public:
    
    std::optional<sf::Vector2f> target;
    int patterntype;
    sf::Sprite body;
    bool view = true;
    AI(Vector2f position, float movementspeed, int width, int height,sf::Vector2u imageCount,float switchTime, int pattern):
    animation(imageCount, switchTime, 10, 17){
        body.setPosition(position);
        movementSpeed = movementspeed;
        patterntype = pattern;
       
      
    };
    void settexture(){
         
        t.loadFromFile("Textures/Char/" + to_string(patterntype) + ".png");
        body.setTexture(t);
    }
    void update(float deltatime,sf::RenderWindow& window);
    void SetSelected(Selection sel){
        if(body.getGlobalBounds().intersects(sel.getglobalbounds()))
            Selected = true;
        if(Selected && Mouse::isButtonPressed(Mouse::Left)){
            Selected = false;
        }
    };
  
    void Draw(sf::RenderWindow& window){
        if(view){
            window.draw(body);
        }
       
    };
    void handleWallCollisions(const std::vector<Wall>& walls, const std::vector<Door>& doors);
    FloatRect getGlobalBounds(){
        return body.getGlobalBounds();
    };
};


void AI::update(float deltatime, RenderWindow& window)
{
   

    if(Selected){
        if (Mouse::isButtonPressed(Mouse::Right) && !mouseDown) {
            mouseDown = true;
            target = Vector2f(Mouse::getPosition(window));
        }

        if (!Mouse::isButtonPressed(Mouse::Right)) {
            mouseDown = false;
        }

    // Movement
        if (target)
        {
            sf::Vector2f vectorToTarget = *target - body.getPosition();
            float distanceToTarget = sqrt(vectorToTarget.x * vectorToTarget.x + vectorToTarget.y * vectorToTarget.y);
            if (distanceToTarget < movementSpeed) {
                body.move(vectorToTarget);
                target = {}; // clear target
            } else {
                sf::Vector2f movementDirection = vectorToTarget / distanceToTarget;
                body.move(movementDirection * movementSpeed);
            }
            if( abs(vectorToTarget.x) < vectorToTarget.y ){
                setani = 1;
            }else{
                setani = 0;
            }
        }else
            setani = 2;
    }
    animation.update(setani,deltatime, true);
    body.setTextureRect(animation.uvRect);
    
}
void AI::handleWallCollisions(const std::vector<Wall>& walls, const std::vector<Door>& doors) {
         sf::FloatRect bodyBounds = body.getGlobalBounds();
        for (const Wall& wall : walls) {
            sf::FloatRect wallBounds = wall.Wallbox.getGlobalBounds();
           
            
            if (bodyBounds.intersects(wallBounds)) {
                sf::FloatRect overlap;
               
                bodyBounds.intersects(wallBounds, overlap);

                if (overlap.width < overlap.height) {
                    if (bodyBounds.left < wallBounds.left) {
                        body.setPosition(body.getPosition().x - overlap.width + 0.1f, body.getPosition().y);
                      
                        
                        
                        
                    } else {
                        body.setPosition(body.getPosition().x + overlap.width -0.1f, body.getPosition().y);
                        
                           
                    }
                } else {
                    
                    if (bodyBounds.top < wallBounds.top) {
                        body.setPosition(body.getPosition().x, body.getPosition().y - overlap.height);
                    
                    } else {
                        body.setPosition(body.getPosition().x, body.getPosition().y + overlap.height);
                    }
                }
            }
        }
       
        for (const Door& door : doors) {
            sf::FloatRect wallBounds = door.Wallbox.getGlobalBounds();
           
            
            if (bodyBounds.intersects(wallBounds)) {
                sf::FloatRect overlap;
               
                bodyBounds.intersects(wallBounds, overlap);

                if (overlap.width < overlap.height) {
                    if (bodyBounds.left < wallBounds.left) {
                        body.setPosition(body.getPosition().x - overlap.width + 0.1f, body.getPosition().y);
                      
                        
                        
                        
                    } else {
                        body.setPosition(body.getPosition().x + overlap.width -0.1f, body.getPosition().y);
                        
                           
                    }
                } else {
                    
                    if (bodyBounds.top < wallBounds.top) {
                        body.setPosition(body.getPosition().x, body.getPosition().y - overlap.height);
                    
                    } else {
                        body.setPosition(body.getPosition().x, body.getPosition().y + overlap.height);
                    }
                }
            }
        }
       
    }
