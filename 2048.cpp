/*
    The definition of metods for describe
    the logic of the game. And display it.

    Version 1.11

    Last Revised 8/14/2018
    Autor ENEMY
*/
#include "2048.h"

Table::Table()
{
    /* Variable for Random values*/
    int row    = 0;
    int col    = 0;
    int number = 0;

    /* Defenition standard values for game */
    score = 0;
    free  = 15;
    table = new int*[ROW];
    table[0] = new int[ROW * COL];

    for(size_t i = 1; i < ROW; ++i)
        table[i] = table[i - 1] + COL;

    for(size_t i = 0; i < ROW; ++i)
        for(size_t j = 0; j < COL; ++j)
            table[i][j] = 0;

    /* Standart output for starting game */
    system("cls");
    std::cout << "SCORE:" << score <<std::endl;

    /* Get random block for table */
    srand(time(NULL));

    number = rand() % 2;
    row    = rand() % ROW;
    col    = rand() % COL;

    table[row][col] = number * 2 + 2; /* Paste value in block */
    score += table[row][col];         /* Increase score */
}

/* Method for drownig game table */
void Table::drow()
{
    /* Variable for Random values*/
    int row    = 0;
    int col    = 0;
    int number = 0;

    /* Get random block for table */

    number = rand() % 2;

    
    while(true)       /* Searching free block */
    {
        row = rand() % ROW;
        col = rand() % COL;

        if(table[row][col] == 0)
            break;
    }

    table[row][col] = number * 2 + 2;  /* Paste value in block */
    score += table[row][col];          /* Increase score */
    --free;

    /* Show table */
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

/* Metod for writing number in table */
void Table::write_number(int number)
{
    int    numb = number;
    int    is_n = 0;
    size_t size = 0;

    if(numb == 0)     /* If number is 0, write empty string */
    {
        std::cout << "        ";
        return;
    }

    while(numb != 0)  /* Get the size of number */
    {
        numb /= 10;
        ++size;
    }

    is_n = (8 - size) % 2;  /* Check for parity the size of free space */

    if(is_n)
        std::cout << " ";

    is_n = (8 - size) / 2;

    /* Write number */
    for(size_t i = is_n; i > 0; --i)
        std::cout << " ";

    std::cout << number;

    for(size_t i = is_n; i > 0; --i)
        std::cout << " ";
}

/* Metod for move to left values in the table */
void Table::move_left()
{
    int  position = 0;
    bool change   = false;

    for(size_t i = 0; i < ROW; ++i)
        for(size_t j = 1; j < COL; ++j)
            if(table[i][j] > 0)
            {
                if(table[i][0] == 0)
                {
                    table[i][0] = table[i][j];
                    table[i][j] = 0;
                    change = true;

                    continue;
                }

                position = j - 1;
                
                while((table[i][position] == 0) && (position > 0))
                    --position;

                if(table[i][position] == table[i][j])
                {
                    table[i][position] *= 2;
                    table[i][j] = 0;

                    score += table[i][position];
                    change = true;
                    ++free;
                }
                else if((position + 1) != j)
                {
                    table[i][position + 1] = table[i][j];
                    table[i][j] = 0;
                    change = true;
                }
            }

    if(free == 0)         /* If we have not free space */
    {
        if(is_dead())     /* And we have not opportunity to move blocks */
            game_over();  /* Exit from game */
    }
    else if(change)   /* If we have changes */
    {
        system("cls");  /* Clear screen */
        std::cout << "SCORE:" << score <<std::endl; /* Output score */
        drow();  /* Drow table */
    }
}

/* Metod for move to right values in the table */
void Table::move_right()
{
    int  position = 0;
    bool change   = false;

    for(size_t i = 0; i < ROW; ++i)
        for(size_t j = COL - 2; j >= 0; --j)
        {
            if(j > 4)
                break;

            if(table[i][j] > 0)
            {
                if(table[i][COL - 1] == 0)
                {
                    table[i][COL - 1] = table[i][j];
                    table[i][j] = 0;
                    change = true;

                    continue;
                }

                position = j + 1;

                while((table[i][position] == 0) && (position < 3))
                    ++position;

                if(table[i][position] == table[i][j])
                {
                    table[i][position] *= 2;
                    table[i][j] = 0;

                    score += table[i][position];
                    change = true;
                    ++free;
                }
                else if((position - 1) != j)
                {
                    table[i][position - 1] = table[i][j];
                    table[i][j] = 0;
                    change = true;
                }
            }
        }

    if(free == 0)         /* If we have not free space */
    {
        if(is_dead())     /* And we have not opportunity to move blocks */
            game_over();  /* Exit from game */
    }
    else if(change)   /* If we have changes */
    {
        system("cls");  /* Clear screen */
        std::cout << "SCORE:" << score <<std::endl; /* Output score */
        drow();  /* Drow table */
    }
}

/* Metod for move to up values in the table */
void Table::move_up()
{
    int  position = 0;
    bool change   = false;

    for(size_t i = 0; i < COL; ++i)
        for(size_t j = 1; j < ROW; ++j)
            if(table[j][i] > 0)
            {
                if(table[0][i] == 0)
                {
                    table[0][i] = table[j][i];
                    table[j][i] = 0;
                    change = true;

                    continue;
                }

                position = j - 1;

                while((table[position][i] == 0) && (position > 0))
                    --position;

                if(table[position][i] == table[j][i])
                {
                    table[position][i] *= 2;
                    table[j][i] = 0;

                    score += table[i][position];
                    change = true;
                    ++free;
                }
                else if((position + 1) != j)
                {
                    table[position + 1][i] = table[j][i];
                    table[j][i] = 0;
                    change = true;
                }
            }

    if(free == 0)         /* If we have not free space */
    {
        if(is_dead())     /* And we have not opportunity to move blocks */
            game_over();  /* Exit from game */
    }
    else if(change)   /* If we have changes */
    {
        system("cls");  /* Clear screen */
        std::cout << "SCORE:" << score <<std::endl; /* Output score */
        drow();  /* Drow table */
    }
}

/* Metod for move to down values in the table */
void Table::move_down()
{
    int  position = 0;
    bool change   = false;

    for(size_t i = 0; i < COL; ++i)
        for(size_t j = ROW - 2; j >= 0; --j)
        {
            if(j > 4)
                break;

            if(table[j][i] > 0)
            {
                if(table[ROW - 1][i] == 0)
                {
                    table[ROW - 1][i] = table[j][i];
                    table[j][i] = 0;
                    change = true;

                    continue;
                }

                position = j + 1;

                while((table[position][i] == 0) && (position < 3))
                    ++position;

                if(table[position][i] == table[j][i])
                {
                    table[position][i] *= 2;
                    table[j][i] = 0;

                    score += table[i][position];
                    change = true;
                    ++free;
                }
                else if((position - 1) != j)
                {
                    table[position - 1][i] = table[j][i];
                    table[j][i] = 0;
                    change = true;
                }
            }
        }

    if(free == 0)         /* If we have not free space */
    {
        if(is_dead())     /* And we have not opportunity to move blocks */
            game_over();  /* Exit from game */
    }
    else if(change)   /* If we have changes */
    {
        system("cls");  /* Clear screen */
        std::cout << "SCORE:" << score <<std::endl; /* Output score */
        drow();  /* Drow table */
    }
}

/* Metod for losing and output result */
void Table::game_over()
{
    system("cls");

    std::cout << "GAME OVER" << std::endl;
    std::cout << "SCORE:" << score <<std::endl;

    exit(0);
}

/*
    Metod for checking status of game.
    If we have opportunetes to combine
    blocks return false, else return true
*/
bool Table::is_dead()
{
    for(size_t i = 0; i < ROW; ++i)
        for(size_t j = 0; j < COL; ++j)
        {
            if((j + 1) < COL)
                if(table[i][j] == table[i][j + 1])
                    return false;

            if((i + 1) < ROW)
                if(table[i][j] == table[i + 1][j])
                    return false;
        }

    return true;
}

Table::~Table()
{
    delete[] table;
}