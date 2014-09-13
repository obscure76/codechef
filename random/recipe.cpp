#include <iostream>
#include<stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>
#include <fstream>
using namespace std;

int findBound(pair<int, int> *group, int val, int size)
{
  int start = -1;
  int left, right, mid;
  left = 0;
  right = size;
  mid = (left+right)/2;
  while(left<right)
  {
    if(right-left ==1)
      return right;
    mid = (left+right)/2;
    if(group[mid].first > val)
      right = mid;
    else
      left = mid;
  }
  return mid;
}

int main()
{
  int recipeCount, groupNum, alienCount;
  int count = 0;
  int temp, gp=0;
#ifdef PC
      freopen("1.in","r",stdin);
#endif
  scanf("%d", &recipeCount);
  if(recipeCount <= 0)
    return -1;
  pair<int, int> intervalArray[recipeCount];
  int *download = new int[recipeCount];
  while(recipeCount--)
  {
    int start, end;
    scanf("%d %d", &start, &end);
    intervalArray[count].first = start;
    intervalArray[count++].second = end;
  }
  sort(intervalArray, intervalArray+count);
  scanf("%d", &groupNum);

  int* fin = new int[groupNum];
  int index;
  while(groupNum--)
  {
    scanf("%d", &alienCount);
    int *alienArray = new int[alienCount];
    index = 0;
    while(alienCount--)
    {
      scanf("%d", &temp);
      alienArray[index++] = temp;
    }
    sort(alienArray, alienArray+index);
    int currCount = 0;
    int prevind = 0;
    int bound;
    for(int alien = 0; alien < index; alien++)
    {
      bound = findBound(intervalArray, alienArray[alien], count);
      for(int i=prevind;i<bound;i++)
      {
        if(alienArray[alien] < intervalArray[i].first)
          break;
        if(download[i] == gp+1)
          continue;
        if(intervalArray[i].first <= alienArray[alien] && intervalArray[i].second >= alienArray[alien])
        {
          download[i] = gp+1;
          currCount++;
          prevind = i;
        }
      }
    }
    fin[gp++] = currCount;
    //free(alienArray);
  }
  for(int i =0; i< gp; i++)
    printf("%d\n", fin[i]);;
  return 0;
}

