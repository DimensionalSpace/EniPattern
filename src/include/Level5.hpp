#pragma once
#include "TilemapImporter.hpp"
#include "Goal.hpp"
#include "PushableItem.hpp"
#include "Teleporter.hpp"
#include "Selection.hpp"
#include "AI.hpp"
#include "DataLoader.hpp"
#include "SettingsMenu.hpp"
#include "Door.hpp"
#include "StepButton.hpp"
#include "Button.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;
class GameScene;
class Level5: public Scene
{
private:
GameData gamedata;
DataLoader dl;
    TilemapImporter tmpimp = TilemapImporter("./Levels/level5.json", "Textures/tilemap1.png", {64*32, 64*32}, {32, 32}, {256, 256});
    AI ai = AI( {27*32,9*32},2.5f, 32, 32, {4,3}, 0.2f, 6);
    
    vector<AI> ais;
    vector<Wall> walls;
    vector<Sprite> bottom;
    Goal g = Goal( {24*32, 23*32}, 6); 
    
    vector<Goal> goals = {g};
    Door door = Door("Textures/slidedoor1.png", true, {24*32, 21*32});
    
    vector<Door> doors = {door};
    
     
     PushButton p2 = PushButton("Textures/PushButton.png", {11*32, 7*32}, true);
   
  
     Teleporter tp = Teleporter("Textures/teleporter.png", {21*32, 9*32}, {6*32,7*32});
    Teleporter tp2 = Teleporter("Textures/teleporter.png", {8*32, 12*32}, {7*32,18*32});
    Teleporter tp3 = Teleporter("Textures/teleporter.png", {10*32, 19*32}, {25*32,18*32});
     PushableItem item2 = PushableItem("Textures/Vase.png", {23*32, 9*32}); 
    vector<PushableItem> items = { item2};
    sf::Clock clock;
    vector<Sprite>  top;
    Selection sel;
    Button backbutton = Button("Textures/SoftwareButtons.png",15,15, {40, 850});
//    Button nextlevel = Button("Textures/SoftwareButtons.png",15,15, {640, 850});
    sf::View camera;
    SoundSettings ss;
    Music music;
public:
   
  
 void Code(sf::RenderWindow& window) override;
  void Update(sf::RenderWindow& window) override;
  void Render(sf::RenderWindow& window) override;
  void Events(sf::RenderWindow& window, sf::Event event) override{
         if (event.type == sf::Event::Closed)
                window.close();
        if(event.type == sf::Event::Resized){
                 sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
         //   camera = sf::View(visibleArea);
              camera.setSize(Vector2f(window.getSize()));
    camera.setCenter(window.getSize().x / 2, window.getSize().y / 2); 
            window.setView(camera);
                
        }
        sel.Update(window, event);
    }
};

void Level5::Code(sf::RenderWindow& window){
    bottom = tmpimp.tileMapSprites();
    top = tmpimp.TopLayer();
    walls = tmpimp.TilemapWalls();
    ai.settexture();
    ais = {ai};
    for(auto& a : ais){
      a.body.setScale(3,3);
    }
      camera.setSize(Vector2f(window.getSize()));
    camera.setCenter(window.getSize().x / 2, window.getSize().y / 2);  
    backbutton.rect.setTextureRect({0,17, backbutton.width, backbutton.height});
    backbutton.Scale({3,3}); 
  // nextlevel.rect.setTextureRect({17,17, nextlevel.width, nextlevel.height});
    //nextlevel.Scale({3,3}); 
         dl.LoadSoundSettings("soundsettings",ss);
         music.openFromFile("Music/Game.wav");
         music.setLoop(true);
        music.play();
}

void Level5::Update(sf::RenderWindow &window)
{
  music.setVolume(ss.musicvolume);
   sf::Vector2i mousePos = sf::Mouse::getPosition(window);
      sf::Vector2f mousePosF = window.mapPixelToCoords(mousePos);
  float deltaTime = clock.restart().asSeconds();
  for(auto& er : ais){
            er.update(deltaTime, window);
         er.SetSelected(sel);
         er.handleWallCollisions(walls, doors);
         }
    for (Goal& goal : goals)
    {
      goal.HandleCollisions(ais);
      
    }
    if(g.finishedpattern){
          gamedata.l5 = true;
          dl.SaveGameData(1, gamedata);
         
       
      
      }
    
       doors[0].update(p2.pressed, 22*32,24*32);
      
      
      
     items[0].handleCollisions(walls, doors, ais);
      
    p2.HandleCollisions(ais, items);
     
        
        
     tp.HandleCollisions(ais, items);
     tp2.HandleCollisions(ais, items);
      tp3.HandleCollisions(ais, items);   
  
    
    if(backbutton.contains(mousePosF)){
          
            if(Mouse::isButtonPressed(Mouse::Left)){
                
                index = 4;
                music.stop();
                cs = true;
            }
            }
    //if(nextlevel.contains(mousePosF)){
          
   //         if(Mouse::isButtonPressed(Mouse::Left)){
                
    //            index += 1;
     //           music.stop();
     //           cs = true;
     //       }
      //      }
}

void Level5::Render(sf::RenderWindow &window)
{
   window.setView(camera);
   for (Sprite bott : bottom){
      window.draw(bott);
    }
    for (Goal& goal : goals)
    {
      goal.Draw(window);
      
    }
     
       
      p2.Draw(window);
     tp.Draw(window);
      tp2.Draw(window);
      tp3.Draw(window);
    for(auto& it : items){
      it.character.setScale({2, 2});
      it.Draw(window);
    }
    for(auto& a : ais){
            a.Draw(window);
         }
    
    for(auto& d : doors){   d.drawTo(window);}
   
    
      
    
  
    for(auto& tile : top){
            window.draw(tile);
           
        }
    for(auto wall : walls){
            wall.drawTo(window);
        }
        backbutton.Draw(window);
   
   
     sel.Draw(window);
      for (Goal& goal : goals){
    if(goal.finishedpattern){
      
      }}
     
}
