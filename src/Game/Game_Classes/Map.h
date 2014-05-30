#ifndef MAP_H
#define MAP_H
#include "../../Graphics/GObject.h"
#include "../../GEGraphicsCore.h"
#include "../../GEGlobal.h"
#include "vector"
#include "../../GERandom.h"
#include "../../GEInput.h"
#include "../../GEMouse.h"

//#define map[x][y] (*vet1)[x*(GE_GLOBAL_SCREEN_HEIGHT/GE_GLOBAL_TILESIZE) + y]

using namespace std;

class Map
{
private:
    bool editingMode;

    int size = GE_GLOBAL_TILESIZE;
    int FIELD_DIMENSION = (GE_GLOBAL_SCREEN_HEIGHT/size);
//    std::vector<int> *vet1;
    int map[GE_GLOBAL_SCREEN_HEIGHT/GE_GLOBAL_TILESIZE][GE_GLOBAL_SCREEN_HEIGHT/GE_GLOBAL_TILESIZE];
    int checkCellState(int x, int y, int state);
    int c_left(int x, int y);
    int c_right(int x, int y);
    int c_up(int x, int y);
    int c_down(int x, int y);
    void processInput();
public:
    Map();
    void Draw();
    void Update();
    int getMatrix(int x, int y);
    void setMatrix(int x,int y,int value);
};

#endif // MAP_H
