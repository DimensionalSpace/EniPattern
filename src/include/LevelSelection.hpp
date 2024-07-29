#pragma once
#include "./GameScene.hpp"
#include <SFML/Graphics.hpp>
#include "./Scene.hpp"
#include "Button.hpp"
#include "DataLoader.hpp"
using namespace sf;

class LevelSelection : public Scene
{
private:
    Button l1 = Button("Textures/levels.png", 64, 64, {150, 100});
    Button l2 = Button("Textures/levels.png", 64, 64, {250, 100});
     Button l3 = Button("Textures/levels.png", 64, 64, {350, 100});
     Button l4 = Button("Textures/levels.png", 64, 64, {450, 100});
     Button l5 = Button("Textures/levels.png", 64, 64, {550, 100});
     Button backbutton = Button("Textures/SoftwareButtons.png",15,15, {40, 800});
    sf::View camera;
    sf::Music music;
    DataLoader dl;
    GameData gd;
    SoundSettings ss;
public:
   
  
 void Code(sf::RenderWindow& window) override;
  void Update(sf::RenderWindow& window) override;
  void Render(sf::RenderWindow& window) override;
  void Events(sf::RenderWindow& window, sf::Event event) override{
           if(event.type == sf::Event::Resized){
                 sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
         //   camera = sf::View(visibleArea);
              camera.setSize(Vector2f(window.getSize()));
    camera.setCenter(window.getSize().x / 2, window.getSize().y / 2); 
            window.setView(camera);
                
        }
            
    }
};

void LevelSelection::Code(sf::RenderWindow& window){
    l2.rect.setTextureRect({64, 0 , 64, 64});
    l3.rect.setTextureRect({128, 0 , 64, 64});
      l4.rect.setTextureRect({192, 0 , 64, 64});
      l5.rect.setTextureRect({256, 0 , 64, 64});
    camera.setSize(Vector2f(window.getSize()));
    camera.setCenter(window.getSize().x / 2, window.getSize().y / 2);
      dl.LoadSoundSettings("soundsettings",ss);
          dl.LoadGameData(1,gd);
         music.openFromFile("Music/Game.wav");
         music.setLoop(true);
        music.play();
        backbutton.rect.setTextureRect({0,17, backbutton.width, backbutton.height});
    backbutton.Scale({3,3});
}
       
      
        


void LevelSelection::Update(sf::RenderWindow &window)
{
       sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosF = window.mapPixelToCoords(mousePos);
   if(l1.contains(mousePosF)){
            
            if(Mouse::isButtonPressed(Mouse::Left)){
                index = 5;
                music.stop();
                cs = true;
            }
            }
    if(l2.contains(mousePosF)){
            
            if(Mouse::isButtonPressed(Mouse::Left)){
                index = 6;
                music.stop();
                cs = true;
            }
            }
     if(l3.contains(mousePosF)){
            
            if(Mouse::isButtonPressed(Mouse::Left)){
                index = 7;
                music.stop();
                cs = true;
            }
            }
     if(l4.contains(mousePosF)){
            
            if(Mouse::isButtonPressed(Mouse::Left)){
                index = 8;
                music.stop();
                cs = true;
            }
            }
     if(l5.contains(mousePosF)){
            
            if(Mouse::isButtonPressed(Mouse::Left)){
                index = 9;
                music.stop();
                cs = true;
            }
            }
    if(backbutton.contains(mousePosF)){
            
            if(Mouse::isButtonPressed(Mouse::Left)){
                index = 0;
                music.stop();
                cs = true;
            }
            }
}

void LevelSelection::Render(sf::RenderWindow &window)
{
  window.setView(camera);
  window.clear(Color::White);
     l1.Draw(window);
     l2.Draw(window);
     l3.Draw(window);
     l4.Draw(window);
     l5.Draw(window);
     backbutton.Draw(window);
}
