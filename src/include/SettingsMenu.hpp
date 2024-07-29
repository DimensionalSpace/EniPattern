#pragma once
#include "./GameScene.hpp"
#include <SFML/Graphics.hpp>
#include "./Scene.hpp"
#include "Button.hpp" 
#include "DataLoader.hpp"
using namespace sf;




class SettingsMenu : public Scene
{
private:

     Font font;
    Button Soundsettings = Button("Textures/SoftwareButtons.png",15,15, {-200, 0});
    Button DisplaySettings = Button("Textures/SoftwareButtons.png",15,15, {200, 0});
    Button backbutton = Button("Textures/SoftwareButtons.png",15,15, {-300, 300});
    View view;
     sf::Music music;
    DataLoader dl;
    SoundSettings ss;
public:
   
  
  void Code(sf::RenderWindow& window) override;
  void Update(sf::RenderWindow& window) override;
  void Render(sf::RenderWindow& window) override;
  void Events(sf::RenderWindow& window, sf::Event event) override{
          
            if (event.type == sf::Event::Closed)
                window.close();
        
  }
};

void SettingsMenu::Code(sf::RenderWindow& window){
    
    view.setSize(800, 600);
    backbutton.rect.setTextureRect({0,17, backbutton.width, backbutton.height});
    backbutton.Scale({3,3});
     Soundsettings.rect.setTextureRect({34,0, Soundsettings.width, Soundsettings.height});
    Soundsettings.Scale({3,3});
     DisplaySettings.rect.setTextureRect({34,34, DisplaySettings.width, DisplaySettings.height});
    DisplaySettings.Scale({3,3});
     dl.LoadSoundSettings("soundsettings",ss);
         music.openFromFile("Music/SettingsMenu.wav");
         music.setLoop(true);
        music.play();
}

void SettingsMenu::Update(sf::RenderWindow &window)
{

    music.setVolume(ss.musicvolume);
    view.setSize(Vector2f{window.getSize()});
     sf::Vector2i mousePos = sf::Mouse::getPosition(window);
      sf::Vector2f mousePosF = window.mapPixelToCoords(mousePos);
   if(backbutton.contains(mousePosF)){
            
            if(Mouse::isButtonPressed(Mouse::Left)){
                index = 0;
                music.stop();
                cs = true;
            }
            }
    if(Soundsettings.contains(mousePosF)){
            
            if(Mouse::isButtonPressed(Mouse::Left)){
                index = 2;
                music.stop();
                cs = true;
            }
            }
    if(DisplaySettings.contains(mousePosF)){
           
            if(Mouse::isButtonPressed(Mouse::Left)){
                index = 3;
                music.stop();
                cs = true;
            }
            }
        
}

void SettingsMenu::Render(sf::RenderWindow &window)
{
    window.clear(Color::White);
    Soundsettings.Draw(window);
    DisplaySettings.Draw(window);
    backbutton.Draw(window);
    window.setView(view);
    view.setCenter(0, 0);
    
}
