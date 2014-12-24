/*
Chef loves to play games. Now he plays very interesting game called "Segment". At the beginning Chef has segment [0, X] and no points on it. On each step
Chef chooses the subsegment of maximal length possible such as it contains no points on it. If there are more than one such subsegment Chef chooses the 
one with the minimal left coordinate. Once Chef chosed the subsegment he put the point in it's middle and the step is over.Help Chef to define the coordinate of the point he will put on the K-th step.
 
Input
The first line contains integer T - number of test cases.
Each of next T lines contains two integers X and K.
  
Output
For each test case in a single line print single double number - the coordinate of the K-th point Chef will put. Answer will be considered as correct if absolute difference between the answer and correct answer is less or equal 10^(-6).
1 ≤ T ≤ 10^5
1 ≤ X ≤ 10^9
1 ≤ K ≤ 10^12
*/
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>
#include <fstream>
#include <cmath>
#define PC 1

using namespace std;

long scanl()
{
    long retval=0;
    char x;
    for(x = getchar_unlocked();x<'0' || x>'9';x=getchar_unlocked());
    for(;x>'0' && x< '9';x=getchar_unlocked())
    {
        retval = retval * 10 + x-'0';
    }
    return retval;
}

int main()
{
#ifdef PC
    freopen("input","r",stdin);
#endif
    int testcase;
    unsigned int X;
    unsigned long K;
    unsigned int left = 0;
    unsigned int level=0;
    unsigned long position;
    double result;
    scanf("%d", &testcase);
    while(testcase--)
    {
        cin>>X;
        K = scanl();
        cout<<X<<' '<<K<<'\t'; 
        int i =0;
        while(i<sizeof(K)*8)
        {
            if(K>>i)
                level = i;
            i++;
        }
        position = K - pow(2,level);
        result = pow(2.0, -1.0*(level+1)) + position * pow(2.0, -1.0*(level));
        result *= X;
        printf("%.4f\n", result);
    }
    return 0;
}
