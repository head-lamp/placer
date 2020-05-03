#include <SDL2/SDL.h>
#define SHAPE_SIZE 17

int main(int argc, char *argv[])
{
  SDL_Window* Main_Window;
  SDL_Renderer* Main_Renderer;
  SDL_Surface* Loading_Surf;
  SDL_Texture* Background_Tx;
  SDL_Texture* BlueShapes;

  /* Rectangles for drawing which will specify source (inside the texture)
  and target (on the screen) for rendering our textures. */
  SDL_Rect SrcR;
  SDL_Rect DestR;

  SrcR.x = 0;
  SrcR.y = 0;
  SrcR.w = SHAPE_SIZE/32;
  SrcR.h = SHAPE_SIZE/32;

  DestR.x = 640 / 10 - SHAPE_SIZE / 10;
  DestR.y = 580 / 10 - SHAPE_SIZE / 10;
  DestR.w = SHAPE_SIZE/32;
  DestR.h = SHAPE_SIZE/32;
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("sdl wouldn't init %s\n", SDL_GetError());
    }


  /* Before we can render anything, we need a window and a renderer */
  Main_Window = SDL_CreateWindow("SDL_RenderCopy Example",
  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 580, SDL_WINDOW_SHOWN);
  Main_Renderer = SDL_CreateRenderer(Main_Window, -1, SDL_RENDERER_ACCELERATED);
    if (Main_Renderer == NULL) {
        printf("Main_Renderer is null");
    }
    SDL_SetRenderDrawColor(Main_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

  /* The loading of the background texture. Since SDL_LoadBMP() returns
  a surface, we convert it to a texture afterwards for fast accelerated
  blitting. */
  Loading_Surf = SDL_LoadBMP("assets/hedlmp.bmp");
    if (Loading_Surf == NULL) {
        printf("loading surface is null");
    }
  Background_Tx = SDL_CreateTextureFromSurface(Main_Renderer, Loading_Surf);
    if (Background_Tx == NULL) {
        printf("background text is null");
    }
  SDL_FreeSurface(Loading_Surf); /* we got the texture now -> free surface */

  /* Load an additional texture */
  Loading_Surf = SDL_LoadBMP("assets/hedlmp.bmp");
    if (Loading_Surf == NULL) {
        printf("loading surface is null");
    }
  BlueShapes = SDL_CreateTextureFromSurface(Main_Renderer, Loading_Surf);
    if (BlueShapes == NULL) {
        printf("blushapes is null");
    }
  SDL_FreeSurface(Loading_Surf);

    SDL_RenderClear(Main_Renderer);
  /* now onto the fun part.
  This will render a rotating selection of the blue shapes
  in the middle of the screen */
  int i;
  int n;
  for (i = 0; i < 2; ++i) {
    for(n = 0; n < 4; ++n) {
      SrcR.x = SHAPE_SIZE * (n % 8);
      if (n > 1) {
        SrcR.y = SHAPE_SIZE/4;
      } else {
        SrcR.y = 0;
      }

      /* render background, whereas NULL for source and destination
      rectangles just means "use the default" */
      SDL_RenderCopy(Main_Renderer, Background_Tx, NULL, NULL);

      /* render the current animation step of our shape */
      SDL_RenderCopy(Main_Renderer, BlueShapes, &SrcR, &DestR);
      SDL_RenderPresent(Main_Renderer);
      // SDL_Delay(500);
    }
  }
    SDL_Event e;
    bool running =true;
    while (running) {
        while (SDL_PollEvent(&e) != 0){
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }
      SDL_RenderPresent(Main_Renderer);
    }


  /* The renderer works pretty much like a big canvas:
  when you RenderCopy() you are adding paint, each time adding it
  on top.
  You can change how it blends with the stuff that
  the new data goes over.
  When your 'picture' is complete, you show it
  by using SDL_RenderPresent(). */

  /* SDL 1.2 hint: If you're stuck on the whole renderer idea coming
  from 1.2 surfaces and blitting, think of the renderer as your
  main surface, and SDL_RenderCopy() as the blit function to that main
  surface, with SDL_RenderPresent() as the old SDL_Flip() function.*/

  SDL_DestroyTexture(BlueShapes);
  SDL_DestroyTexture(Background_Tx);
  SDL_DestroyRenderer(Main_Renderer);
  SDL_DestroyWindow(Main_Window);
  SDL_Quit();


  return 0;
}

