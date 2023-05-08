#include "defer.h"

#include <stdio.h>

int main(int argc, char const *argv[])
{
    FILE* f = fopen("LICENSE", "rb");
    if (!f) 
    {
        return 1;
    }
    DEFER
    {
        fprintf(stderr, "Closing file...\n");
        fclose(f);
        fprintf(stderr, "File closed.\n");
    } END_DEFER;

    while (1)
    {
        int c = fgetc(f);
        if (c == EOF)
        {
            break;
        }
        fprintf(stderr, "%c", c);
    }
    return 0;
}
