
#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "Coin.h"
#include <math.h>
#include "Wall.hpp"
#include "Animation.hpp"


using namespace sf;
using namespace std;

class Player {
private:
   
    int gravitySpeed = 6;
    float jumpTime = 3.f; 
    bool canJump = true;
    
   bool direction = true;
    float walkspeed;
    unsigned int setani = 0;
    bool faceRight = true;
    int switchTime = 0.2f;
    Texture t;
    Animation animation;
    Animation shootingpointanimation;
    Keyboard::Key keys[4];
    Texture t2;
    float angle;
    float shootradius;
    
public:
 sf::Sprite player;
 Sprite Shootingpoint;
 int health;
 

 public:
    
    Player(const string& filename, float speed,sf::Vector2u imageCount,float switchTime, int width, int height,sf::Vector2u spimageCount,float spswitchTime, int spwidth, int spheight, const string& spfilename, float shootingrange): 
    animation(imageCount, switchTime, width, height),
    shootingpointanimation(spimageCount, spswitchTime, spwidth, spheight){
        t.loadFromFile(filename);
        t2.loadFromFile(spfilename);
        player.setTexture(t);
        Shootingpoint.setTexture(t2);
        faceRight = true;
        this->walkspeed = speed;
        this->shootradius = shootingrange;
        player.setOrigin(width/2, height/2);
        health = 100;
         player.setOrigin(width/2, height/2);
        Shootingpoint.setOrigin(spwidth/2, spheight/2);
    }
     void Scale(Vector2f scale){
        player.setScale(scale);
    }
    void Update(float deltatime, RenderWindow& window){
         sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosF = window.mapPixelToCoords(mousePos);
        sf::Vector2f vectorToTarget = mousePosF - player.getPosition();
       sf::Vector2f movement(0,0);
       //takeDamage(10);
       if(Keyboard::isKeyPressed(keys[0])){
            movement.x -= walkspeed * deltatime;
            direction = false;
       }
            
       if(Keyboard::isKeyPressed(keys[1])){
            movement.x += walkspeed * deltatime;
            direction = true;
       }
            
        if(Keyboard::isKeyPressed(keys[2]))
            movement.y -= walkspeed * deltatime;
       if(Keyboard::isKeyPressed(keys[3]))
            movement.y += walkspeed * deltatime;
       
       if(movement.x == 0 && movement.y == 0){
         setani = 0;
       }
       else{
            setani = 1;
            if(direction)
                faceRight = true;
            else
                faceRight = false;
        
       }
        angle = atan2(player.getPosition().y -mousePosF.y, player.getPosition().x -mousePosF.x) * 180/3.141592;
            if(angle < 0){
                angle = atan2(player.getPosition().y -mousePosF.y, player.getPosition().x -mousePosF.x) * 180/3.141592 + 360;
            } else{
                angle = atan2(player.getPosition().y -mousePosF.y, player.getPosition().x -mousePosF.x) * 180/3.141592;
            }
        
            Shootingpoint.setRotation(angle);
        float shootingPointX = player.getPosition().x - shootradius * std::cos(angle * 3.141592 / 180.0f);
        float shootingPointY = player.getPosition().y - shootradius * std::sin(angle * 3.141592 / 180.0f);
            Shootingpoint.setPosition(shootingPointX, shootingPointY);
            cout << health << endl;
       animation.update(setani, deltatime, faceRight);
       player.setTextureRect(animation.uvRect);
       player.move(movement);
    }
    FloatRect GetGlobalBounds(){
         return player.getGlobalBounds();
       }
    
    void Draw(sf::RenderWindow &window) {
       
        window.draw(player);
        window.draw(Shootingpoint);
    }
    void takeDamage(int damage){
        health -= damage;
        
    }
    

    void setPosition(sf::Vector2f pos) {
        player.setPosition(pos);
        Shootingpoint.setPosition(player.getPosition() + sf::Vector2f(std::cos(angle) * shootradius, std::sin(angle) * shootradius));
    }

    bool isCollidingWithCoin(Coin *coin) {
        if (player.getGlobalBounds().intersects(coin->getglobalbounds())) {
            return true;
        }
        return false;
    }
    Vector2f GetPosition(){
        return player.getPosition();
    }
    void handleWallCollisions(const std::vector<Wall>& walls) {
         sf::FloatRect playerBounds = player.getGlobalBounds();
        for (const Wall& wall : walls) {
            sf::FloatRect wallBounds = wall.Wallbox.getGlobalBounds();
           
            
            if (playerBounds.intersects(wallBounds)) {
                sf::FloatRect overlap;
               
                playerBounds.intersects(wallBounds, overlap);

                if (overlap.width < overlap.height) {
                    if (playerBounds.left < wallBounds.left) {
                        player.setPosition(player.getPosition().x - overlap.width + 0.1f, player.getPosition().y);
                      
                        
                        
                        
                    } else {
                        player.setPosition(player.getPosition().x + overlap.width -0.1f, player.getPosition().y);
                        
                           
                    }
                } else {
                    
                    if (playerBounds.top < wallBounds.top) {
                        player.setPosition(player.getPosition().x, player.getPosition().y - overlap.height);
                        canJump = true;
                        jumpTime = 3.f; 
                    } else {
                        player.setPosition(player.getPosition().x, player.getPosition().y + overlap.height);
                    }
                }
            }
        }
       
        
       
    }
     
       
    void Keybinds(Keyboard::Key keyLeft, Keyboard::Key keyRight, Keyboard::Key keyUp, Keyboard::Key keyDown){
            keys[0] = keyLeft;
            keys[1] = keyRight;
            keys[2] = keyUp;
            keys[3] = keyDown;
    }
    
};


