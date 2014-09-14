#include <iostream>
#include<stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>
#include <fstream>
//#define PC 1

using namespace std;

int main()
{
#ifdef PC
    freopen("input","r",stdin);
#endif
	int N, M;
	int input;
	int index;
	char ch;
	int a[100000];
	int rot=0,h;
	scanf("%d %d", &N, &M);
	char str[100] = {'\0'};
	string pent;
	for(int i=0;i<N;i++)
		scanf("%d", a+i);
	
	while(M)
	{
		M--;
		cin>>ch>>input;
		switch(ch)
		{
			case 'R':
				index = (rot+input-1)%N;
				printf("%d\n", a[index]);	
				break;
			case 'C':
				rot = (rot+input)%N;
				break;
			case 'A':
				rot = (rot-input)%N;
				if(rot <0)
					rot = rot+N;
				break;
		}
	}
    return 0;
}
