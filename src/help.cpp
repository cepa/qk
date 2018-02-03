#include "engine.h"

int Engine::Help()
{
  DrawMap();
  int iCloud = 0;
  for(iCloud = 0; iCloud < 3; iCloud++)
    Cloud[iCloud]->Draw();
  text_mode(-1);
  textout_centre(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"Qrczoks Killer",324,24,makecol(84,79,79));
  textout_centre(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"Qrczoks Killer",320,20,makecol(234,33,18));
  textout_centre(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"Help",324,104,makecol(84,79,79));
  textout_centre(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"Help",320,100,makecol(255,242,63));
  textout(ScreenBuffer,(FONT *)datFonts[DAT_FONT1].dat,"Mission target:",40,160,makecol(242,36,36));
  textout(ScreenBuffer,(FONT *)datFonts[DAT_FONT1].dat,"You must kill qrczoks",40,180,makecol(255,255,255));
  textout(ScreenBuffer,(FONT *)datFonts[DAT_FONT1].dat,"in short time using your secret weapon - ",40,200,makecol(255,255,255));
  textout(ScreenBuffer,(FONT *)datFonts[DAT_FONT1].dat,"Super Mega Anty-Qrczoks Cannon - caliber 1000mm ! ;]",40,220,makecol(255,255,255));
  textout(ScreenBuffer,(FONT *)datFonts[DAT_FONT1].dat,"Your country need you, but how do it:",40,240,makecol(242,36,36));
  textout(ScreenBuffer,(FONT *)datFonts[DAT_FONT1].dat,"Cannon is directed by your mouse, and for shooting",40,260,makecol(255,255,255));
  textout(ScreenBuffer,(FONT *)datFonts[DAT_FONT1].dat,"use left mouse-button...",40,280,makecol(255,255,255));
  textout(ScreenBuffer,(FONT *)datFonts[DAT_FONT1].dat,"About:",40,300,makecol(242,36,36));
  textout(ScreenBuffer,(FONT *)datFonts[DAT_FONT1].dat,"Qrczaks Killer",40,320,makecol(255,255,255));
  textout(ScreenBuffer,(FONT *)datFonts[DAT_FONT1].dat,"By CEPA 2003   GNU GPL License",40,340,makecol(255,255,255));
  textout(ScreenBuffer,(FONT *)datFonts[DAT_FONT1].dat,"www.cepa.prv.pl",40,360,makecol(255,255,255));
  textout(ScreenBuffer,(FONT *)datFonts[DAT_FONT1].dat,"The game is based on ALLEGRO library !",40,380,makecol(255,255,255));
  BITMAP *bm = (BITMAP *)datGfx[DAT_GFX_MOUSE].dat;
  masked_blit(bm,ScreenBuffer,0,0,SCREEN_W - bm->w,SCREEN_H - bm->h - 20,bm->w,bm->h);
  textout_centre(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"Back",324,414,makecol(84,79,79));
  textout_centre(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"Back",320,410,makecol(255,242,63));
  if(IsTextCentre("Back",(FONT *)datFonts[DAT_FONT0].dat,320,410))
  {
    textout_centre(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"Back",320,410,makecol(16,13,219));
    if(mouse_b & 1)
    {
      play_sample((SAMPLE *)datSound[DAT_SND_DING].dat,255,127,1000,0); 
      job = JOB_START_MENU;
      Delay(500);
    }
  }
  DrawMouse(DAT_GFX_CURSOR0);
  return ENGINE_CONTINUE;
}
