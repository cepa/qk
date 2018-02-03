#include "engine.h"

int Engine::StartMenu()
{
  DrawMap();
  int iCloud = 0;
  for(iCloud = 0; iCloud < 3; iCloud++)
    Cloud[iCloud]->Draw();
  text_mode(-1);
  textout_centre(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"Qrczoks Killer",324,24,makecol(84,79,79));
  textout_centre(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"Qrczoks Killer",320,20,makecol(234,33,18));
  textout_centre(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"Start",324,204,makecol(84,79,79));
  textout_centre(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"Start",320,200,makecol(255,242,63));
  textout_centre(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"Help",324,244,makecol(84,79,79));
  textout_centre(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"Help",320,240,makecol(255,242,63));
  textout_centre(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"Quit",324,284,makecol(84,79,79));
  textout_centre(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"Quit",320,280,makecol(255,242,63));
  if(IsTextCentre("Start",(FONT *)datFonts[DAT_FONT0].dat,320,200))
  { 
    textout_centre(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"Start",320,200,makecol(16,13,219));
    if(mouse_b & 1)
    {
      play_sample((SAMPLE *)datSound[DAT_SND_DING].dat,255,127,1000,0); 
      Delay(500);
      job = JOB_GAME;
    }
  }
  if(IsTextCentre("Help",(FONT *)datFonts[DAT_FONT0].dat,320,240))
  {
    textout_centre(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"Help",320,240,makecol(16,13,219));
    if(mouse_b & 1)
    {
      play_sample((SAMPLE *)datSound[DAT_SND_DING].dat,255,127,1000,0); 
      Delay(500);
      job = JOB_HELP;
    }
  }
  if(IsTextCentre("Quit",(FONT *)datFonts[DAT_FONT0].dat,320,280))
  {
    textout_centre(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"Quit",320,280,makecol(16,13,219));
    if(mouse_b & 1)
    {
      play_sample((SAMPLE *)datSound[DAT_SND_DING].dat,255,127,1000,0); 
      Delay(500);
      job = JOB_QUIT;
    }
  }
  DrawMouse(DAT_GFX_CURSOR0);
  return ENGINE_CONTINUE;
}

int Engine::Quit()
{
  int ret = ENGINE_CONTINUE;
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
      ret = ENGINE_QUIT;
      Delay(500);
    }
  }
  if(IsTextLeft("No",(FONT *)datFonts[DAT_FONT0].dat,340,360))
  {
    textout(ScreenBuffer,(FONT *)datFonts[DAT_FONT0].dat,"No",340,360,makecol(16,13,219));
    if(mouse_b & 1)
    {
      play_sample((SAMPLE *)datSound[DAT_SND_DING].dat,255,127,1000,0); 
      job = JOB_START_MENU;
      Delay(500);
    }
  }
  DrawMouse(DAT_GFX_CURSOR0);
  return ret;
}

