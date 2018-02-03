#include "engine.h"

Cannon::Cannon()
  : x(0),y(0),angle(0)
{
  sprite = (BITMAP *)datGfx[DAT_GFX_GUN].dat;
  base = (BITMAP *)datGfx[DAT_GFX_GUN_BASE].dat;
  bm = create_bitmap(sprite->w,sprite->h);
  clear_to_color(bm,makecol(255,0,255));
}

Cannon::~Cannon()
{
  destroy_bitmap(bm);
}

void Cannon::Draw()
{
  rotate_sprite(bm,sprite,0,0,itofix((int)a360_to_a256((double)angle)));
  masked_blit(bm,ScreenBuffer,0,0,x,y,bm->w,bm->h);
  masked_blit(base,ScreenBuffer,0,0,x,y + bm->h - base->h,base->w,base->h);
  clear_to_color(bm,makecol(255,0,255));
}

