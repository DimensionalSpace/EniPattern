#pragma once

#include <SFML/Graphics.hpp>

class Animation
{
private:
    //variables
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;

    float totalTime;
    float switchTime;

    //functions


public:
    //variables
    sf::IntRect uvRect;

    //constructor && destructor
    Animation(sf::Vector2u imageCount, float switchTime, int width, int height);
    virtual ~Animation();

    void update(int row, float deltaTime, bool faceRight);

};

Animation::Animation(sf::Vector2u imageCount, float switchTime, int width, int height)
{
    this->imageCount = imageCount;
    this->switchTime = switchTime;

    totalTime = 0.0f;
    currentImage.x = 0.0f;

    uvRect.width = width;
    uvRect.height = height;
    
}

Animation::~Animation()
{

}

void Animation::update(int row, float deltaTime, bool faceRight)
{
    currentImage.y = row;
    totalTime += deltaTime;

    if(totalTime >= switchTime)
    {
        totalTime -= switchTime;
        currentImage.x++;

        if(currentImage.x >= imageCount.x)
        {
            currentImage.x = 0;
        }
    }

    
    uvRect.top = currentImage.y * uvRect.height;
    if(faceRight){
        uvRect.left = currentImage.x * uvRect.width;
        uvRect.width = abs(uvRect.width);
    }else{
        uvRect.left = (currentImage.x +1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }
}
