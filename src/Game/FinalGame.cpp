/*
 * FinalGame.cpp
 *
 *  Created on: 24/02/2014
 *      Author: jordy
 */

#include "FinalGame.h"




FinalGame::FinalGame()
{
    ifstream file;
    file.open("map.txt");
    map = new Map();
    string line;
    if(file != NULL)
    {
        GE_LOG("Lendo mapa");
        for (int x = 0; x < GE_GLOBAL_SCREEN_HEIGHT/GE_GLOBAL_TILESIZE; ++x)
        {
            getline(file,line);
            for (int y = 0; y < GE_GLOBAL_SCREEN_HEIGHT/GE_GLOBAL_TILESIZE; ++y)
            {
                map->setMatrix(x,y,line[y] - '0');
            }
        }
    }
    file.close();

}


void FinalGame::gameUpdate(long currentTime)
{


    if(GEInput::isKeyDown(GEInput::LEFT))
        fps = GE_MAX((fps - 1),1);
    if(GEInput::isKeyDown(GEInput::RIGHT))
        fps++;
    timeMedia += deltaTime;


    if(timeMedia >= 1000/fps)
    {
        map->Update();
        timeMedia = 0;
    }
}

void FinalGame::gameDraw()
{
    map->Draw();
    
}

void FinalGame::gameDispose()
{
    ofstream file;
    file.open("map.txt");
    for (int x = 0; x < GE_GLOBAL_SCREEN_HEIGHT/GE_GLOBAL_TILESIZE; ++x)
    {
        for (int y = 0; y < GE_GLOBAL_SCREEN_HEIGHT/GE_GLOBAL_TILESIZE; ++y)
        {
            file << (map->getMatrix(x,y) > 0 ? 1 : 0);
        }
        file << endl;
    }
    delete map;
}

FinalGame::~FinalGame()
{
    
}

