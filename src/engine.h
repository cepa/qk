#ifndef __ENGINE_H__
  #define __ENGINE_H__

  #include <allegro.h>
  #include "global.h"
  #include <stdio.h>
  #include "errors.h"
  #include "vector.h"
  #include "cloud.h"
  #include <stdlib.h>
  #include "cannon.h"
  #include "bomb.h"
  #include "qrczok.h"
  #include "explosion.h"

  #define ENGINE_QUIT 1
  #define ENGINE_CONTINUE 0
  #define JOB_START_MENU 0
  #define JOB_QUIT 1
  #define JOB_HELP 2
  #define JOB_GAME 3
  #define JOB_GAME_OVER 4
  #define JOB_PAUSE 5

class Engine
{
  public:
    Engine(int _argc,char **_argv);
    ~Engine();
    bool AllegroInit();
    void AllegroExit();
    bool LoadData();
    void RemoveData();
    bool StartGfx();
    void ShutdownGfx();
    void Start();
    int Work();
    int StartMenu();
    void UpdateScreen();
    void DrawMap();
    void DrawMouse(int cursor_num);
    void DrawMouse(int cursor_num,int x,int y);
    int IsTextCentre(char *str,FONT *f,int x,int y);
    int IsTextRight(char *str,FONT *f,int x,int y);
    int IsTextLeft(char *str,FONT *f,int x,int y);
    int Quit();
    void Delay(int ms);
    int Help();
    int Game();
    bool IsCollision(int x1,int y1,int w1,int h1,int x2,int y2,int w2,int h2);
    int GameOver();
    void DrawBlood(int qx,int qy);
    void DrawBloodBuffer();
    int GamePause();
  private:
    int argc;
    char **argv;  
    int job;
    BITMAP *nullcursor;
    bool StartMenuSetup;
    ::Cloud *Cloud[3];
    ::Cannon *Cannon;
    ::Bomb *Bomb;
    int SmokeY;
    int SmokeColor;
    ::Qrczok *Qrczok[30];
    int QrczoksSpeed;
    int Points;
    int iQrczokDelay;
    int Level;
    bool MakeSetup;
    ::Explosion *Explosion[30];
    int Dead;
};  

void DelayTimer();
void SecondTimer();
  
#endif
