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
    Goal(const string& filename, Vector2f position, int pattern);
    ~Goal();
    void Draw(RenderWindow& window){
        window.draw(body);
    }
    void HandleCollisions( std::vector<AI>& ai);
};

Goal::Goal(const string& filename, Vector2f position, int pattern)
{
    tex.loadFromFile(filename);
    body.setPosition(position);
    body.setTexture(tex);
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
