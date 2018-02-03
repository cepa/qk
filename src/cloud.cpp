#include "engine.h"

Cloud::Cloud(int _speed,int _x,int _y)
  : speed(_speed),x(_x),y(_y),bm((BITMAP *)datGfx[DAT_GFX_CLOUD].dat)
{
}

Cloud::~Cloud()
{
}

void Cloud::Draw()
{
  masked_blit(bm,ScreenBuffer,0,0,x,y,bm->w,bm->h);
}

void Cloud::CalcPos()
{
  x -= speed;
  if(x < -bm->w)
    x = SCREEN_W;
}

