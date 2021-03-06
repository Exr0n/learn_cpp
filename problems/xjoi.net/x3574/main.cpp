/*
 * Problem #3574
 * 3x5 array
 */

#include <iostream>
#include <string>
#include <math.h>

using namespace std;


int main ()
{
  string line;
  bool gone = 0;
  while (getline(cin, line))
  {
    for (int i=0; i<3; ++i)
    {
      if (gone) cout << endl;
      else gone = true;

      for (int j=0; j<5; ++j) cout << line[j]; // only output 5 characters max, todo this can break if the line is shorter than expected

      if (!getline(cin, line) || line == "") break; // break if the array is shorter than expected
    }
    while (line != "") getline(cin, line); // remove until we get a blank line
  }

  return 0;
}

/* test data
*****
abcdf
abcdg

*****e
abcdff
abcdgg

****
abcd
abcd

*****
inele
nbutt
oohii
hetun

*****
short

*****
abcde
abcde

*/

/* old code
int main ()
{
  string line;
  bool gone = false;
  while (getline(cin, line))
  {
    for (int i=0; i<3; ++i)
    {
      if (gone) cout << endl;
      else gone = true;
      cout << line;
      if (!getline(cin, line)) break;
    }
  }
  //cout << line;

  return 0;
}

int main ()
{
  string line, line1, line2;
  bool gone = false;
  while (getline(cin, line))
  {
    getline(cin, line1);
    getline(cin, line2);

    if (gone) cout << endl;
    else gone = true;

    cout << line << endl << line1 << endl << line2;
    getline(cin, line); // remove trailing newline in input
  }
  //cout << line;

  return 0;
}
*/
