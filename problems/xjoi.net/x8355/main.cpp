/*
 * Problem #8355
 * Tue 06 Aug 2019 @ 22:30 CST)
 * euclidean distance
 */

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

#define UN unsigned
#define ST static
#define CN const
#define LL long long
#define DL double
#define LD long double
#define INF 1047483647
#define PI 3.14159265358979323846264338

using namespace std;

const int MAXSZ = 1; // todo

int main ()
{
  
  int a, b, c, d;
  scanf("%d%d%d%d", &a, &b, &c, &d);
  
  printf("%.2Lf", sqrt(pow(abs((LD)a-(LD)c), 2) + pow(abs((LD)b-(LD)d), 2)));
  return 0;
}
