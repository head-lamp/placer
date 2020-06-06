#ifndef STARTMENU
#define STARTMENU
int8_t init_startup();

int8_t update_startup(SDL_Event *e, int dt);
int8_t draw_startup(SDL_Event *e, int dt);

int8_t init_startmenu(void);
int8_t update_startmenu(SDL_Event *e, int dt);
int8_t draw_startmenu(SDL_Event *e, int dt);
#endif
