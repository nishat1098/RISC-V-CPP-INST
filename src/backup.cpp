#include <bits/stdc++.h>

using namespace std;

class StringOperations
{
protected:
  string removeSpaces(string str)
  {
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
  }

  bool isValidNumber(string a)
  {
    bool isit = true;
    for (int i = 0; i < a.length(); i++)
    {
      if (!(a[i] >= '0' && a[i] <= '9'))
      {
        isit = false;
      }
    }
    // regex b("[0-9]+$");
    // return regex_match(a, b);
    return isit;
  }
  bool isHashThere(string a)
  {
    for (int i = 0; i < a.length(); i++)
    {
      if (a[i] == '#' && i == 0)
        return true;
      if (a[i] == '#')
      {
        string dum = a.substr(i, a.length() - 1);
        for (int j = 0; j < dum.length(); j++)
        {
          if ((dum[j] >= 'a' && dum[j] <= 'z') || (dum[j] >= '0' && dum[j] <= '9') && j != dum.length())
          {
            return true;
          }
        }
      }
    }
    return false;
  }

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
    return (cnt == dum.length());
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
    // cout << res << "\n";
    return res;
  }
};

class OpCodeChecker : public StringOperations
{
private:
  vector<string> valid{"add", "addi", "la", "li", "sub", "subi", "ecall"};
  vector<string> validReg{"x0", "x1", "x2", "x3", "x4", "x5", "x6", "x7", "x8", "x9", "x10", "x11", "x12", "x13", "x14", "x15", "x16", "x17", "x18", "x19", "x20", "x21", "x22", "x23", "x24", "x25", "x26", "x27", "x28", "x29", "x30", "x31", "zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11", "a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7"};

  vector<string> input, output;

protected:
  bool isValidOPCode(string a)
  {
    return (find(validReg.begin(), validReg.end(), a) != validReg.end());
  }

  bool addSubChecker(string a)
  {
    string b;
    bool validity = true;
    auto pos = a.find_first_of(' ');
    b = a.substr(pos, a.length() - 1);

    b = removeSpaces(b);
    vector<string> result;
    stringstream s_stream(b);
    while (s_stream.good())
    {
      string substr;
      getline(s_stream, substr, ',');
      result.push_back(substr);
    }
    if ((a[0] == 's' || a[0] == 'a') && result.size() > 3)
      validity = false;
    else if ((a[0] == 'l') && result.size() > 2)
      validity = false;
    else
    {
      for (int i = 0; i < result.size(); i++)
      {
        if (!isValidOPCode(result[i]) && !isValidNumber(result[i]))
        {
          validity = false;
          break;
        }
      }
    }
    // if (validity) // opt
    // printf("%s\n", a.c_str());
    return validity;
  }

public:
  int a;
  void checkPrint(string path)
  {
    ifstream infile(path);
    string line;
    while (getline(infile, line))
    {
      if (!isHashThere(line))
      {
        input.push_back(line);
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        string x = line;
        if (isHashEnd(line))
          x = removeHashEnd(line);
        output.push_back(x);
      }
    }
    //
    for (int i = 0; i < output.size(); i++)
    {
      stringstream s(output[i]);
      string inst;
      s >> inst;

      if (find(valid.begin(), valid.end(), inst) != valid.end())
      {
        if (inst == "add" || inst == "sub" || inst == "addi" || inst == "subi" || inst == "li" || inst == "la")
        {
          if (addSubChecker(output[i]))
          {
            cout << input[i] << "\n";
          }
        }
        else if (inst == "ecall")
          cout << input[i] << "\n";
      }
    }
  }
};

int main()
{
  string path = "../data/input.txt";
  OpCodeChecker oc;
  oc.checkPrint(path);
}