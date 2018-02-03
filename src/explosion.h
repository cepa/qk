#ifndef __EXPLOSION_H__
  #define __EXPLOSION_H__
  
class Explosion
{
  public:
    Explosion(int x,int y);
    ~Explosion();
    void Draw();
    BITMAP *sprite[8];
    int frame_counter;
    bool done;
    int x,y;
};  
  
#endif
