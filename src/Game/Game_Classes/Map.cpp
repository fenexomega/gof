#include "Map.h"

Map::Map()
{
    FIELD_DIMENSION = GE_GLOBAL_SCREEN_HEIGHT/size;
//    vet1 = new vector<int>(FIELD_DIMENSION*FIELD_DIMENSION,0);

    for (int x = 0; x < FIELD_DIMENSION; ++x)
    {
        for (int y = 0; y < FIELD_DIMENSION; ++y)
        {
            map[x][y] = GERandom::getInt(3);
        }
    }

    editingMode = false;


}   

void Map::Draw()
{

    for (int x = 0; x < FIELD_DIMENSION; ++x)
    {
        for (int y = 0; y < FIELD_DIMENSION; ++y)
        {
            if(map[x][y] == 1)
                GEGraphicsCore::DrawRectangle(x*size,y*size,size,size,GEColor::Blue());
            if(map[x][y] == 2)
                GEGraphicsCore::DrawRectangle(x*size,y*size,size,size,GEColor::getColor(0,150,255));
        }
    }
    if(editingMode)
        GEGraphicsCore::Grid(GEColor::getColor(100,100,100),size);
    else
        GEGraphicsCore::Grid(GEColor::getColor(0,0,0),size);
}

void Map::Update()
{
    processInput();
    int x,y;
    int aux[GE_GLOBAL_SCREEN_HEIGHT/GE_GLOBAL_TILESIZE][GE_GLOBAL_SCREEN_HEIGHT/GE_GLOBAL_TILESIZE];
    if(!editingMode)
    {
        for (int x = 0; x < FIELD_DIMENSION; ++x)
        {
            for (int y = 0; y < FIELD_DIMENSION; ++y)
            {
                aux[x][y] = checkCellState(x,y,map[(x)][y]);
            }
        }

        for (int x = 0; x < FIELD_DIMENSION; ++x)
        {
            for (int y = 0; y < FIELD_DIMENSION; ++y)
            {
                map[x][y] =  aux[x][y] ;
            }
        }
    }
    else
    {
        GEMouse::getMousePos(x,y);
        if(GEMouse::isButtonPressed(1))
            map[x/size][y/size] = 1;
        if(GEMouse::isButtonPressed(3))
            map[x/size][y/size] = 0;
    }


}

void Map::processInput()
{
    if(GEInput::isKeyPressed(GEInput::SPACE))
        editingMode = !editingMode;
}

int Map::checkCellState(int x, int y,int state)
{
    int counter = 0; //O contador inicia com -1 porque o código conta a vida da própria célula

    int l = this->c_left(x,y);
    int r = this->c_right(x,y);
    int u = this->c_up(x,y);
    int d = this->c_down(x,y);

    counter += map[l][y] ? 1 : 0;
    counter += map[r][y] ? 1 : 0;
    counter += map[x][u] ? 1 : 0;
    counter += map[x][d] ? 1 : 0;
    counter += map[l][u] ? 1 : 0;
    counter += map[l][d] ? 1 : 0;
    counter += map[r][u] ? 1 : 0;
    counter += map[r][d] ? 1 : 0;


    if(state == 0)
    {
        if(counter == 3)
            return 2;
        return 0;
    }
    else
    {
       if(counter == 2 || counter == 3)
            return 1;
       return 0;

    }

}

int Map::c_left(int x, int y)
{
    if( x <= 0 )
        return FIELD_DIMENSION-1;
    return x-1;
}

int Map::c_right(int x, int y)
{
    if( x >= (FIELD_DIMENSION-1) )
        return 0;
    return x+1;
}

int Map::c_up(int x, int y)
{
    if( y <= 0 )
        return FIELD_DIMENSION-1;
    return y-1;
}

int Map::c_down(int x, int y)
{
    if( y >= (FIELD_DIMENSION-1) )
        return 0;
    return y+1;
}

int Map::getMatrix(int x, int y)
{
    return map[x][y];
}

void Map::setMatrix(int x,int y,int value)
{
    map[x][y] = value;
}
