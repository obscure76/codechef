#include <iostream>
#include<stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>
#include <fstream>
#define PC 1

using namespace std;

int main()
{
#ifdef PC
    freopen("input","r",stdin);
#endif
    int testcase, len, level;
	long numCovered; 
	scanf("%d", &testcase);
	while(testcase--)
	{
		char str[100001] = {'\0'};
		scanf("%s", str);
		len = strlen(str);
		level = (len+1);
		numCovered = 0;
		
		for(int i=0;i<len;i++)
		{
			if(i%2 && len%2)
				numCovered += 1<<i;
			else if(!(i%2) && !(len%2))
				numCovered += 1<<i;
			if(str[i] == 'r')
				numCovered += 1<<(len-1-i);
		}

		if(len%2)
			printf("%ld\n", 2*(numCovered+1));
		else
			printf("%ld\n", 2*(numCovered+1)-1);
	}
    return 0;
}
