#include <allegro.h>

DATAFILE *datGfx = NULL;
DATAFILE *datFonts = NULL;
DATAFILE *datSound = NULL;
BITMAP *ScreenBuffer = NULL;
volatile bool DelayTimerTick = false;
volatile bool SecondTimerTick = false;
BITMAP *BloodBuffer = NULL;

