#ifndef EDITOR_HEADER
#define EDITOR_HEADER
int8_t init_editor(void);
int8_t update_editor(SDL_Event *e, int dt);
int8_t draw_editor(SDL_Event *e, int dt);
#endif
