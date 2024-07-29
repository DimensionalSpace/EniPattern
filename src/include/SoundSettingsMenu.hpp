#pragma once
#include "./GameScene.hpp"
#include <SFML/Graphics.hpp>
#include "./Scene.hpp"
#include "Button.hpp"
#include "DataLoader.hpp"
using namespace sf;

class SoundSettingsMenu : public Scene
{
private:
    SoundSettings settings;
  Text text;
    DataLoader dl;
    View view;
    Button decmusic = Button("Textures/SoftwareButtons.png",14,15,{170, 0});
    Button incmusic = Button("Textures/SoftwareButtons.png",14,15, {260, 0});
     Button backbutton = Button("Textures/SoftwareButtons.png",15,15, {-270, 300});
    Text aatext;

    Font font;
    sf::Music music;
    
public:
   
  
 void Code(sf::RenderWindow& window) override;
  void Update(sf::RenderWindow& window) override;
  void Render(sf::RenderWindow& window) override;
  void Events(sf::RenderWindow& window, sf::Event event) override;
        
};

void SoundSettingsMenu::Code(sf::RenderWindow& window){
    
    
  view.setSize(800, 600);
  backbutton.rect.setTextureRect({0,17, backbutton.width, backbutton.height});
  incmusic.rect.setTextureRect({0,0, backbutton.width, backbutton.height});
  decmusic.rect.setTextureRect({17,0, backbutton.width, backbutton.height});
    backbutton.Scale({3,3});
    incmusic.Scale({3,3});
    decmusic.Scale({3,3});
  
  dl.LoadSoundSettings("soundsettings",settings);
    font.loadFromFile("Fonts/Raleway.ttf");
        aatext.setOutlineThickness(5);
        aatext.setOutlineColor(Color::Black);
        aatext.setFont(font);
        aatext.setPosition({320, 0});
    text.setString("Volume");
     text.setPosition({-230, 0});
        view.setSize(Vector2f{window.getSize()});
      
        
        text.setOutlineThickness(5);
        text.setOutlineColor(Color::Black);
        text.setFont(font); 
         dl.LoadSoundSettings("soundsettings",settings);
         music.openFromFile("Music/SettingsMenu.wav");
         music.setLoop(true);
        music.play();
}

void SoundSettingsMenu::Update(sf::RenderWindow &window)
{
  
    music.setVolume(settings.musicvolume);
  if(settings.musicvolume > 100)
      settings.musicvolume = 100;
  if(settings.musicvolume < 1)
       settings.musicvolume = 1;
  aatext.setString(to_string(settings.musicvolume));
  sf::Vector2i mousePos = sf::Mouse::getPosition(window);
      sf::Vector2f mousePosF = window.mapPixelToCoords(mousePos);
       view.setSize(Vector2f{window.getSize()});
  
    if(backbutton.contains(mousePosF)){
         
            if(Mouse::isButtonPressed(Mouse::Left)){
                dl.SaveSoundSettings("soundsettings",settings);
                index = 1;
                music.stop();
                cs = true;
            }
            }
}
        

void SoundSettingsMenu::Render(sf::RenderWindow &window)
{
  window.clear(Color::White);
  backbutton.Draw(window);
  decmusic.Draw(window);
  incmusic.Draw(window);
  window.draw(aatext);
  window.setView(view);
  view.setCenter(0, 0);
  window.draw(text);
}
void SoundSettingsMenu::Events(sf::RenderWindow &window, Event event)
{
  if (event.type == sf::Event::Closed)
                window.close();
  bool lock_click = false;
 
     
       sf::Vector2i mousePos = sf::Mouse::getPosition(window);
      sf::Vector2f mousePosF = window.mapPixelToCoords(mousePos);
         if(incmusic.contains(mousePosF)){
            
      if (event.mouseButton.button == sf::Mouse::Left && lock_click != true){
        settings.musicvolume += 1;
        dl.SaveSoundSettings("soundsettings",settings);
        lock_click = true;
      }}
     if(decmusic.contains(mousePosF)){
            
       if (event.mouseButton.button == sf::Mouse::Left && lock_click != true)
        settings.musicvolume -= 1;
        dl.SaveSoundSettings("soundsettings",settings);
        lock_click = true;
       
      }
    
    
         
        
  

  if (event.type == sf::Event::MouseButtonReleased) {
      if (event.mouseButton.button == sf::Mouse::Left) 
      {
          lock_click = false; 
      }        
    }
}