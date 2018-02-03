#include "engine.h"

Bomb::Bomb(int _x,int _y,double _angle)
  : done(false)
{
  sprite = (BITMAP *)datGfx[DAT_GFX_BOMB].dat;
  bm = create_bitmap(sprite->w,sprite->h);
  clear_to_color(bm,makecol(255,0,255));
  Vector = new ::Vector((double)_x,(double)_y,_angle - a360_to_rad(90),10.0);
}

Bomb::~Bomb()
{
  delete Vector;
  destroy_bitmap(bm);
}
 
void Bomb::CalcPos()
{
  Vector->x1 = Vector->x2;
  Vector->y1 = Vector->y2;
  Vector->Calc();
  if((Vector->x2 < 0) || (Vector->x2 > SCREEN_W) ||
    (Vector->y2 < 0) || (Vector->y2 > SCREEN_H))
    done = true;
}

void Bomb::Draw()
{
  rotate_sprite(bm,sprite,0,0,itofix((int)rad_to_a256(Vector->angle + a360_to_rad(90))));
  masked_blit(bm,ScreenBuffer,0,0,(int)Vector->x2 - bm->w / 2,(int)Vector->y2 - bm->h / 2,bm->w,bm->h);
  clear_to_color(bm,makecol(255,0,255));
}

