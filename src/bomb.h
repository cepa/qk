#ifndef __BOMB_H__
  #define __BOMB_H__
  
  #include "vector.h"

class Bomb
{
  public:
    Bomb(int _x,int _y,double _angle);
    ~Bomb();
    void CalcPos();
    void Draw();
    ::Vector *Vector;
    bool done;
    BITMAP *bm,*sprite;
};

#endif 
