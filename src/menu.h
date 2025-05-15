#ifndef MENU_H
#define MENU_H

typedef enum {
    MENU,
    GAME,
    INSTRUCOES,
    EXIT
} GameState;

int menu(void);
int buttons(void);

#endif