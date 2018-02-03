#include "engine.h"

Qrczok::Qrczok(int _startx,int _starty,int _speed)
  : startx(_startx),starty(_starty),x(_startx),y(_starty),speed(_speed),sprite_counter(0),
    sprite_num(0),sprite_frame(0),killed(false),shooted(false),winner(false)
{
  sprite[0] = (BITMAP *)datGfx[DAT_GFX_QRCZAK00].dat;
  sprite[1] = (BITMAP *)datGfx[DAT_GFX_QRCZAK01].dat;
  sprite[2] = (BITMAP *)datGfx[DAT_GFX_QRCZAK10].dat;
  sprite[3] = (BITMAP *)datGfx[DAT_GFX_QRCZAK11].dat;
  sprite[4] = (BITMAP *)datGfx[DAT_GFX_QRCZAK20].dat;
  sprite[5] = (BITMAP *)datGfx[DAT_GFX_QRCZAK21].dat;
  sprite[6] = (BITMAP *)datGfx[DAT_GFX_QRCZAK30L].dat;
  sprite[7] = (BITMAP *)datGfx[DAT_GFX_QRCZAK31L].dat;
  sprite[8] = (BITMAP *)datGfx[DAT_GFX_QRCZAK30R].dat;
  sprite[9] = (BITMAP *)datGfx[DAT_GFX_QRCZAK31R].dat;
}

Qrczok::~Qrczok()
{
}

void Qrczok::CalcPos()
{
  if(shooted)
  {
    speed = 15;
    sprite_num = 4;
  }
  x += (rand() % 4) - 2;
  y += speed;
  int frame_delta = 0;
  if(x > SCREEN_W / 2 - 22)
    frame_delta = 2;
  if(y > SCREEN_H - 86)
  {
    if(shooted)
      killed = true;
    if(!killed)
    {     
      if(frame_delta == 0)
      {
        x += 2;
        sprite_num = 8;
      }  
      else
      { 
        x -= 2;
        sprite_num = 6;
      }    
      y = SCREEN_H - 85;
      if((x > SCREEN_W / 2 - 22 - 45) && (x < SCREEN_W / 2 + 22))
      {
        winner = true;
        killed = true;
      }  
    }
  }    
}

void Qrczok::Draw()
{
  sprite_counter++;
  if(sprite_counter > 20)
  {
    sprite_frame++;
    sprite_counter = 0;
  }  
  if(sprite_frame > 1)
    sprite_frame = 0;
  BITMAP *bm = sprite[sprite_num + sprite_frame];   
  masked_blit(bm,ScreenBuffer,0,0,x,y,bm->w,bm->h);  
}

bool Qrczok::Sighted(int mx,int my)
{
  bool ret = false;
  if(y < SCREEN_H - 86)
  {
    if(!shooted)
    {
      if((mx > x) && (mx < x + 45) && (my > y) && (my < y + 76))
      {
        sprite_num = 2;
        ret = true;
      } 
      else
      {
        sprite_num = 0;
      }
    }   
  }
  return ret;
}


