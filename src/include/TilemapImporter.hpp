#pragma once
#include <SFML/Graphics.hpp>
#include "json.hpp"
#include "Wall.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <math.h>
#include <ctime>
#include "AI.hpp"
#include "Door.hpp"
#include "Goal.hpp"
using json = nlohmann::json;
using namespace sf;
using namespace std;
class TilemapImporter
{
private:
    int y = 0;
    int x = 0;
    json level;
    array<Texture, 128> maptextures;
public:
    TilemapImporter(const string& filename, const string& textureFile);
    ~TilemapImporter();
    
    vector<Sprite> tileMapSprites(){
        vector<Sprite> tilemap;
        int posx = 0;
        int posy = 0;
        for(const auto& element : level["layers"][0]["data"]){
            int value = element.get<int>();
        
            if(posx == 2048){
                    posx = 0;
                    posy += 32;
                
            }
            if(value == 0){
                posx += 32;
            }
            if(value != 0){
                Sprite tile;
           
                tile.setTexture(maptextures[value - 1]);
            
                tile.setPosition(Vector2f(posx, posy));
            
                tilemap.push_back(tile);
                posx += 32;  
            }
        }
        return tilemap;
    }
    vector<Wall> TilemapWalls(){
        vector<Wall> walls;
        for(const auto& element : level["layers"][1]["objects"]){

            Wall wall(Vector2f(element["width"], element["height"]), Color::Transparent);
            wall.setPos(Vector2f(element["x"], element["y"]));
            walls.push_back(wall);
        }
        return walls;
    };
    vector<Sprite> TopLayer(){
       vector<Sprite> tilemap;
        int posx = 0;
        int posy = 0;
        for(const auto& element : level["layers"][2]["data"]){
            int value = element.get<int>();
        
            if(posx == 2048){
                    posx = 0;
                    posy += 32;
                
            }
            if(value == 0){
                posx += 32;
            }
            if(value != 0){
                Sprite tile;
           
                tile.setTexture(maptextures[value - 1]);
            
                tile.setPosition(Vector2f(posx, posy));
            
                tilemap.push_back(tile);
                posx += 32;  
                cout << tile.getPosition().x<<" "<< tile.getPosition().y;
            }
        }
        return tilemap;
    }
   

    

};

TilemapImporter::TilemapImporter(const string& filename, const string& textureFile)
{
    ifstream f(filename);
    level = json::parse(f);
    for(int i = 0; i < maptextures.size(); i++){
         
       maptextures[i].loadFromFile(textureFile, IntRect(x,y,32,32));
        x += 32;
        if(x==256){
            x=0;
            y+=32;
        }
        
    }
}

TilemapImporter::~TilemapImporter()
{
}
