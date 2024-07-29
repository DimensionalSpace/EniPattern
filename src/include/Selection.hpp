#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Selection
{
private:
    sf::Vector2i starting_position;
    sf::RectangleShape box;
    sf::Vector2i current_position;
    bool view = false;
public:
    void Update(RenderWindow& window, Event event);
    void Draw(RenderWindow& window){
        if(view)
            window.draw(box);
    };
    sf::FloatRect getglobalbounds(){
        return box.getGlobalBounds();
    }
};
void Selection::Update(RenderWindow& window, Event event){
       if( event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left )
            {
                starting_position.x = event.mouseButton.x;
                starting_position.y = event.mouseButton.y;
            }

            if( event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                current_position.x = event.mouseMove.x - starting_position.x;
                current_position.y = event.mouseMove.y - starting_position.y;
                box.setSize( Vector2f{current_position} );
                box.setPosition( starting_position.x , starting_position.y );
                box.setFillColor(sf::Color::Transparent);
                box.setOutlineThickness(1.f);
                box.setOutlineColor(sf::Color::Blue);
                view = true;
            }
            else{
                current_position = Mouse::getPosition();
                view = false;
            }
               
            
    
}


