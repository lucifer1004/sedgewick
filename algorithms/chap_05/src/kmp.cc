#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

const string usage = "[Usage] kmp <pattern> <txt>\n";

class KMP
{
  vector<vector<int>> dfa;
  string pattern;

public:
  KMP(string pattern, int radix = 256)
  {
    assert(!pattern.empty());
    this->pattern = pattern;
    dfa = vector<vector<int>>(radix);
    int length = pattern.size();
    for (auto &character : dfa)
      character = vector<int>(length);
    dfa[pattern[0]][0] = 1;
    for (int restart = 0, step = 1; step < length; step++)
    {
      for (int character = 0; character < radix; character++)
      {
        dfa[character][step] = dfa[character][restart];
      }
      dfa[pattern[step]][step] = step + 1;
      restart = dfa[pattern[step]][restart];
    }
  }

  int match(string txt)
  {
    int txt_length = txt.size();
    int pattern_length = pattern.size();
    if (txt_length < pattern_length)
      return -1;
    int txt_pointer, match_length;
    for (txt_pointer = 0, match_length = 0; txt_pointer < txt_length && match_length < pattern_length; txt_pointer++)
    {
      match_length = dfa[txt[txt_pointer]][match_length];
    }
    if (match_length == pattern_length)
      return txt_pointer - pattern_length;
    else
      return -1;
  }
};

int main(int argc, char **argv)
{
  auto kmp = KMP("hello");
  assert(kmp.match("in hell no one say hello") == 19);
  assert(kmp.match("we are all in a hell oh no") == -1);

  if (argc < 3)
    cout << "Too few arguments.\n"
         << usage;
  else if (argc > 3)
    cout << "Too many arguments.\n"
         << usage;
  else
  {
    kmp = KMP(argv[1]);
    int result = kmp.match(argv[2]);
    if (result == -1)
      cout << "Match failed.\n";
    else
      cout << "First successful match starts at index "
           << result
           << ".\n";
  }
}