#include #include <string>
#include <cstdlib>
#include <ctime>

#define RAW 4
#define CEL 4
#define NUMBERS 12

class Table
{
public:
    explicit Table();
    ~Table();

    void drow();

private:
    int  **table;

};