#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

const string usage = "[Usage] bm <pattern> <txt>\n";

class BM {
  vector<int> right;
  string pattern;

public:
  BM(string pattern, int radix = 256) {
    assert(!pattern.empty());
    this->pattern = pattern;
    right = vector<int>(radix);
    fill(right.begin(), right.end(), -1);
    int length = pattern.size();
    for (int i = 0; i < length; ++i) {
      right[pattern[i]] = i;
    }
  }

  int match(string txt) {
    int txt_length = txt.size();
    int pattern_length = pattern.size();
    int skip;
    for (int i = 0; i <= txt_length - pattern_length; i += skip) {
      skip = 0;
      for (int j = pattern_length - 1; j >= 0; --j) {
        if (pattern[j] != txt[i + j]) {
          skip = max(j - right[txt[i + j]], 1);
          break;
        }
      }
      if (skip == 0)
        return i;
    }
    return -1;
  }
};

int main(int argc, char **argv) {
  auto bm = BM("hello");
  assert(bm.match("in hell no one say hello") == 19);
  assert(bm.match("we are all in a hell oh no") == -1);

  if (argc < 3)
    cout << "Too few arguments.\n" << usage;
  else if (argc > 3)
    cout << "Too many arguments.\n" << usage;
  else {
    bm = BM(argv[1]);
    int result = bm.match(argv[2]);
    if (result == -1)
      cout << "Match failed.\n";
    else
      cout << "First successful match starts at index " << result << ".\n";
  }
}