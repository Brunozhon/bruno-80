#include <SDL2/SDL.h>
#include "wren.h"
// x
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const int WIDTH = 256;
const int HEIGHT = 128;
int framebuffer[WIDTH][HEIGHT];

WrenConfiguration config;

void draw(WrenVM* vm) {
    int x = wrenGetSlotDouble(vm, 1);
    int y = wrenGetSlotDouble(vm, 2);

    int r = wrenGetSlotDouble(vm, 3);
    int g = wrenGetSlotDouble(vm, 4);
    int b = wrenGetSlotDouble(vm, 5);

    int color = (r << 24) + (g << 16) + (b << 8);

    framebuffer[x][y] = color;
}

WrenForeignMethodFn bindForeignMethod(
    WrenVM* vm,
    const char* module,
    const char* className,
    bool isStatic,
    const char* signature
) {
    if (strcmp(module, "main") == 0) {
        if (strcmp(className, "Bruno80") == 0) {
            if (isStatic && strcmp(signature, "draw(_,_,_,_,_)") == 0) {
                return draw;
            }
        }
    }
    return NULL;
}

void writeFn(WrenVM* vm, const char* text) {
    printf("%s", text);
}

void errorFn(WrenVM* vm, WrenErrorType errorType,
             const char* module, const int line,
             const char* msg)
{
  switch (errorType)
  {
    case WREN_ERROR_COMPILE:
    {
      printf("[%s line %d] [Error] %s\n", module, line, msg);
    } break;
    case WREN_ERROR_STACK_TRACE:
    {
      printf("[%s line %d] in %s\n", module, line, msg);
    } break;
    case WREN_ERROR_RUNTIME:
    {
      printf("[Runtime Error] %s\n", msg);
    } break;
  }
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Fantasy Computer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH * 4, HEIGHT * 4, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

    wrenInitConfiguration(&config);
    config.writeFn = writeFn;
    config.errorFn = errorFn;
    config.bindForeignMethodFn = bindForeignMethod;

    WrenVM* vm = wrenNewVM(&config);

    WrenInterpretResult result = wrenInterpret(
        vm,
        "main",
        "class Bruno80 {\
    foreign static draw(x, y, r, g, b)\
}"
    );

    wrenInterpret(vm, "main", "Bruno80.draw(1, 2, 255, 0, 0)");

    SDL_Event e;
    bool running = true;
    while (running) {
        SDL_PumpEvents();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
        }

            uint32_t pixels[WIDTH * HEIGHT];
    
            for (int y = 0; y < HEIGHT; y++) {
                for (int x = 0; x < WIDTH; x++) {
                    int color = framebuffer[x][y];  // Assuming `framebuffer[x][y]` holds an RGB or grayscale color
                    pixels[y * WIDTH + x] = color;
                }
            }

            SDL_UpdateTexture(texture, NULL, pixels, WIDTH * sizeof(uint32_t));
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    wrenFreeVM(vm);

    return 0;
}