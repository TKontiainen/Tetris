#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

#define FRAMERATE 60

// Check the return code of an SDL process
void scc(int code)
{
    if (code < 0)
    {
        fprintf(stderr, "SDL error: %s\n", SDL_GetError());
        exit(1);
    }
}

// Check the returned pointer of an SDL process
void* scp(void* ptr)
{
    if (ptr == NULL)
    {
        fprintf(stderr, "SDL error: %s\n", SDL_GetError());
        exit(1);
        return NULL;
    }
    return ptr;
}

int main(void)
{
    scc(SDL_Init(SDL_INIT_VIDEO));

    SDL_Window* window = scp(SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN));

    SDL_Renderer* renderer = scp(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));

    scc(SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255));
    scc(SDL_RenderClear(renderer));

    int quit = 0;
    SDL_Event event;
    int mouse_down = 0;
    while (!quit)
    {
        if (mouse_down)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            scc(SDL_RenderDrawPoint(renderer, x, y));
        }

        while (SDL_PollEvent(&event) != 0)
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    quit = 1;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    switch (event.button.button)
                    {
                    case SDL_BUTTON_LEFT:
                        scc(SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255));
                        mouse_down = 1;
                        break;
                    
                    case SDL_BUTTON_RIGHT:
                        scc(SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255));
                        scc(SDL_RenderClear(renderer));
                        break;
                    
                    default:
                        break;
                    } break;

                case SDL_MOUSEBUTTONUP:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        mouse_down = 0;
                    } break;
                
                default:
                    break;
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}