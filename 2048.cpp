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

    system("cls");
    std::cout << "SCORE:" << score <<std::endl;

    /* Get random block for table */
    srand(time(NULL));

    number = rand() % 2;
    row    = rand() % ROW;
    col    = rand() % COL;

    table[row][col] = number * 2 + 2;
    score += table[row][col];
}

/*********************************
 * Method for drownig game table *
 *********************************/
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
    score += table[row][col];
    ++free;

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

/*************************************
 * Metod for writing number in table *
 *************************************/
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

/*************************************
 * Metod for move to left value in   *
 * the table                         *
 *************************************/
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
                    --free;
                }
                else if((position + 1) != j)
                {
                    table[i][position + 1] = table[i][j];
                    table[i][j] = 0;
                    change = true;
                }
            }

    if(change)
    {
        system("cls");
        std::cout << "SCORE:" << score <<std::endl;
        drow();
    }
}

/*************************************
 * Metod for move to right value in   *
 * the table                         *
 *************************************/
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
                    --free;
                }
                else if((position - 1) != j)
                {
                    table[i][position - 1] = table[i][j];
                    table[i][j] = 0;
                    change = true;
                }
            }
        }

    if(change)
    {
        system("cls");
        std::cout << "SCORE:" << score <<std::endl;
        drow();
    }
}

/*************************************
 * Metod for move to up value in   *
 * the table                         *
 *************************************/
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
                    --free;
                }
                else if((position + 1) != j)
                {
                    table[position + 1][i] = table[j][i];
                    table[j][i] = 0;
                    change = true;
                }
            }

    if(change)
    {
        system("cls");
        std::cout << "SCORE:" << score <<std::endl;
        drow();
    }
}

/*************************************
 * Metod for move to down value in   *
 * the table                         *
 *************************************/
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
                    --free;
                }
                else if((position - 1) != j)
                {
                    table[position - 1][i] = table[j][i];
                    table[j][i] = 0;
                    change = true;
                }
            }
        }

    if(change)
    {
        system("cls");
        std::cout << "SCORE:" << score <<std::endl;
        drow();
    }
}

/*************************************
 * Metod for lose and output result  *
 *************************************/
void Table::game_over()
{
    system("cls");

    std::cout << "GAME OVER" << std::endl;
    std::cout << "SCORE:" << score <<std::endl;
}

Table::~Table()
{
    delete[] table;
}