//mingw32-make -f MakeFile


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>

#define HEIGHT 480
#define WITH 640

#define DIM_VET (WITH / 10)

SDL_Window *Inti_wind();
SDL_Renderer *Init_rend(SDL_Window *wind);
void Init_rect(struct SDL_Rect *rect);

void SDL_INPUT();
void SDL_DRAW();


SDL_Window *wind;
SDL_Renderer *rend;

bool run = true, fullscreen = false;

int vet[DIM_VET];
struct SDL_Rect re_vet[DIM_VET];
struct SDL_Rect re;

int main(int argv, char** args) {
    
    wind = Inti_wind();
    rend = Init_rend(wind);
    

    for(int i = 0; i < DIM_VET; i++) {
        vet[i] = rand() % HEIGHT;
        re_vet[i].w = 10;
        re_vet[i].h = vet[i];
        re_vet[i].x = (10 * i);
        re_vet[i].y = HEIGHT - vet[i];
    }


    while(run)    {
        SDL_INPUT();
        SDL_DRAW();
    }


    SDL_DestroyWindow(wind);
    SDL_Quit();

    return 0;
}

SDL_Window *Inti_wind() {

    SDL_Window *wind;

    wind = SDL_CreateWindow("Test 1", 400, 400, WITH, HEIGHT,  SDL_WINDOW_SHOWN /*| SDL_WINDOW_FULLSCREEN*/);

    SDL_Init(SDL_INIT_VIDEO);

    return wind;
}

SDL_Renderer *Init_rend(SDL_Window *wind) {
    SDL_Renderer *rend;

    rend = SDL_CreateRenderer(wind, -1, SDL_RENDERER_ACCELERATED);

    return rend;
}

void Init_rect(struct SDL_Rect *rect) {
    rect->h = 10;
    rect->w = 10;
    rect->x = 10;
    rect->y = 10;
}

void bab() {
    bool ordered = false;

    while(!(ordered)) {
        ordered = true;
        for(int i = 0; i < DIM_VET - 1; i++) {
            if(vet[i] > vet[i + 1]) {
                ordered = false;


                int pos1 = (10 * i), pos2 = (10 * (i + 1));

                struct SDL_Rect r_temp = re_vet[i];
                re_vet[i] = re_vet[i + 1];
                re_vet[i + 1] = r_temp;

                

                re_vet[i].x = pos1;
                re_vet[i + 1].x = pos2;


                int temp = vet[i];
                vet[i] = vet[i + 1];
                vet[i + 1] = temp;

                SDL_DRAW();
            }
        }
    }
}


void SDL_DRAW() {
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderClear(rend);

    SDL_SetRenderDrawColor(rend, 40,43,200,255);
    for(int i = 0; i < DIM_VET; i++) {
        SDL_RenderFillRect(rend, &re_vet[i]);
    }


    SDL_RenderPresent(rend);
    SDL_Delay(16);
}

void SDL_INPUT() {
    SDL_Event ev;

    while(SDL_PollEvent(&ev)) {
        switch (ev.type)
        {
        case SDL_QUIT:
            
            run = false;
            break;

        case SDL_KEYDOWN:

            if(ev.key.keysym.sym == SDLK_RETURN) {
                bab();
            }
            
            break;

    
        default: 
            break;
        }
    }

    const Uint8 *keystates = SDL_GetKeyboardState(NULL);

}

