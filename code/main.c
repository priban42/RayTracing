#include <stdio.h>
#include <SDL.h>
#include <SDL_timer.h>
#include <math.h>

#include "sphere.h"
#include "ray.h"
#include "scene.h"

#define WINDOW_WIDTH (960)
#define WINDOW_HEIGHT (720)

int main(int argc, char* args[]) {

    Scene scene;
    scene_init(&scene);
    scene.width = WINDOW_WIDTH;
    scene.height = WINDOW_HEIGHT;
    scene_add_plane(&scene);
    scene_add_sphere(&scene, -300, 100, 800, 200);
    scene_let_there_be_light(&scene, -400, -800, -100);

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0){
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);

    int close_requested = 0;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    scene_render_raytrace(&scene, renderer);

    while (!close_requested){
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                close_requested = 1;
            }
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(1000/60);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
