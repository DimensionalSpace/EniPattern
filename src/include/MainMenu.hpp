#pragma once
#include "./GameScene.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "./Scene.hpp"
#include "Button.hpp"
#include "DataLoader.hpp"
using namespace sf;
class GameScene;
class MainMenu : public Scene
{
private:
    Text text;
     Font font;
    Button toGame = Button("Textures/StartButton.png", 69, 28, {-(69*3)/2, 0});
     Button toSettings = Button("Textures/SettingsButton.png", 68, 28, {-(69*3)/2, 90});
     Button Quit = Button("Textures/QuitButton.png", 68, 27, {-(69*3)/2, 180});
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

void MainMenu::Code(sf::RenderWindow& window){
    
    dl.LoadSoundSettings("soundsettings",ss);
         music.openFromFile("Music/Main Menu.wav");
        text.setString("EniPattern");
        Texture t;
        view.setSize(800, 600);
        toGame.Scale(Vector2f(3, 3));
        Quit.Scale(Vector2f(3, 3));
        toSettings.Scale(Vector2f(3, 3));
        text.setPosition(-150, -200);
        view.setSize(Vector2f{window.getSize()});
        font.loadFromFile("Fonts/Raleway.ttf");
        text.setScale(2, 2);
        text.setOutlineThickness(5);
        text.setOutlineColor(Color::Black);
        text.setFont(font);
        music.setLoop(true);
        music.play();
}

void MainMenu::Update(sf::RenderWindow &window)
{
     music.setVolume(ss.musicvolume);
   view.setSize(Vector2f{window.getSize()});
          sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosF = window.mapPixelToCoords(mousePos);
        if(toSettings.contains(mousePosF)){
          
           if(Mouse::isButtonPressed(Mouse::Left)){
                index = 1;
                music.stop();
                cs = true;
           }
        }
        
        if(toGame.contains(mousePosF)){
           if(Mouse::isButtonPressed(Mouse::Left)){
                index = 4;
                music.stop();
                cs = true;
           }
        }
        if(Quit.contains(mousePosF)){
             if(Mouse::isButtonPressed(Mouse::Left)){
                 window.close();
             }
          
        }
}

void MainMenu::Render(sf::RenderWindow &window)
{
      window.setVerticalSyncEnabled(true); 
            window.setFramerateLimit(144);
            window.clear(Color::Blue);
           
            window.draw(text);
            window.setView(view);
             view.setCenter(0, 0);
            toSettings.Draw(window);
            toGame.Draw(window);
            Quit.Draw(window);
}
