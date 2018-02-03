#include "engine.h"

int Engine::Game()
{
  int iQrczok = 0;
  int iExplosion = 0;    

  if(MakeSetup)
  {
    MakeSetup = false;
    for(iQrczok = 0; iQrczok < 30; iQrczok++)
      if(Qrczok[iQrczok]) 
      {
        delete Qrczok[iQrczok];
        Qrczok[iQrczok] = NULL;
      }
    for(iExplosion = 0; iExplosion < 30; iExplosion++)
      if(Explosion[iExplosion])
      {
        delete Explosion[iExplosion];
        Explosion[iExplosion] = NULL;
      }  
    QrczoksSpeed = 1;
    Points = 0;
    iQrczokDelay = 0;  
    Level = 0;
    Dead = 0;
    clear_to_color(BloodBuffer,makecol(255,0,255));
  }
 
  QrczoksSpeed = Level + 1;

  Level = (int)(Dead / 50);

  DrawMap();
  DrawBloodBuffer();
  
  int iCloud = 0;
  for(iCloud = 0; iCloud < 3; iCloud++)
    Cloud[iCloud]->Draw();
//calculate angle 
  double MouseAngle = 0;
  int MouseAngleDelta = 270;
  if(mouse_x > SCREEN_W / 2)
    MouseAngleDelta += 180;
  double CannonCenterY = (double)Cannon->y + (double)Cannon->bm->h / 2;   
  double CannonCenterX = (double)Cannon->x + (double)Cannon->bm->w / 2;   
  double Tan = ((double)mouse_y + 7 - CannonCenterY) / ((double)mouse_x - CannonCenterX);
  if(Tan == 90) Tan = 89.9;
  else if(Tan == 270) Tan = 269.9;
  MouseAngle = atan(Tan) + a360_to_rad(MouseAngleDelta);
//
  Cannon->x = SCREEN_W / 2 - Cannon->bm->w / 2;
  Cannon->y = SCREEN_H - 10 - Cannon->bm->h;
  Cannon->angle = rad_to_a360(MouseAngle);

  for(iQrczok = 0; iQrczok < 30; iQrczok++)
  {
    if(DelayTimerTick)
      iQrczokDelay++;
    if(iQrczokDelay > 200)
    {
      iQrczokDelay = 0;
      if(!Qrczok[iQrczok])
      {
        Qrczok[iQrczok] = new ::Qrczok((rand() % SCREEN_W) - 20,-76,QrczoksSpeed);
      }
    }  
  }

  if(mouse_b & 1)
  {
    if(!Bomb)
    {
      Bomb = new ::Bomb(CannonCenterX,CannonCenterY,MouseAngle);
      play_sample((SAMPLE *)datSound[DAT_SND_CANNON].dat,255,127,1000,0);
    }
  }
 
  if(SecondTimerTick)
  {
    for(iQrczok = 0; iQrczok < 30; iQrczok++)
    {
      if(Qrczok[iQrczok])
      {
        Qrczok[iQrczok]->CalcPos();
      }
    }
    SecondTimerTick = false;
  }

  for(iQrczok = 0; iQrczok < 30; iQrczok++)
  {
    if(Qrczok[iQrczok])
    {
      Qrczok[iQrczok]->Sighted(mouse_x,mouse_y);
      if(Bomb)
      {
        if(IsCollision(Bomb->Vector->x2,Bomb->Vector->y2,Bomb->bm->w,Bomb->bm->h,
          Qrczok[iQrczok]->x,Qrczok[iQrczok]->y,45,30))
        {
          Qrczok[iQrczok]->shooted = true;
          Qrczok[iQrczok]->CalcPos();
          Points += 5;
          play_sample((SAMPLE *)datSound[DAT_SND_HEN].dat,255,127,1000,0);
          play_sample((SAMPLE *)datSound[DAT_SND_SCREAM].dat,255,127,1000,0);
        }
        else if(IsCollision(Bomb->Vector->x2,Bomb->Vector->y2,Bomb->bm->w,Bomb->bm->h,
          Qrczok[iQrczok]->x,Qrczok[iQrczok]->y + 45,31,30))
        {
          Qrczok[iQrczok]->killed = true;
          Qrczok[iQrczok]->CalcPos();
          Points++;
          for(iExplosion = 0; iExplosion < 30; iExplosion++)
          {
            if(!Explosion[iExplosion])
            {
              Explosion[iExplosion] = new ::Explosion(Qrczok[iQrczok]->x + 23,Qrczok[iQrczok]->y + 38);
            }
          }
          play_sample((SAMPLE *)datSound[DAT_SND_EXPLOSION].dat,255,127,1000,0);
          //delete Bomb;
          //Bomb = NULL;
        }
      }  
      Qrczok[iQrczok]->Draw();
      if(Qrczok[iQrczok]->winner)
      {
        play_sample((SAMPLE *)datSound[DAT_SND_EXPLOSION].dat,255,127,1000,0);
        play_sample((SAMPLE *)datSound[DAT_SND_ROOSTER].dat,255,127,1000,0);
        job = JOB_GAME_OVER;
      }  
      if(Qrczok[iQrczok]->killed)
      {
        DrawBlood(Qrczok[iQrczok]->x,Qrczok[iQrczok]->y);
        delete Qrczok[iQrczok];
        Qrczok[iQrczok] = NULL;
        Dead++;
      }
    }
  }
  
  if(DelayTimerTick)
  {    
    for(iExplosion = 0; iExplosion < 30; iExplosion++)
    {
      if(Explosion[iExplosion])
      {
        Explosion[iExplosion]->Draw();
        if(Explosion[iExplosion]->done)
        {
          delete Explosion[iExplosion];
          Explosion[iExplosion] = NULL;
        }  
      }
    }
  }

  if(Bomb)
  {
    if(Bomb->done)
    {
      delete Bomb;
      Bomb = NULL;
    }
    else
    {
      if(DelayTimerTick)
      {
        Bomb->CalcPos();
        Bomb->Draw();
        //DelayTimerTick = false;
      }  
    }
  }

  Cannon->Draw();
  textprintf(ScreenBuffer,(FONT *)datFonts[DAT_FONT1].dat,10,10,makecol(229,27,27),"Level: %d  ",Level);
  textprintf_right(ScreenBuffer,(FONT *)datFonts[DAT_FONT1].dat,630,10,makecol(229,27,27),"Points: %d  ",Points);
  textprintf_right(ScreenBuffer,(FONT *)datFonts[DAT_FONT1].dat,630,30,makecol(229,27,27),"Dead: %d  ",Dead);
  DrawMouse(DAT_GFX_CURSOR1,7,0);
  if(key[KEY_ESC])
  {
    MakeSetup = true;
    job = JOB_PAUSE;
  }  
  return ENGINE_CONTINUE;
}

