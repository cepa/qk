#include "main.h"
#include <allegro.h>
#include "engine.h"

int main(int argc,char **argv)
{
  Engine *app;
  try
  {
    app = new Engine(argc,argv);
  }
  catch(Error)
  {
    set_gfx_mode(GFX_TEXT,0,0,0,0);
    allegro_message("Error !\n");
    return 0;
  }  
  app->Start();
  delete app;
  return 0;
};

END_OF_MAIN();

