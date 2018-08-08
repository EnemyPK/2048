#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

#define ROW 4
#define COL 4
#define NUMBERS 12

class Table
{
public:
    explicit Table();
    ~Table();

    void drow();
    void write_number(int);

private:
    int  **table;
    int score;
};