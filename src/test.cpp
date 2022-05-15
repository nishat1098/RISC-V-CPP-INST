#include <bits/stdc++.h>

using namespace std;

bool isHashEnd(string a)
{
  int cnt = 0;
  string dum;
  for (int i = 0; i < a.length(); i++)
  {
    if (a[i] == '#')
    {
      dum = a.substr(i, a.length() - 1);
      for (int j = 0; j < dum.length(); j++)
      {
        if (dum[j] == '#')
        {
          cnt++;
        }
      }
      break;
    }
  }
  cout << cnt << "\n";
  if (cnt == dum.length())
    return true;
  return false;
}

string removeHashEnd(string a)
{
  string res;
  bool found = false;
  for (int i = 0; i < a.length(); i++)
  {
    if (a[i] == '#')
    {
      res = a.substr(0, i);
      found = true;
      break;
    }
  }
  if (found == false)
    res = a;
  return res;
}

int main()
{
  // string a = "add a, #b, c####";

  // regex b("[a-zA-Z0-9\\s,]+((#)*)$");

  // if (regex_match(a, b))
  //   cout << "matches \n";
  // else
  //   cout << "doesnt \n";

  string str = "add x1, x2, x3 ####";
  // if (isHashEnd(str))
  // {
  //   string res = removeHashEnd(str);
  //   cout << res;
  // }
  // stringstream s(str);
  // string inst;
  // while (s >> inst)
  // {
  //   cout << inst << "\n";
  // }
}