#include <Windows.h>
#include "SDL2/SDL.h"

int bootstrap(int argc, char** argv)
{
    return SDL_main(argc, argv);
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR argv, int argc)
{
    return SDL_WinRTRunApp(bootstrap, NULL);
}
