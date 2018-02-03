#ifndef __GLOBAL_H__
  #define __GLOBAL_H__
  
  #define DAT_FONT0 0
  #define DAT_FONT1 1
  
  #define DAT_GFX_BOMB 0
  #define DAT_GFX_CLOUD 1
  #define DAT_GFX_CURSOR0 2
  #define DAT_GFX_CURSOR1 3
  #define DAT_GFX_EXPLOSION0 4
  #define DAT_GFX_EXPLOSION1 5
  #define DAT_GFX_EXPLOSION2 6
  #define DAT_GFX_EXPLOSION3 7
  #define DAT_GFX_EXPLOSION4 8
  #define DAT_GFX_EXPLOSION5 9
  #define DAT_GFX_EXPLOSION6 10
  #define DAT_GFX_EXPLOSION7 11
  #define DAT_GFX_GUN 12
  #define DAT_GFX_GUN_BASE 13
  #define DAT_GFX_MAP 14
  #define DAT_GFX_MOUSE 15
  #define DAT_GFX_QRCZAK00 16
  #define DAT_GFX_QRCZAK01 17
  #define DAT_GFX_QRCZAK10 18
  #define DAT_GFX_QRCZAK11 19
  #define DAT_GFX_QRCZAK20 20
  #define DAT_GFX_QRCZAK21 21
  #define DAT_GFX_QRCZAK30L 22
  #define DAT_GFX_QRCZAK30R 23
  #define DAT_GFX_QRCZAK31L 24
  #define DAT_GFX_QRCZAK31R 25
  #define DAT_GFX_QRCZAKS_BONE 26
  
  #define DAT_SND_CANNON 0
  #define DAT_SND_DING 1
  #define DAT_SND_EXPLOSION 2
  #define DAT_SND_HEN 3
  #define DAT_SND_MUSIC1 4
  #define DAT_SND_ROOSTER 5
  #define DAT_SND_SCREAM 6
  
  #include <allegro.h>
  
extern DATAFILE *datGfx;
extern DATAFILE *datFonts;
extern DATAFILE *datSound; 
extern BITMAP *ScreenBuffer;
extern BITMAP *BloodBuffer;
extern volatile bool DelayTimerTick;
extern volatile bool SecondTimerTick;
  
#endif
