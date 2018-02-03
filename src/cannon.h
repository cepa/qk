#ifndef __CANNON_H__
  #define __CANNON_H__

  #include "vector.h"

class Cannon
{
  public:
    Cannon();
    ~Cannon();
    void Draw();
    int x,y,angle;
    BITMAP *bm;
    BITMAP *sprite;
    BITMAP *base;
};

#endif
