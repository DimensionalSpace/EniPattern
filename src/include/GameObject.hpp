#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
class GameObject
{
private:
protected:
    Sprite sprite;    
public:

    GameObject(/* args */);
    void HandleCollisions(){
        
    }
    ~GameObject();
};

GameObject::GameObject(/* args */)
{
}

GameObject::~GameObject()
{
}
