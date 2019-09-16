/*
 ID: spoytie2
 TASK: XXXX
 LANG: C++14
 */

/*
 * Problem 9403 (xjoi.net/9403)
 * Created Sun 15 Sep 2019 @ 14:59 (PDT)
 * Accepted [!meta:end!]
 *
 */

#include <bits/stdc++.h>

#include <iostream>
#include <cstdio>
#include <utility>
#include <exception>
#include <algorithm>
#include <functional>
#include <math.h>
#include <random>
#include <set>
#include <map>
#include <tuple>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>

#define cn const int
#define UN unsigned
#define ST static
#define CN const
#define LL long long
#define DL double
#define LD long double
#define INF 1047483647
#define PI 3.14159265358979323846264338

using namespace std;

const int MAXSZ = 10010; // todo
int bricks[MAXSZ];
int num, siz;

int dfc (cn p=-1, cn l=1)
{
  int count = 0;
  if (l >= siz) count = 1;
  if (p == num-1) return count;
  
  for (int i=p+1; i<num; ++i)
  {
    //for (int i=0; i<l; ++i) printf("  "); printf("%d\n", bricks[i]);
    count += dfc(i, l+1);
    count %= 1000000007;
  }
  return count;
}

int main ()
{
  scanf("%d%d", &num, &siz);
  for (int i=0; i<num; ++i)
  {
    scanf("%d", &bricks[i]);
  }
  sort(bricks, bricks+num, greater<int>());
  
  printf("%d", dfc()-1);
  
  return 0;
}

/*
1 1
10
 
4 1
1 2 3 100
*/
