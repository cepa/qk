#ifndef __CLOUD_H__
  #define __CLOUD_H__
  
class Cloud
{
  public:
    Cloud(int _speed,int _x,int _y);
    ~Cloud();
    void Draw();
    void CalcPos();
    int speed,y,x;
    BITMAP *bm;
};
  
#endif
