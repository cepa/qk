#ifndef __QRCZOKS_H__
  #define __QRCZOKS_H__

class Qrczok
{
  public:
    Qrczok(int _startx,int _starty,int _speed);
    ~Qrczok();
    void CalcPos();
    void Draw();
    bool Sighted(int mx,int my);
    int startx,starty,x,y,speed;
    BITMAP *sprite[10];
    int sprite_counter;
    int sprite_num;
    int sprite_frame;
    bool killed;
    bool shooted;
    bool winner;
};

#endif
