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
int N, M;
int *F;

typedef struct nodeP_
{
	int curr;
	int parent;
	
} nodeP;

list<int> findPath(int src, int dst)
{
	list<nodeP*> visorder;
	list<int> que;
	nodeP *node = new nodeP;
	node->curr = src;
	node->parent = 0;
	visorder.push_back(node);
	que.push_back(src);
	bool visited[100001] = {0}, found = false;
	visited[src] = 1;
	while(!que.empty() and !found)
	{
		int curr = que.front();
		que.pop_front();
		list<int>::iterator it = adj[curr].begin();
		for(;it!=adj[curr].end();it++)
		{
			if(visited[*it])
				continue;
			visited[*it] = 1;
			nodeP *temp = new nodeP;
			temp->curr = *it;
			temp->parent = curr;
			visorder.push_back(temp);
			que.push_back(*it);
			if(*it == dst)
			{
				found = true;
				break;
			}
		}
	}
	list<int> path;
	nodeP *temp;
	if(found)
	{
		path.push_front(visorder.back()->curr);
		int parent = visorder.back()->parent;
		temp = visorder.back();
		visorder.pop_back();
		delete temp;
		while(!visorder.empty())
		{
			if(visorder.back()->curr == parent)
			{
				parent = visorder.back()->parent;
				path.push_front(visorder.back()->curr);
			}
			temp = visorder.back();
			visorder.pop_back();
			delete temp; 
		}
	} else 
		cout<<"Path not found";
	return path;
}

void updatePath(int x, int y)
{
	list<int> path = findPath(x,y);
	list<int>::iterator it = path.begin();
	for(int i=0;it!=path.end();it++,i++)
	{
		long prev = val[*it].back();
		val[*it].push_back(prev+F[i]);
	}
	path.clear();
}

void resetVal(int x)
{
	int i=0;
	for(int i=0;i<N;i++)
	{
		list<int>::iterator it = val[i].begin();
		for(;it!=val[i].end()&&i<x;it++,i++);
		val[i].push_back(*it);
	}
}

int querySum(int x, int y)
{
	list<int> que;
	int src;
	long sum = 0;
	que.push_back(y);
	bool visited[100001] = {0};
	visited[src] = 1;
	while(!que.empty())
	{
		src = que.front();
		que.pop_front();
		list<int>::iterator it = adj[src].begin();
		for(;it!=adj[src].end();it++)
		{
			if(!visited[*it])
			{
				sum = (sum + val[*it].back())%MODVAL;
				que.push_back(*it);
				visited[*it] = 1;
			}
		}
	}
	printf("%ld", sum);
	return sum;
}

int query(int x, int y)
{
	list<int> path = findPath(x, y);
	list<int>::iterator it = path.begin();
	long sum = 0;
	for(;it!=path.end();it++)
	{
		sum = (sum+val[*it].back())%MODVAL;
	}
	printf("%ld", sum);
	return sum;
}

int main()
{
#ifdef PC
	freopen("input","r",stdin);
#endif
	int src, dst;
	scanf("%d %d", &N, &M);
	F = new int[N];
	adj = new list<int> [N];
	val = new list<int> [N];
	//Fill the Fibonacci num
	F[0] = F[1] = 1;
	for(int i=2;i<N;i++)
	{
		F[i] = F[i-1]+F[i-2];
	}
	for(int i=0;i<N;i++)
	{
		val[i].push_back(0);
	}
	//Read the Graph
	for(int i=0;i<N-1;i++)		
	{
		scanf("%d %d", &src, &dst);
		//Add edge from src to dst and dst to src
		adj[src-1].push_back(dst-1);
		adj[dst-1].push_back(src-1);
	}
	string str;
	int x,y;
	int iter = 0;
	int lastans = 0;
	//Read the Queries
	while(M--)
	{
		cin>>str;
		if(str.compare("A") == 0)
		{
			cin>>x>>y;
			x = x xor lastans;
			updatePath(x-1,y-1);
		} else if(str.compare("R") == 0){
			cin>>x;
			x = x xor lastans;
			resetVal(x);
		} else if(str.compare("QS") == 0){
			cin>>x>>y;
			x = x xor lastans;
			lastans = querySum(x-1, y-1);
		} else if(str.compare("QC") == 0){
			cin>>x>>y;
			x = x xor lastans;
			lastans = query(x-1, y-1);
		} 
		iter++;
	} 
	return 0;
}
