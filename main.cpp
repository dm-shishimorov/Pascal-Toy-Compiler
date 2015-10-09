#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>

#include "tokenizer.hpp"

using namespace std;

enum compState { csTokenizer, csParser };

void badOpt(const char* opt) {
  cout << "fatal error: undefined option " << opt << endl;
}

int main(int argc, char** argv) {
  if (argc == 1) {
    cout << "fatal error: no input files" << endl;
    return 0;
  }

  vector<string> files;
  vector<compState> st;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (strlen(argv[i]) == 2) {
        bool f = false;
        switch (argv[i][1]) {
          case 't':
            st.push_back(csTokenizer);
            break;
          case 'p':
            st.push_back(csParser);
            break;
          default:
            badOpt(argv[i]);
            return 0;
        }
      }
      else {
        badOpt(argv[i]);
        return 0;
      }
    }
    else {
      files.push_back(argv[i]);
    }
  }

  for (int i = 0; i < st.size(); i++) {
    for (int j = 0; j < files.size(); j++) {
      ifstream fin(files[j]);
      string str;
      getline(fin, str, '\0');

      if (st[i] == csTokenizer) {
        Tokenizer t(str);
        while (!t.eof()) {
          Token tt = t.nextToken();
          cout << tt._row << '\t' << tt._col << '\t' << tokenTypeNames[tt._type] << '\t' << tt._value << endl;
        }

      }
      else if (st[i] == csParser) {
        cout << "Called Parser" << endl;
      }
    }
  }

  return 0;
}