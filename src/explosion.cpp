#include "engine.h"

Explosion::Explosion(int _x,int _y)
  : x(_x),y(_y),frame_counter(0),done(false)
{
  sprite[0] = (BITMAP *)datGfx[DAT_GFX_EXPLOSION0].dat;
  sprite[1] = (BITMAP *)datGfx[DAT_GFX_EXPLOSION1].dat;
  sprite[2] = (BITMAP *)datGfx[DAT_GFX_EXPLOSION2].dat;
  sprite[3] = (BITMAP *)datGfx[DAT_GFX_EXPLOSION3].dat;
  sprite[4] = (BITMAP *)datGfx[DAT_GFX_EXPLOSION4].dat;
  sprite[5] = (BITMAP *)datGfx[DAT_GFX_EXPLOSION5].dat;
  sprite[6] = (BITMAP *)datGfx[DAT_GFX_EXPLOSION6].dat;
  sprite[7] = (BITMAP *)datGfx[DAT_GFX_EXPLOSION7].dat;
}

Explosion::~Explosion()
{
}

void Explosion::Draw()
{
  BITMAP *bm = sprite[frame_counter];
  masked_blit(bm,ScreenBuffer,0,0,x - bm->w / 2,y - bm->h / 2,bm->w,bm->h);
  frame_counter++;
  if(frame_counter > 7)
    done = true;
}

