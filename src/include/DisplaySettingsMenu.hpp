#pragma once
#include "./GameScene.hpp"
#include <SFML/Graphics.hpp>
#include "./Scene.hpp"
#include "Button.hpp"
#include "DataLoader.hpp"
using namespace sf;

class DisplaySettingsMenu : public Scene
{
private:
    DisplaySettings settings;
    Button fullscreen = Button("Textures/SoftwareButtons.png",15,15, {260, 0});
    DataLoader dl;
    View view;
    Button decantiali = Button("Textures/SoftwareButtons.png",15,15, {170, 100});
    Button incantiali = Button("Textures/SoftwareButtons.png",15,15,{260, 100});
     Button backbutton = Button("Textures/SoftwareButtons.png",15,15, {-270, 300});
    Text aatext;
    Text text;
    Text text2;
    Font font;
    sf::Music music;
    SoundSettings ss;
public:
   
  
 void Code(sf::RenderWindow& window) override;
  void Update(sf::RenderWindow& window) override;
  void Render(sf::RenderWindow& window) override;
  void Events(sf::RenderWindow& window, sf::Event event) override;
        
};

void DisplaySettingsMenu::Code(sf::RenderWindow& window){
    
    dl.LoadDisplaySettings("displaysettings",settings);
  backbutton.rect.setTextureRect({0,17, backbutton.width, backbutton.height});
    backbutton.Scale({3,3});
    fullscreen.Scale({3,3});
     incantiali.rect.setTextureRect({0,0, incantiali.width, incantiali.height});
  decantiali.rect.setTextureRect({17,0, decantiali.width, decantiali.height});
  incantiali.Scale({3,3});
  decantiali.Scale({3,3});

   font.loadFromFile("Fonts/Raleway.ttf");
        aatext.setOutlineThickness(5);
        aatext.setOutlineColor(Color::Black);
        aatext.setFont(font);
        aatext.setPosition({320, 100});
    text.setString("Anti-Aliasing Level");
     text.setPosition({-230, 100});
        view.setSize(Vector2f{window.getSize()});
      
        
        text.setOutlineThickness(5);
        text.setOutlineColor(Color::Black);
        text.setFont(font); 
       text2.setString("Fullscreen/Windowed");
     text2.setPosition({-230, 0});
        
      
        
        text2.setOutlineThickness(5);
        text2.setOutlineColor(Color::Black);
        text2.setFont(font); 
        
         dl.LoadSoundSettings("soundsettings",ss);
         music.openFromFile("Music/SettingsMenu.wav");
         music.setLoop(true);
        music.play();
}

void DisplaySettingsMenu::Update(sf::RenderWindow &window)
{
  
    music.setVolume(ss.musicvolume);
  if(settings.settings.antialiasingLevel > 100)
      settings.settings.antialiasingLevel = 100;
  if(settings.settings.antialiasingLevel < 1)
       settings.settings.antialiasingLevel = 1;
  aatext.setString(to_string(settings.settings.antialiasingLevel));
  sf::Vector2i mousePos = sf::Mouse::getPosition(window);
      sf::Vector2f mousePosF = window.mapPixelToCoords(mousePos);
       view.setSize(Vector2f{window.getSize()});
   if(fullscreen.contains(mousePosF)){
      
      if(Mouse::isButtonPressed(Mouse::Left)){
          settings.isFullscreen = !settings.isFullscreen;
          dl.SaveDisplaySettings("displaysettings",settings);
          if(settings.isFullscreen){
            fullscreen.rect.setTextureRect({17,34, fullscreen.width, fullscreen.height}); 
            window.create(sf::VideoMode(), "My window",  sf::Style::Fullscreen| sf::Style::Titlebar | sf::Style::Close, settings.settings);
            
          }else{
            fullscreen.rect.setTextureRect({0,34, fullscreen.width, fullscreen.height}); 
            window.create(sf::VideoMode(1200, 900), "My window",  sf::Style::Default| sf::Style::Titlebar | sf::Style::Close, settings.settings);
         
          }
            
      }
      if(settings.isFullscreen){
            fullscreen.rect.setTextureRect({17,34, fullscreen.width, fullscreen.height}); 
            
            
          }else{
            fullscreen.rect.setTextureRect({0,34, fullscreen.width, fullscreen.height}); 
          
         
          }
    }
    if(backbutton.contains(mousePosF)){
            
            if(Mouse::isButtonPressed(Mouse::Left)){
                dl.SaveDisplaySettings("displaysettings",settings);
                index = 1;
                music.stop();
                cs = true;
            }
            }
}
        

void DisplaySettingsMenu::Render(sf::RenderWindow &window)
{
  window.clear(Color::White);
  fullscreen.Draw(window);
  backbutton.Draw(window);
  decantiali.Draw(window);
  incantiali.Draw(window);
  window.draw(aatext);
  window.draw(text);
  window.draw(text2);
  window.setView(view);
  view.setCenter(0, 0);
}
void DisplaySettingsMenu::Events(sf::RenderWindow &window, Event event)
{
  if (event.type == sf::Event::Closed)
                window.close();
  bool lock_click = false;
 
     
       sf::Vector2i mousePos = sf::Mouse::getPosition(window);
      sf::Vector2f mousePosF = window.mapPixelToCoords(mousePos);
         if(incantiali.contains(mousePosF)){
            
      if (event.mouseButton.button == sf::Mouse::Left && lock_click != true){
        settings.settings.antialiasingLevel += 1;
        dl.SaveDisplaySettings("displaysettings",settings);
        lock_click = true;
      }}
     if(decantiali.contains(mousePosF)){
        
       if (event.mouseButton.button == sf::Mouse::Left && lock_click != true)
        settings.settings.antialiasingLevel -= 1;
        dl.SaveDisplaySettings("displaysettings",settings);
        lock_click = true;
       
      }
    
    
         
        
  

  if (event.type == sf::Event::MouseButtonReleased) {
      if (event.mouseButton.button == sf::Mouse::Left) 
      {
          lock_click = false; 
      }        
    }
}