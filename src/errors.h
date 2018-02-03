#ifndef __ERRORS_H__
  #define __ERRORS_H__
  
  #include <string.h>
  
class Error {};  

class MouseInitError {};

class KeyboardInitError {};

class TimerInitError {};

class SoundInitError {};

class FileNotFound 
{ 
  private:
    char fname[1024];
  public: 
    FileNotFound(char *filename)
    {
      int len = strlen(filename);
      strncpy(fname,filename,((len < 1024) ? len : 1023));
    }
    char *FileName() { return fname; }
};

class DataFileLoadingError 
{ 
  private:
    char fname[1024];
  public: 
    DataFileLoadingError(char *filename)
    {
      int len = strlen(filename);
      strncpy(fname,filename,((len < 1024) ? len : 1023));
    }
    char *FileName() { return fname; }
};

class GfxSettingError {};

class ScreenBufferCreatingError {};

class NullCursorCreatingError {};

class BloodBufferCreatingError {};
 
#endif
