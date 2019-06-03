//INCLUDE EVERYTHING
//#define VITOR

#ifdef VITOR
    #include "SDL.h"
    #include "SDL_mixer.h"
    #include "SDL_ttf.h"
    #include "SDL_image.h"
#elif __APPLE__
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_mixer.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
#elif _WIN32
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_mixer.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
#elif __linux__
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_mixer.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
#else
    #error "Unknown compiler"
#endif

#define PARA(i,max)         for(int i=0;    i<(max);i++)
#define PARA2(i,min,max)    for(int i=(min);i<(max);i++)
#define PARA3(i,max,min)    for(int i=(max);i>(min);i--)
#define MSET(var,val)       memset(var, val, sizeof(var))

#define D_TRACE 1

#define TRACE(msg)          if(D_TRACE) std::cout << msg << std::endl;
#define TRACEN(msg)         if(D_TRACE) std::cout << msg;

#define M_PI                3.14159265358979323846