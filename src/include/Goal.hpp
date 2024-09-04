#pragma once
#include <SFML/Graphics.hpp>
#include "AI.hpp"
using namespace sf;
using namespace std;


class Goal
{
private:
    Sprite body;
    int patterntype;
    Texture tex;
    
public:
bool finishedpattern = false;
    Goal( Vector2f position, int pattern);
    ~Goal();
    void Draw(RenderWindow& window){
        window.draw(body);
    }
    void SetTexture(){
        tex.loadFromFile("Textures/Goal.png");
        body.setTexture(tex);
    }
    void HandleCollisions( std::vector<AI>& ai);
};

Goal::Goal( Vector2f position, int pattern)
{
    
    body.setPosition(position);
    
    patterntype = pattern;
     body.setTextureRect({0,0,32,32});
}

Goal::~Goal()
{
}

void Goal::HandleCollisions(std::vector<AI>& ai)
{
     sf::FloatRect bodyBounds = body.getGlobalBounds();
        for ( AI& a : ai) {
            FloatRect abounds = a.body.getGlobalBounds();
            if(bodyBounds.intersects(abounds) && patterntype == a.patterntype){
                finishedpattern = true;
                a.view = false;
                body.setTextureRect({0, patterntype*32, 32, 32});
                cout << finishedpattern << endl;
            }
        }
 }
