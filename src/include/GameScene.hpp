#pragma once
#include <SFML/Graphics.hpp>
#include "./Scene.hpp"
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
using namespace sf;
using namespace std;

class MainMenu;
class GameScene : public Scene
{
private:
     vector<Wall> walls;
        vector<Sprite> tilemap;

        
        GameData data;
        KeyboardSettings dataks;
        sf::View camera;
        sf::Clock clock;
        Selection sel;
        
        AI ai = AI("Textures/Char/2.png", {200,200},2.5f, 32, 32, {4,3}, 0.2f, 0);
        TilemapImporter tilemapImporter = TilemapImporter("./Levels/level1.json", "Textures/tilemap1.png", {64*32, 64*32}, {32, 32}, {256, 256});
        Goal g = Goal("Textures/1.png", {57, 1000}, 0);
        Door door = Door("Textures/3.png", false, {100, 4});
        vector<Door> doors = {door};
        PushButton p = PushButton("Textures/3.png", {678, 5}, true);
       vector<AI> ais = {ai};

       PushableItem pi = PushableItem("Textures/4.png", {100, 50});
       vector<PushableItem> pis = {pi};
        Teleporter tp = Teleporter("Textures/6.png", {630, 40}, {0,0});
public:
    Texture et;
    
    
    void Events(sf::RenderWindow& window, sf::Event event) override{
        
        if (event.type == sf::Event::Closed)
                window.close();
        if(event.type == sf::Event::Resized){
                 sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            camera = sf::View(visibleArea);
            window.setView(camera);
                
            }
          sel.Update(window, event);
    }
    void Render(sf::RenderWindow& window) override{
       
        
        window.clear(Color::Black);
        
       
        for(auto wall : walls){
            wall.drawTo(window);
        }
         for(auto tile : tilemap){
            window.draw(tile);
           
        }
        tp.Draw(window);
          p.Draw(window);
         for(auto& e : pis){
             e.Draw(window);
        }
         for(auto& a : ais){
            a.Draw(window);
         }
         
            door.drawTo(window);
         
      
        g.Draw(window);
      sel.Draw(window);
       
    };
    void Update(sf::RenderWindow& window) override{
        cout << door.Wallbox.getPosition().x << " " << door.Wallbox.getPosition().y << endl;
  
        float deltaTime = clock.restart().asSeconds();
        for(auto& e : pis){
             e.handleCollisions(walls, doors, ais);
        }
       
        
          tp.HandleCollisions(ais, pis);
         window.setView(camera);
         for(auto& er : ais){
            er.update(deltaTime, window);
         er.SetSelected(sel);
         er.handleWallCollisions(walls, doors);
         }
         
         p.HandleCollisions(ais, pis);
       
        ai.handleWallCollisions(walls, doors);
        g.HandleCollisions(ais);
        
        
        if(Keyboard::isKeyPressed(Keyboard::E)){
                index = 0;
                cs = true;
             
        }
    };
    void Code(sf::RenderWindow& window) override{
       
        Wall floor(Vector2f(200, 200), Color::White);
        Wall ceiling(Vector2f(200, 100), Color::White);
       
      
        

     
        
        
        //walls = tilemapImporter.TilemapWalls();
        //tilemap = tilemapImporter.tileMapSprites();
    camera.setSize(Vector2f(window.getSize()));
        camera.setCenter(window.getSize().x / 2, window.getSize().y / 2);
        
       
    //std::cout << walls.size() << endl;
    //std::cout << tilemap.size() << endl;   
        floor.setPos(Vector2f(20, 300));
        ceiling.setPos(Vector2f(20, 100));
        walls.push_back(ceiling);
        walls.push_back(floor);
     
    
    };
     
};


