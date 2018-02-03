#include "engine.h"

int Engine::Work()
{
  int ret = ENGINE_CONTINUE;
  switch(job)
  {
    case JOB_START_MENU: ret = StartMenu(); break;
    case JOB_GAME: ret = Game(); break; 
    case JOB_HELP: ret = Help(); break;
    case JOB_QUIT: ret = Quit(); break; 
    case JOB_GAME_OVER: ret = GameOver(); break; 
    case JOB_PAUSE: ret = GamePause(); break;
  }
  return ret;
}

Engine::Engine(int _argc,char **_argv)
  : argc(_argc),argv(_argv),job(JOB_START_MENU),StartMenuSetup(true)
{
  try
  {
    AllegroInit();
    StartGfx();
    LoadData();
  }
  catch(MouseInitError)
  {
    set_gfx_mode(GFX_TEXT,0,0,0,0);
    allegro_message("Mouse init error !\n");
    throw Error();
  }
  catch(KeyboardInitError)
  {
    set_gfx_mode(GFX_TEXT,0,0,0,0);
    allegro_message("Keyboard init error !\n");
    throw Error();
  }
  catch(TimerInitError)
  {
    set_gfx_mode(GFX_TEXT,0,0,0,0);
    allegro_message("Timer init error !\n");
    throw Error();
  }
  catch(SoundInitError)
  {
    set_gfx_mode(GFX_TEXT,0,0,0,0);
    allegro_message("Sound init error !\n");
    throw Error();
  }  
  catch(FileNotFound theException)
  {
    set_gfx_mode(GFX_TEXT,0,0,0,0);
    allegro_message("File %s doesn't exist !\n",theException.FileName());
    throw Error();
  }
  catch(DataFileLoadingError theException)
  {
    set_gfx_mode(GFX_TEXT,0,0,0,0);
    allegro_message("Can't load %s data file !\n",theException.FileName());
    throw Error();
  }
  catch(GfxSettingError)
  {
    set_gfx_mode(GFX_TEXT,0,0,0,0);
    allegro_message("Requested video mode isn't supported on your video card !\n");
    throw Error();
  }
  catch(ScreenBufferCreatingError)
  {
    set_gfx_mode(GFX_TEXT,0,0,0,0);
    allegro_message("Can't create 640x480 16bit screen buffer !\n");
    throw Error();
  }
  catch(NullCursorCreatingError)
  {
    set_gfx_mode(GFX_TEXT,0,0,0,0);
    allegro_message("Can't create a NULL cursor !\n");
    throw Error();
  }
  catch(BloodBufferCreatingError)
  {
    set_gfx_mode(GFX_TEXT,0,0,0,0);
    allegro_message("Can't create blood buffer !\n");
    throw Error();
  }
}

Engine::~Engine()
{
  ShutdownGfx();
  RemoveData();
  AllegroExit();
}

bool Engine::AllegroInit()
{
  allegro_init();
  if(install_mouse() == -1)
  {
    throw MouseInitError();
    return false;
  }
  if(install_keyboard() != 0)
  {
    throw KeyboardInitError();
    return false;
  }
  if(install_timer() != 0)
  {
    throw TimerInitError();
    return false;
  }
  if(install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,argv[0]) != 0)
  {
    throw SoundInitError();
    return false;
  } 
  return true;
}

void Engine::AllegroExit()
{
  remove_sound();
  remove_keyboard();
  remove_timer();
  remove_mouse();
  allegro_exit();
}

bool Engine::LoadData()
{
  if(!exists("data/gfx.dat"))
  {
    throw FileNotFound("data/gfx.dat");
    return false;
  }
  datGfx = load_datafile("data/gfx.dat");
  if(!datGfx)
  {
    throw DataFileLoadingError("data/gfx.dat");
    return false;
  }
  if(!exists("data/fonts.dat"))
  {
    throw FileNotFound("data/fonts.dat");
    return false;
  }
  datFonts = load_datafile("data/fonts.dat");
  if(!datFonts)
  {
    throw DataFileLoadingError("data/fonts.dat");
    return false;
  }
  if(!exists("data/sound.dat"))
  {
    throw FileNotFound("data/sound.dat");
    return false;
  }
  datSound = load_datafile("data/sound.dat");
  if(!datSound)
  {
    throw DataFileLoadingError("data/sound.dat");
    return false;
  }
  return true;
}

void Engine::RemoveData()
{
  unload_datafile(datSound);
  unload_datafile(datFonts);
  unload_datafile(datGfx);
}

bool Engine::StartGfx()
{
  set_color_depth(16);
  if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,640,480,0,0) != 0)
  {
    throw GfxSettingError();
    return false;
  }
  set_window_title("Qrczoks Killer");
  if(!(ScreenBuffer = create_bitmap(SCREEN_W,SCREEN_H)))
  {
    throw ScreenBufferCreatingError();
    return false;
  }
  clear_to_color(ScreenBuffer,makecol(255,255,255));
  if(!(nullcursor = create_bitmap(1,1)))
  {
    throw NullCursorCreatingError();
    return false;
  }
  clear_to_color(nullcursor,makecol(255,0,255));
  if(!(BloodBuffer = create_bitmap(SCREEN_W,80)))
  {
    throw BloodBufferCreatingError();
    return false;
  }
  clear_to_color(BloodBuffer,makecol(255,0,255));
  set_mouse_speed(0,0);
  set_mouse_sprite(nullcursor);
  set_mouse_sprite_focus(0,0);
  show_mouse(screen);
  UpdateScreen();
  LOCK_VARIABLE(DelayTimerTick);
  LOCK_FUNCTION(DelayTimer);
  install_int(DelayTimer,1);
  LOCK_VARIABLE(SecondTimerTick);
  LOCK_FUNCTION(SecondTimer);
  install_int(SecondTimer,100);
  return true;
}

