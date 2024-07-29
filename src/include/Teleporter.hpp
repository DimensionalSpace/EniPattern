#pragma once
#include <SFML/Graphics.hpp>
#include "AI.hpp"
#include "PushableItem.hpp"
using namespace sf;
using namespace std;


class Teleporter
{
private:
    Sprite body;
    Vector2f travelpos;
    Texture tex;
    
public:
    
    Teleporter(const string& filename, Vector2f position, Vector2f travelposition);
    ~Teleporter();
    void Draw(RenderWindow& window){
        window.draw(body);
    }
    void HandleCollisions(vector<AI>& ai, vector<PushableItem>& pis);
};

Teleporter::Teleporter(const string& filename, Vector2f position, Vector2f travelposition)
{
    tex.loadFromFile(filename);
    body.setPosition(position);
    body.setTexture(tex);
    travelpos = travelposition;
    
}

Teleporter::~Teleporter()
{
}

void Teleporter::HandleCollisions(vector<AI>& ai, vector<PushableItem>& pis)
{
    sf::FloatRect bodyBounds = body.getGlobalBounds();

    // Handle collision with AI
    for (AI& a : ai) {
        FloatRect abounds = a.body.getGlobalBounds();
        if (bodyBounds.intersects(abounds)) {
            a.body.setPosition(travelpos);
            a.target = {}; // Reset target, if applicable
        }
    }

    // Handle collision with PushableItem
    for (PushableItem& item : pis) {
        FloatRect itemBounds = item.bounds;
        if (bodyBounds.intersects(itemBounds)) {
            item.character.setPosition(travelpos);
            
        }
      
      
    }
}