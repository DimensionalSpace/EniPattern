#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <math.h>
#include <ctime>
#include "include/json.hpp"
#include "include/TilemapImporter.hpp"
#include "include/GameScene.hpp"
#include "include/MainMenu.hpp"
#include "include/SettingsMenu.hpp"
#include "include/SoundSettingsMenu.hpp"
#include "include/DisplaySettingsMenu.hpp"
#include "include/Level1.hpp"
#include "include/LevelSelection.hpp"
#include "include/Level2.hpp"
#include "include/Level3.hpp"
#include "include/Level4.hpp"
#include "include/Level5.hpp"
using json = nlohmann::json;
using namespace std;
using namespace sf;



   
int main()
{
    
    DisplaySettings ds;
    DataLoader dataloader;
    dataloader.LoadDisplaySettings("displaysettings",ds);
    vector<Scene*> scenes = {new MainMenu(),new SettingsMenu(),new SoundSettingsMenu(),new DisplaySettingsMenu(),new LevelSelection(),new Level1(), new Level2(), new Level3() ,new Level4(), new Level5()};
    Scene *scene = scenes[scene->index];
    
    
    sf::RenderWindow window;
    if(ds.isFullscreen){
        window.create(sf::VideoMode(), "My window",  sf::Style::Fullscreen | sf::Style::Titlebar | sf::Style::Close, ds.settings);
    }
    else{
        window.create(sf::VideoMode(1200, 900), "My window",  sf::Style::Default|sf::Style::Titlebar | sf::Style::Close, ds.settings);
    }
   
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    scene->Code(window);
    Clock clock;
    
    while (window.isOpen())
    {
      
    
        scene = scenes[scene->index];
        for (Event event = Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if(scene->cs == true){
                
                
                
                
                scene->Code(window);
                scene->cs = false;
            }
            scene->Events(window,event);
        }
        scene->Update(window);
        
        window.clear();
        scene->Render(window);
        
        
        window.display();
    
    }
    
    
    
    
    return 0;
}
