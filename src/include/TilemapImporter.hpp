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
    Vector2i Tilesize, Tilemapsize;
    array<Texture, 128> maptextures;
public:
    TilemapImporter(const string& filename, const string& textureFile, Vector2i tilemapsize, Vector2i tilesize, Vector2i texturedim);
    ~TilemapImporter();
    
    vector<Sprite> tileMapSprites(){
        vector<Sprite> tilemap;
        int posx = 0;
        int posy = 0;
        for(const auto& element : level["layers"][0]["data"]){
            int value = element.get<int>();
        
            if(posx == Tilemapsize.x){
                    posx = 0;
                    posy += Tilesize.y;
                
            }
            if(value == 0){
                posx += Tilesize.x;
            }
            if(value != 0){
                Sprite tile;
           
                tile.setTexture(maptextures[value - 1]);
            
                tile.setPosition(Vector2f(posx, posy));
            
                tilemap.push_back(tile);
                posx += Tilesize.x;  
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
        
            if(posx == Tilemapsize.x){
                    posx = 0;
                    posy += Tilesize.y;
                
            }
            if(value == 0){
                posx += Tilesize.x;
            }
            if(value != 0){
                Sprite tile;
           
                tile.setTexture(maptextures[value - 1]);
            
                tile.setPosition(Vector2f(posx, posy));
            
                tilemap.push_back(tile);
                posx += Tilesize.x;  
               
            }
        }
        return tilemap;
    }
     vector<AI> AIs(){
        vector<AI> tilemap;
        int posx = 0;
        int posy = 0;
        for(const auto& element : level["layers"][3]["data"]){
            int value = element.get<int>();
        
            if(posx == Tilemapsize.x){
                    posx = 0;
                    posy += Tilesize.y;
                
            }
            if(value == 0){
                posx += Tilesize.x;
            }
            if(value != 0){
                int num = value - 10;
                string dir = "Textures/Char/" + to_string(num) + ".png";
                AI ai = AI(dir, {posx,posy},2.5f, 32, 32, {4,3}, 0.2f, num);
                ai.body.setScale(3,3);
                
            
                tilemap.push_back(ai);
                posx += Tilesize.x;  
            }
        }
        return tilemap;
    }

    

};

TilemapImporter::TilemapImporter(const string& filename, const string& textureFile, Vector2i tilemapsize, Vector2i tilesize, Vector2i texturedim)
{
    Tilemapsize = tilemapsize;
    Tilesize = tilesize;
    
    ifstream f(filename);
    level = json::parse(f);
    for(int i = 0; i < maptextures.size(); i++){
         
       maptextures[i].loadFromFile(textureFile, IntRect(x,y,tilesize.x,tilesize.y));
        x += tilesize.x;
        if(x==texturedim.x){
            x=0;
            y+=tilesize.y;
        }
        
    }
}

TilemapImporter::~TilemapImporter()
{
}
