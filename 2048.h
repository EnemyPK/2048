#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

#define ROW     4
#define COL     4
#define NUMBERS 12

#define ESC     27
#define UP      72
#define DOWN    80
#define LEFT    75
#define RIGHT   77

class Table
{
public:
    explicit Table();
    ~Table();

    void drow();
    void write_number(int);
    void move_left();
    void move_right();
    void move_up();
    void move_down();
    void game_over();

private:
    int** table;
    int   score;
    int   free;
};