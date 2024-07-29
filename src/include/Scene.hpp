#pragma once
#include <SFML/Graphics.hpp>

class Scene
{
private:
    /* data */
public:
    
    virtual void Code(sf::RenderWindow& window) = 0;
    virtual void Update(sf::RenderWindow& window) = 0;
    virtual void Events(sf::RenderWindow& window, sf::Event event) = 0;
    virtual void Render(sf::RenderWindow& window) = 0;
    static int index;
    static bool cs;
};

int Scene::index = 0;
bool Scene::cs = false;