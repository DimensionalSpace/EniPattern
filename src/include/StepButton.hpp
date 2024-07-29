#pragma once
#include <SFML/Graphics.hpp>
#include "AI.hpp"
#include "PushableItem.hpp"
using namespace sf;
using namespace std;


class PushButton
{
private:
    Sprite body;
    bool pushonce;
    Texture tex;
    
public:
    bool pressed = false;
    PushButton(const string& filename, Vector2f position, bool pushoncebutton);
    ~PushButton();
    void Draw(RenderWindow& window){
        window.draw(body);
    }
    void HandleCollisions( const std::vector<AI>& ai, const std::vector<PushableItem>& pis);
};

PushButton::PushButton(const string& filename, Vector2f position, bool pushoncebutton)
{
    tex.loadFromFile(filename);
    body.setPosition(position);
    body.setTexture(tex);
    pushonce = pushoncebutton;
    body.setTextureRect({0,0,32,32});
}

PushButton::~PushButton()
{
}

void PushButton::HandleCollisions(const std::vector<AI>& ai, const std::vector<PushableItem>& pis) {
   if(pressed){
    body.setTextureRect({0,32,32,32});
   }else{
    body.setTextureRect({0,0,32,32});
   }
    sf::FloatRect bodyBounds = body.getGlobalBounds();
    for (const AI& a : ai) {
        FloatRect abounds = a.body.getGlobalBounds();
        if (bodyBounds.intersects(abounds)) {
            pressed = true;
            
            
        }else{
            if(!pushonce)
                pressed = false;
        }
    }
     for (const PushableItem& item : pis) {
        FloatRect abounds = item.character.getGlobalBounds();
        if (bodyBounds.intersects(abounds)) {
            pressed = true;
            
            
        }else{
            if(!pushonce)
                pressed = false;
        }
    }

     // Reset to false if no AI intersects
}
