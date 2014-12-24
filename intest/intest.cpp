#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;
#define PC 1
#define gcu getchar_unlocked()

unsigned long scanl()
{
    unsigned long ret=0;
    char ch;
    for(ch=gcu;ch<'0' || ch > '9';ch=gcu)
        printf("%c",ch);
    for(;ch>='0' || ch <= '9';ch = gcu)
        ret = ret*10+ch-'0';
    printf("%lu", ret);
    return ret;
}

int main()
{
#ifdef PC
        freopen("input", "r", stdin);
#endif
    unsigned long n,k, x;
    n = scanl();
    k = scanl();
    unsigned long count = 0;
    printf("%lu %lu", n, k);
    /*
    while(n--)
    {
        x = scanl();
        if(x%k==0)
        {
            count++;
        }
    }*/
    printf("%lu",count);
}