void Engine::ShutdownGfx()
{
  remove_int(SecondTimer);
  remove_int(DelayTimer);
  clear_to_color(screen,makecol(0,0,0));
  destroy_bitmap(nullcursor);
  destroy_bitmap(ScreenBuffer);
  destroy_bitmap(BloodBuffer);
}

void Engine::Start()
{
  bool done = false;
  int iCloud = 0;
  int iCloudDelay = 0;
  for(iCloud = 0; iCloud < 3; iCloud++)
    Cloud[iCloud] = new ::Cloud(((iCloud == 2) ? 2 : 1),rand() % SCREEN_W,rand() % 30);
  Cannon = new ::Cannon();  
  Bomb = NULL;
  int iQrczok = 0;
  for(iQrczok = 0; iQrczok < 30; iQrczok++)
    Qrczok[iQrczok] = NULL;
  int iExplosion = 0;
  for(iExplosion = 0; iExplosion < 30; iExplosion++)
    Explosion[iExplosion] = NULL;
  set_mouse_range(0,0,SCREEN_W,SCREEN_H - 18 - Cannon->base->h);
  SAMPLE *sample = (SAMPLE *)datSound[DAT_SND_MUSIC1].dat;
  play_sample(sample,256,127,1000,1);
  MakeSetup = true;
  while(!done)
  {
    switch(Work())
    {
      case ENGINE_CONTINUE: break;
      case ENGINE_QUIT: done = true; break;
    }
    UpdateScreen();
    if(DelayTimerTick)
    {
      DelayTimerTick = false;
      iCloudDelay++;
      if(iCloudDelay > 3)
      {
        for(iCloud = 0; iCloud < 3; iCloud++)
          Cloud[iCloud]->CalcPos();
        iCloudDelay = 0;  
      }    
    }
  }
  stop_sample(sample);
  for(iQrczok = 0; iQrczok < 30; iQrczok++)
    if(Qrczok[iQrczok]) 
      delete Qrczok[iQrczok];
  for(iExplosion = 0; iExplosion < 30; iExplosion++)
    if(Explosion[iExplosion])
      delete Explosion[iExplosion];
  delete Cannon;
  for(iCloud = 0; iCloud < 3; iCloud++)
    delete Cloud[iCloud];
}

void Engine::UpdateScreen()
{
  vsync();
  blit(ScreenBuffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
}

void Engine::DrawMap()
{
  blit((BITMAP *)datGfx[DAT_GFX_MAP].dat,ScreenBuffer,0,0,0,0,640,480);
}

void Engine::DrawMouse(int cursor_num)
{
  DrawMouse(cursor_num,0,0);
}

void Engine::DrawMouse(int cursor_num,int x,int y)
{
  BITMAP *bmp = (BITMAP *)datGfx[cursor_num].dat;
  masked_blit(bmp,ScreenBuffer,0,0,mouse_x - x,mouse_y - y,bmp->w,bmp->h);
}

int Engine::IsTextCentre(char *str,FONT *f,int x,int y)
{
  int mx,my,width,height,ret = 0;
  width = text_length(f,str);
  height = text_height(f);
  mx = x - width / 2;
  my = y;
  if((mouse_x > mx) && (mouse_x < mx + width) &&
    (mouse_y > my) && (mouse_y < my + height))
  {
    ret = 1;
  } 
  return ret;
}

int Engine::IsTextRight(char *str,FONT *f,int x,int y)
{
  int mx,my,width,height,ret = 0;
  width = text_length(f,str);
  height = text_height(f);
  mx = x - width;
  my = y;
  if((mouse_x > mx) && (mouse_x < mx + width) &&
    (mouse_y > my) && (mouse_y < my + height))
  {
    ret = 1;
  } 
  return ret;
}

int Engine::IsTextLeft(char *str,FONT *f,int x,int y)
{
  int mx,my,width,height,ret = 0;
  width = text_length(f,str);
  height = text_height(f);
  mx = x;
  my = y;
  if((mouse_x > mx) && (mouse_x < mx + width) &&
    (mouse_y > my) && (mouse_y < my + height))
  {
    ret = 1;
  } 
  return ret;
}

void Engine::Delay(int ms)
{
  int counter = 0;
  while(counter < ms / 10)
  {
    if(DelayTimerTick)
    {
      counter++;
      DelayTimerTick = false;
    }
  }
}

void Engine::DrawBlood(int qx,int qy)
{
  BITMAP *bone = (BITMAP *)datGfx[DAT_GFX_QRCZAKS_BONE].dat;
  BITMAP *bm = create_bitmap(bone->w,bone->h);
  clear_to_color(bm,makecol(255,0,255));
  rotate_sprite(bm,bone,0,0,itofix(rand() % 255));
  masked_blit(bm,BloodBuffer,0,0,qx,20 + (rand() % 30),bm->w,bm->h);
  for(int i = 0; i < 100; i++)
    putpixel(BloodBuffer,qx + (rand() % 100),20 + (rand() % 60),makecol(239,27,27));
  destroy_bitmap(bm);
}

void Engine::DrawBloodBuffer()
{
  masked_blit(BloodBuffer,ScreenBuffer,0,0,0,SCREEN_H - 80,SCREEN_W,80);
}

void DelayTimer()
{
  DelayTimerTick = true;
}
END_OF_FUNCTION(DelayTimer)

void SecondTimer()
{
  SecondTimerTick = true;
}
END_OF_FUNCTION(SecondTimer)



