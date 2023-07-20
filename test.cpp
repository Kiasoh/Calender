#include <bits/stdc++.h>    
using namespace std;
int main ()
{
    char array1[18] = {"abcdefg"};
    char array2[18] = {"hahahahaha"};
    size_t destination_size = sizeof (array2);
    snprintf(array2, destination_size, "%s", array1);
    printf("%s", array2);
}