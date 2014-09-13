#include <iostream>
#include<stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cmath>
#include <fstream>
using namespace std;

int scan_d() {int ip=getchar_unlocked(),ret=0;for(;ip<'0'||ip>'9';ip=getchar_unlocked());for(;ip>='0'&&ip<='9';ip=getchar_unlocked())ret=ret*10+ip-'0';return ret;}
long scan_ld() {long ip=getc(stdin),ret=0;for(;ip<'0'||ip>'9';ip=getc(stdin));for(;ip>='0'&&ip<='9';ip=getc(stdin))ret=ret*10+ip-'0';return ret;}
long long scan_lld() {long long ip=getc(stdin),ret=0;for(;ip<'0'||ip>'9';ip=getc(stdin));for(;ip>='0'&&ip<='9';ip=getc(stdin))ret=ret*10+ip-'0';return ret;}
long long unsigned scan_llu() {long long unsigned ip=getc(stdin),ret=0;for(;ip<'0'||ip>'9';ip=getc(stdin));for(;ip>='0'&&ip<='9';ip=getc(stdin))ret=ret*10+ip-'0';return ret;}

char* nextPalin(char *ip)
{
    int digits = strlen(ip);
    int ninecount=0;
    int carry = 0;
    int *digitarray = new int[digits]();
    for(int i = 0; i<digits;i++)
        digitarray[i] = ip[i] - '0';
    char *res = new char[1000003]();
    memset(res, '\0', 1000003);
    bool chumma= false, change = false;
    int j=0;
    bool skip = false;
    if(digits == 1)
    {
        res[0] = '1';
        res[1] = '1';
        return res;
    }
    for(int i=0;i < digits/2;i++)
    {
        if(digitarray[i] <= digitarray[digits-1-i]) {
            if((digitarray[i] == digitarray[digits-1-i]) && change)
            {
                skip = true;
                continue;
            }
            change = true;
            if(digitarray[digits-2-i] == 9)
            {
                carry = 1;
                digitarray[digits-2-i] = 0;
                j=1;
                while(carry)
                {
                    carry = (digitarray[digits-2-i-j] +1 )/10;
                    digitarray[digits-2-i-j] = (digitarray[digits-2-i-j] +1 )%10;
                    if(digits-2-i-j == 0)
                    {
                        chumma = true;
                        break;
                    } 
                    j++;
                }
            } else {
                digitarray[digits-2-i]++;
                change = true;
            }
        } else { 
            change = true;
        }
        if(chumma)
            break;
        digitarray[digits-1-i] = digitarray[i] ;
    }
    if(chumma & carry)
    {
        digits++;
        res[0] = res[digits-1] = 1+'0';
        for(int i =1;i<digits-1;i++)
            res[i] = '0';
    } else if(chumma) {
        for(int i =1;i<digits-1;i++)
            res[i] = '0';
    } else {
        for(int i = digits-1;i>=0;i--)
            res[i] = digitarray[i]+'0';
    }
    return res;
}

int main()
{
    int t;
    char ip[1000003] = {'\0'};
    //freopen("ippalin", "r", stdin);
    scanf("%d", &t);
    while(t--)
    {
        memset(ip,'\0',1000000);
        scanf("%s", ip);
        if(t)
            printf("%s\n", nextPalin(ip));
        else
            printf("%s", nextPalin(ip));
    }
    return 0;
}