bool Engine::IsCollision(int x1,int y1,int w1,int h1,int x2,int y2,int w2,int h2)
{
  bool ret = false;
  if((x2 > x1) && (x2 < x1 + w1) && (y2 > y1) && (y2 < y1 + h1)) ret = true;
  if((x2 + w1 > x1) && (x2 + w1 < x1 + w1) && (y2 > y1) && (y2 < y1 + h1)) ret = true;
  if((x2 > x1) && (x2 < x1 + w1) && (y2 + h1 > y1) && (y2 + h1 < y1 + h1)) ret = true;
  if((x2 + w1 > x1) && (x2 + w1 < x1 + w1) && (y2 + h1 > y1) && (y2 + h1 < y1 + h1)) ret = true;
  return ret;
}

int Engine::GameOver()
{
  DrawMap();
  textout_centre(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"Qrczoks Killer",324,24,makecol(84,79,79));
  textout_centre(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"Qrczoks Killer",320,20,makecol(234,33,18));
  textout_centre(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"Game Over",324,204,makecol(84,79,79));
  textout_centre(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"Game Over",320,200,makecol(255,242,63));
  textprintf(ScreenBuffer,(FONT *)datFonts[DAT_FONT1].dat,10,10,makecol(229,27,27),"Level: %d  ",Level);
  textprintf_right(ScreenBuffer,(FONT *)datFonts[DAT_FONT1].dat,630,10,makecol(229,27,27),"Points: %d  ",Points);
  textprintf_right(ScreenBuffer,(FONT *)datFonts[DAT_FONT1].dat,630,30,makecol(229,27,27),"Dead: %d  ",Dead);
  textout_centre(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"Back To Menu",324,284,makecol(84,79,79));
  textout_centre(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"Back To Menu",320,280,makecol(255,242,63));
  if(IsTextCentre("Back To Menu",(FONT *)datFonts[DAT_FONT0].dat,320,280))
  {
    textout_centre(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"Back To Menu",320,280,makecol(16,13,219));
    if(mouse_b & 1)
    {
      play_sample((SAMPLE *)datSound[DAT_SND_DING].dat,255,127,1000,0); 
      Delay(500);
      MakeSetup = true;
      job = JOB_START_MENU;
    }
  }
  DrawMouse(DAT_GFX_CURSOR0);
  return ENGINE_CONTINUE;
}

int Engine::GamePause()
{
  DrawMap();
  int iCloud = 0;
  for(iCloud = 0; iCloud < 3; iCloud++)
    Cloud[iCloud]->Draw();
  text_mode(-1);
  textout_centre(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"Qrczoks Killer",324,24,makecol(84,79,79));
  textout_centre(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"Qrczoks Killer",320,20,makecol(234,33,18));
  textout_centre(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"Really quit ???",324,324,makecol(84,79,79));
  textout_centre(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"Really quit ???",320,320,makecol(255,242,63));
  textout_right(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"Yes",304,364,makecol(84,79,79));
  textout_right(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"Yes",300,360,makecol(255,242,63));
  textout(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"No",344,364,makecol(84,79,79));
  textout(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"No",340,360,makecol(255,242,63));
  if(IsTextRight("Yes",(FONT *)datFonts[DAT_FONT0].dat,300,360))
  {
    textout_right(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"Yes",300,360,makecol(16,13,219));
    if(mouse_b & 1)
    {
      play_sample((SAMPLE *)datSound[DAT_SND_DING].dat,255,127,1000,0);
      MakeSetup = true;
      job = JOB_START_MENU;
      Delay(500);
    }
  }
  if(IsTextLeft("No",(FONT *)datFonts[DAT_FONT0].dat,340,360))
  {
    textout(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"No",340,360,makecol(16,13,219));
    if(mouse_b & 1)
    {
      play_sample((SAMPLE *)datSound[DAT_SND_DING].dat,255,127,1000,0); 
      MakeSetup = false;
      job = JOB_GAME;
      Delay(500);
    }
  }
  DrawMouse(DAT_GFX_CURSOR0);
  return ENGINE_CONTINUE;
}


