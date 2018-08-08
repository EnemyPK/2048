#include "2048.h"

Table::Table()
{
    /* Variable for Random values*/
    int row    = 0;
    int col    = 0;
    int number = 0;

    /* Defenition standard values for game */
    score = 0;
    table = new int*[ROW];
    table[0] = new int[ROW * COL];

    for(size_t i = 1; i < ROW; ++i)
        table[i] = table[i - 1] + COL;

    for(size_t i = 0; i < ROW; ++i)
        for(size_t j = 0; j < COL; ++j)
            table[i][j] = 0;

    /* Get random block for table */
    srand(time(NULL));

    number = rand() % 2;
    row    = rand() % ROW;
    col    = rand() % COL;

    table[row][col] = number * 2 + 2;
}

/******************************
 Method for drownig game table
 ******************************/
void Table::drow()
{
    /* Variable for Random values*/
    int row    = 0;
    int col    = 0;
    int number = 0;

    /* Get random block for table */

    number = rand() % 2;

    while(true)
    {
        row    = rand() % ROW;
        col    = rand() % COL;
        if(table[row][col] == 0)
            break;
    }

    table[row][col] = number * 2 + 2;

    /* Show table */
    system("cls");
    std::cout << "-------------------------------------" << std::endl;
    for(size_t i = 0; i < ROW; ++i)
    {
        std::cout << "|        |        |        |        |" << std::endl;

        for(size_t j = 0; j < COL; ++j)
        {
            std::cout << "|" ;
            write_number(table[i][j]);
        }

        std::cout << "|" << std::endl;
        std::cout << "|        |        |        |        |" << std::endl;
        std::cout << "-------------------------------------"  << std::endl;
    }
}

/**********************************
 Metod for writing number in table
 **********************************/
void Table::write_number(int number)
{
    int    numb = number;
    int    is_n = 0;
    size_t size = 0;

    while(numb != 0)
    {
        numb /= 10;
        ++size;
    }

    if(size == 0)
    {
        std::cout << "        ";
        return;
    }

    is_n = (8 - size) % 2;

    if(is_n)
        std::cout << " ";

    for(size_t i = (8 - size) / 2; i > 0; --i)
        std::cout << " ";

    std::cout << number;

    for(size_t i = (8 - size) / 2; i > 0; --i)
        std::cout << " ";
}

Table::~Table()
{
    delete[] table;
}