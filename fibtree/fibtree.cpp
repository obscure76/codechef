#include <iostream>
#include<stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>
#include <list>
#include <fstream>
#define PC 1
#define MODVAL 1000000009
using namespace std;

list<int> *adj;
list<int> *val;

void updatePath(int src, int dst)
{
	
}

void resetPath(int x)
{
}

int main()
{
#ifdef PC
    freopen("input","r",stdin);
#endif
	int N, M;
	int src, dst;
	scanf("%d %d", &N, &M);
	int* F = new int[N];
	adj = new list<int> [N];
	val = new list<int> [N];
	//Fill the Fibonacci num
	F[0] = F[1] = 1;
	for(int i=2;i<N;i++)
	{
		F[i] = F[i-1]+F[i-2];
	}
	
	//Read the Graph
	for(int i=0;i<N-1;i++)		
	{
		scanf("%d %d", &src, &dst);
		//Add edge from src to dst and dst to src
		adj[src-1].push_back(dst);
		adj[dst-1].push_back(src);
	}
	string str;
	int x,y;
	int iter = 0;
	//Read the Queries
	while(M--)
	{
		cin>>str;
		if(str.compare("A") == 0)
		{
			cin>>x>>y;
			updatePath(x,y);
		} else if(str.compare("R") == 0){
			cin>>x;
			resetVal(x);
		} else if(str.compare("QS") == 0){
			cin>>x>>y;
		} else if(str.compare("QC") == 0){
			cin>>x>>y;
		} 
		iter++;
	} 
	return 0;
}
