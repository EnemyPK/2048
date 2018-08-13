#include "2048.h"
#include <conio.h>

int main()
{
    Table* game = new Table();
    game->drow();

    while(true)
    {
        switch(getch())
        {
        case LEFT:  game->move_left();  break;
        case RIGHT: game->move_right(); break;
        case UP:    game->move_up();    break;
        case DOWN:  game->move_down();  break;
        case ESC:   return 0;
        default: break;
        }
    }

    return 0;
}