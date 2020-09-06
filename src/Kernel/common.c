#include "kernel.h"

size_t strlen(char *str)
{
    register size_t len = 0;
    while (str[len])
        len++;
    return len;
}

bool strcmp(char *str1, char *str2)
{
    register size_t len = strlen(str1);

    if (len != strlen(str2))
        return false;

    for (int i = 0; i < len; i++)
        if (str1[i] != str2[i])
            return false;
    
    return true;
}