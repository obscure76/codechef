#include <iostream>
#include<stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>
#include <fstream>
using namespace std;
char seq[65] = {'0'};
int nextIndex = 0;
int nextCurr = 0;

int findmatch(char*pat, int patlen, int index, int mlen)
{
    int curr = mlen;
    int len = 32;
    char *s = seq;
    for(int i=index;i<len;i++)
    {
        while(s[i+curr] == pat[curr] && curr < patlen)
        {
            curr++;
            if(nextIndex)
            {
                if((s[nextIndex+nextCurr] == pat[nextCurr]) && (nextIndex+nextCurr == i+curr-1))
                {
                    nextCurr++;
                } else {
                    nextIndex = 0;
                }
            } else if(curr-1){
                if(s[i+curr-1] == pat[0])
                {
                    nextIndex = i+curr-1;
                    nextCurr = 1;
                }
            }
        } 
        if(patlen == curr)
            return i;
        else if(curr>1)
        {
            if(i<nextIndex)
            {
                i = nextIndex;
                curr = nextCurr;
                nextIndex = 0;
            } else {
                i = i+curr-1;
                curr = 0;
            }
        } else {
            curr = 0;
            nextIndex = 0;
        }
    }
    return -1;
}

int main()
{
#ifdef PC
    freopen("ipseq","r",stdin);
#endif
    int testcase, len, tem;
    char vec[100000] = {'0'};
    int temp;
    bool curr;
    int index=0, mlen =0;
    scanf("%d", &testcase);
    seq[0] = '0';
    for(int i=0;i<64;i++)
    {
        if(i)
        {
            curr = false;
            temp = i;
            while(temp)
            {
                curr = curr xor temp%2;
                temp/=2;
            }
        }
        if(curr)
            seq[i] = '1';
        else
            seq[i] = '0';
    }
    seq[64] = '\0';
    for(int i=0;i<testcase;i++)
    {
        scanf("%d", &len);
        memset(vec, '0', sizeof(char) * len);
        for(int j=0;j<len;j++)
        {
            scanf("%d", &tem);
            if(tem)
                vec[j] = '1';
        }
        for(int k=1;k<=len;k++)
        {
            index = findmatch(vec, k, index, mlen);
            printf("%d ", index);
            if(index < 0)
            {
                while(k<len)
                {
                    printf("-1 ");
                    k++;
                }
            } else {
                mlen = k-1;
            }
        }
        nextIndex = 0;
        nextCurr = 0;
        index = 0;
        mlen = 0;
        printf("\n");
    }
    return 0;
}
